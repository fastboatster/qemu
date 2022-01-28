/*
 *  TriCore emulation for qemu: fpu helper.
 *
 *  Copyright (c) 2016 Bastian Koppelmann University of Paderborn
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include "qemu/osdep.h"
#include "cpu.h"
#include "exec/helper-proto.h"
#include "fpu/softfloat.h"

#define QUIET_NAN 0x7fc00000
#define ADD_NAN   0x7fc00001
#define SQRT_NAN  0x7fc00004
#define DIV_NAN   0x7fc00008
#define MUL_NAN   0x7fc00002
#define FPU_FS PSW_USB_BIT31
#define FPU_FI PSW_USB_BIT30
#define FPU_FV PSW_USB_BIT29
#define FPU_FZ PSW_USB_BIT28
#define FPU_FU PSW_USB_BIT27
#define FPU_FX PSW_USB_BIT26
#define FPU_RM1 PSW_USB_BIT25
#define FPU_RM0 PSW_USB_BIT24

#define float32_sqrt_nan make_float32(SQRT_NAN)
#define float32_quiet_nan make_float32(QUIET_NAN)

//the define generates addition info on stderr
//#define DBG_FPU_HELPER


/* we don't care about input_denormal */
static inline uint8_t f_get_excp_flags(CPUTriCoreState *env)
{
    return get_float_exception_flags(&env->fp_status)
           & (float_flag_invalid
              | float_flag_overflow
              | float_flag_underflow
              | float_flag_output_denormal
              | float_flag_divbyzero
              | float_flag_inexact);
}

static inline float32 f_maddsub_nan_result(float32 arg1, float32 arg2,
                                           float32 arg3, float32 result,
                                           uint32_t muladd_negate_c)
{
    uint32_t aSign, bSign, cSign;
    uint32_t aExp, bExp, cExp;

    if (float32_is_any_nan(arg1) || float32_is_any_nan(arg2) ||
        float32_is_any_nan(arg3)) {
        return QUIET_NAN;
    } else if (float32_is_infinity(arg1) && float32_is_zero(arg2)) {
        return MUL_NAN;
    } else if (float32_is_zero(arg1) && float32_is_infinity(arg2)) {
        return MUL_NAN;
    } else {
        aSign = arg1 >> 31;
        bSign = arg2 >> 31;
        cSign = arg3 >> 31;

        aExp = (arg1 >> 23) & 0xff;
        bExp = (arg2 >> 23) & 0xff;
        cExp = (arg3 >> 23) & 0xff;

        if (muladd_negate_c) {
            cSign ^= 1;
        }
        if (((aExp == 0xff) || (bExp == 0xff)) && (cExp == 0xff)) {
            if (aSign ^ bSign ^ cSign) {
                return ADD_NAN;
            }
        }
    }

    return result;
}

static void f_update_psw_flags(CPUTriCoreState *env, uint8_t flags)
{
    uint8_t some_excp = 0;
    set_float_exception_flags(0, &env->fp_status);

    if (flags & float_flag_invalid) {
        env->FPU_FI = 1 << 31;
        some_excp = 1;
    }

    if (flags & float_flag_overflow) {
        env->FPU_FV = 1 << 31;
        some_excp = 1;
    }

    if (flags & float_flag_underflow || flags & float_flag_output_denormal) {
        env->FPU_FU = 1 << 31;
        some_excp = 1;
    }

    if (flags & float_flag_divbyzero) {
        env->FPU_FZ = 1 << 31;
        some_excp = 1;
    }

    if (flags & float_flag_inexact || flags & float_flag_output_denormal) {
    	env->FPU_FX = 1 << 31;
        some_excp = 1;
    }

    env->FPU_FS = some_excp;
}

#define FADD_SUB(op)                                                           \
uint32_t helper_f##op(CPUTriCoreState *env, uint32_t r1, uint32_t r2)          \
{                                                                              \
    float32 arg1 = make_float32(r1);                                           \
    float32 arg2 = make_float32(r2);                                           \
    uint32_t flags;                                                            \
    float32 f_result;                                                          \
                                                                               \
    f_result = float32_##op(arg2, arg1, &env->fp_status);                      \
    flags = f_get_excp_flags(env);                                             \
    if (flags) {                                                               \
        /* If the output is a NaN, but the inputs aren't,                      \
           we return a unique value.  */                                       \
        if ((flags & float_flag_invalid)                                       \
            && !float32_is_any_nan(arg1)                                       \
            && !float32_is_any_nan(arg2)) {                                    \
            f_result = ADD_NAN;                                                \
        }                                                                      \
        f_update_psw_flags(env, flags);                                        \
    } else {                                                                   \
        env->FPU_FS = 0;                                                       \
    }                                                                          \
    return (uint32_t)f_result;                                                 \
}
FADD_SUB(add)
FADD_SUB(sub)

uint32_t helper_fmul(CPUTriCoreState *env, uint32_t r1, uint32_t r2)
{
    uint32_t flags;
    float32 arg1 = make_float32(r1);
    float32 arg2 = make_float32(r2);
    float32 f_result;

    f_result = float32_mul(arg1, arg2, &env->fp_status);

    flags = f_get_excp_flags(env);
    if (flags) {
        /* If the output is a NaN, but the inputs aren't,
           we return a unique value.  */
        if ((flags & float_flag_invalid)
            && !float32_is_any_nan(arg1)
            && !float32_is_any_nan(arg2)) {
                f_result = MUL_NAN;
        }
        f_update_psw_flags(env, flags);
    } else {
        env->FPU_FS = 0;
    }
    return (uint32_t)f_result;

}

/*
 * Target TriCore QSEED.F significand Lookup Table
 *
 * The QSEED.F output significand depends on the least-significant
 * exponent bit and the 6 most-significant significand bits.
 *
 * IEEE 754 float datatype
 * partitioned into Sign (S), Exponent (E) and Significand (M):
 *
 * S   E E E E E E E E   M M M M M M ...
 *    |             |               |
 *    +------+------+-------+-------+
 *           |              |
 *          for        lookup table
 *      calculating     index for
 *        output E       output M
 *
 * This lookup table was extracted by analyzing QSEED output
 * from the real hardware
 */
static const uint8_t target_qseed_significand_table[128] = {
    253, 252, 245, 244, 239, 238, 231, 230, 225, 224, 217, 216,
    211, 210, 205, 204, 201, 200, 195, 194, 189, 188, 185, 184,
    179, 178, 175, 174, 169, 168, 165, 164, 161, 160, 157, 156,
    153, 152, 149, 148, 145, 144, 141, 140, 137, 136, 133, 132,
    131, 130, 127, 126, 123, 122, 121, 120, 117, 116, 115, 114,
    111, 110, 109, 108, 103, 102, 99, 98, 93, 92, 89, 88, 83,
    82, 79, 78, 75, 74, 71, 70, 67, 66, 63, 62, 59, 58, 55,
    54, 53, 52, 49, 48, 45, 44, 43, 42, 39, 38, 37, 36, 33,
    32, 31, 30, 27, 26, 25, 24, 23, 22, 19, 18, 17, 16, 15,
    14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2
};

uint32_t helper_qseed(CPUTriCoreState *env, uint32_t r1)
{
    uint32_t arg1, S, E, M, E_minus_one, m_idx;
    uint32_t new_E, new_M, new_S, result;

    arg1 = make_float32(r1);

    /* fetch IEEE-754 fields S, E and the uppermost 6-bit of M */
    S = extract32(arg1, 31, 1);
    E = extract32(arg1, 23, 8);
    M = extract32(arg1, 17, 6);

    if (float32_is_any_nan(arg1)) {
        result = float32_quiet_nan;
    } else if (float32_is_zero_or_denormal(arg1)) {
        if (float32_is_neg(arg1)) {
            result = float32_infinity | (1 << 31);
        } else {
            result = float32_infinity;
        }
    } else if (float32_is_neg(arg1)) {
        result = float32_sqrt_nan;
    } else if (float32_is_infinity(arg1)) {
        result = float32_zero;
    } else {
        E_minus_one = E - 1;
        m_idx = ((E_minus_one & 1) << 6) | M;
        new_S = S;
        new_E = 0xBD - E_minus_one / 2;
        new_M = target_qseed_significand_table[m_idx];

        result = 0;
        result = deposit32(result, 31, 1, new_S);
        result = deposit32(result, 23, 8, new_E);
        result = deposit32(result, 15, 8, new_M);
    }

    if (float32_is_signaling_nan(arg1, &env->fp_status)
        || result == float32_sqrt_nan) {
        env->FPU_FI = 1 << 31;
        env->FPU_FS = 1;
    } else {
        env->FPU_FS = 0;
    }

    return (uint32_t) result;
}

uint32_t helper_fdiv(CPUTriCoreState *env, uint32_t r1, uint32_t r2)
{
    uint32_t flags;
    float32 arg1 = make_float32(r1);
    float32 arg2 = make_float32(r2);
    float32 f_result;

    f_result = float32_div(arg1, arg2 , &env->fp_status);

    flags = f_get_excp_flags(env);
    if (flags) {
        /* If the output is a NaN, but the inputs aren't,
           we return a unique value.  */
        if ((flags & float_flag_invalid)
            && !float32_is_any_nan(arg1)
            && !float32_is_any_nan(arg2)) {
                f_result = DIV_NAN;
        }
        f_update_psw_flags(env, flags);
    } else {
        env->FPU_FS = 0;
    }

    return (uint32_t)f_result;
}

uint32_t helper_fmadd(CPUTriCoreState *env, uint32_t r1,
                      uint32_t r2, uint32_t r3)
{
    uint32_t flags;
    float32 arg1 = make_float32(r1);
    float32 arg2 = make_float32(r2);
    float32 arg3 = make_float32(r3);
    float32 f_result;

    f_result = float32_muladd(arg1, arg2, arg3, 0, &env->fp_status);

    flags = f_get_excp_flags(env);
    if (flags) {
        if (flags & float_flag_invalid) {
            arg1 = float32_squash_input_denormal(arg1, &env->fp_status);
            arg2 = float32_squash_input_denormal(arg2, &env->fp_status);
            arg3 = float32_squash_input_denormal(arg3, &env->fp_status);
            f_result = f_maddsub_nan_result(arg1, arg2, arg3, f_result, 0);
        }
        f_update_psw_flags(env, flags);
    } else {
        env->FPU_FS = 0;
    }
    return (uint32_t)f_result;
}

uint32_t helper_fmsub(CPUTriCoreState *env, uint32_t r1,
                      uint32_t r2, uint32_t r3)
{
    uint32_t flags;
    float32 arg1 = make_float32(r1);
    float32 arg2 = make_float32(r2);
    float32 arg3 = make_float32(r3);
    float32 f_result;

    f_result = float32_muladd(arg1, arg2, arg3, float_muladd_negate_product,
                              &env->fp_status);

    flags = f_get_excp_flags(env);
    if (flags) {
        if (flags & float_flag_invalid) {
            arg1 = float32_squash_input_denormal(arg1, &env->fp_status);
            arg2 = float32_squash_input_denormal(arg2, &env->fp_status);
            arg3 = float32_squash_input_denormal(arg3, &env->fp_status);

            f_result = f_maddsub_nan_result(arg1, arg2, arg3, f_result, 1);
        }
        f_update_psw_flags(env, flags);
    } else {
        env->FPU_FS = 0;
    }
    return (uint32_t)f_result;
}

uint32_t helper_fcmp(CPUTriCoreState *env, uint32_t r1, uint32_t r2)
{
    uint32_t result, flags;
    float32 arg1 = make_float32(r1);
    float32 arg2 = make_float32(r2);

    set_flush_inputs_to_zero(0, &env->fp_status);

    result = 1 << (float32_compare_quiet(arg1, arg2, &env->fp_status) + 1);
    result |= float32_is_denormal(arg1) << 4;
    result |= float32_is_denormal(arg2) << 5;

    flags = f_get_excp_flags(env);
    if (flags) {
        f_update_psw_flags(env, flags);
    } else {
        env->FPU_FS = 0;
    }

    set_flush_inputs_to_zero(1, &env->fp_status);
    return result;
}

uint32_t helper_ftoi(CPUTriCoreState *env, uint32_t arg)
{
    float32 f_arg = make_float32(arg);
    int32_t result, flags;

    result = float32_to_int32(f_arg, &env->fp_status);

    flags = f_get_excp_flags(env);
    if (flags) {
        if (float32_is_any_nan(f_arg)) {
            result = 0;
        }
        f_update_psw_flags(env, flags);
    } else {
        env->FPU_FS = 0;
    }
    return (uint32_t)result;
}

uint32_t helper_itof(CPUTriCoreState *env, uint32_t arg)
{
    float32 f_result;
    uint32_t flags;
    f_result = int32_to_float32(arg, &env->fp_status);

    flags = f_get_excp_flags(env);
    if (flags) {
        f_update_psw_flags(env, flags);
    } else {
        env->FPU_FS = 0;
    }
    return (uint32_t)f_result;
}

uint32_t helper_utof(CPUTriCoreState *env, uint32_t arg)
{
    float32 f_result;
    uint32_t flags;

    f_result = uint32_to_float32(arg, &env->fp_status);

    flags = f_get_excp_flags(env);
    if (flags) {
        f_update_psw_flags(env, flags);
    } else {
        env->FPU_FS = 0;
    }
    return (uint32_t)f_result;
}

uint32_t helper_ftoiz(CPUTriCoreState *env, uint32_t arg)
{
    float32 f_arg = make_float32(arg);
    uint32_t result;
    int32_t flags;

    result = float32_to_int32_round_to_zero(f_arg, &env->fp_status);

    flags = f_get_excp_flags(env);
    if (flags & float_flag_invalid) {
        flags &= ~float_flag_inexact;
        if (float32_is_any_nan(f_arg)) {
            result = 0;
        }
    }

    if (flags) {
        f_update_psw_flags(env, flags);
    } else {
        env->FPU_FS = 0;
    }

    return result;
}

uint32_t helper_ftouz(CPUTriCoreState *env, uint32_t arg)
{
    float32 f_arg = make_float32(arg);
    uint32_t result;
    int32_t flags;

    result = float32_to_uint32_round_to_zero(f_arg, &env->fp_status);

    flags = f_get_excp_flags(env);
    if (flags & float_flag_invalid) {
        flags &= ~float_flag_inexact;
        if (float32_is_any_nan(f_arg)) {
            result = 0;
        }
    } else if (float32_lt_quiet(f_arg, 0, &env->fp_status)) {
        flags = float_flag_invalid;
        result = 0;
    }

    if (flags) {
        f_update_psw_flags(env, flags);
    } else {
        env->FPU_FS = 0;
    }
    return result;
}

void helper_updfl(CPUTriCoreState *env, uint32_t arg)
{
    uint32_t mask_psw=((arg & 0x0000FF00))<<16;
    uint32_t bits_psw=((arg & 0x000000FF))<<24;
#ifdef DBG_FPU_HELPER
    fprintf(stderr,"upfdl0 %8.8x %8.8x %8.8x %8.8x %8.8x\n",env->PC,env->PSW,arg, mask_psw,bits_psw);
#endif
    env->PSW = env->PSW & ~mask_psw;
    env->PSW = env->PSW | bits_psw;
    //the internal flags according to the status of updated PSW
    if ((env->PSW & MASK_USB_BIT31) !=0) env->FPU_FS=1; else env->FPU_FS=0;
    if ((env->PSW & MASK_USB_BIT30) !=0) env->FPU_FI=1<<31; else env->FPU_FI=0;
    if ((env->PSW & MASK_USB_BIT29) !=0) env->FPU_FV=1<<31; else env->FPU_FV=0;
    if ((env->PSW & MASK_USB_BIT28) !=0) env->FPU_FZ=1<<31; else env->FPU_FZ=0;
    if ((env->PSW & MASK_USB_BIT27) !=0) env->FPU_FU=1<<31; else env->FPU_FU=0;
    if ((env->PSW & MASK_USB_BIT26) !=0) env->FPU_FX=1<<31; else env->FPU_FX=0;
    if ((env->PSW & MASK_USB_BIT25) !=0) env->FPU_RM1=1<<31; else env->FPU_RM1=0;
    if ((env->PSW & MASK_USB_BIT24) !=0) env->FPU_RM0=1<<31; else env->FPU_RM0=0;
#ifdef DBG_FPU_HELPER
    fprintf(stderr,"upfdl1 %8.8x %8.8x %8.8x %8.8x %8.8x\n",env->PC,env->PSW,arg, mask_psw,bits_psw);
#endif
    fpu_set_state(env);
}

static inline uint32_t extractF32Frac(float32 a);
static inline uint32_t extractF32Frac(float32 a) { return a & 0x007FFFFF; };
static inline int32_t extractF32Exp(float32 a);
static inline int32_t extractF32Exp(float32 a) { return (a >> 23) & 0xFF; };
static inline uint32_t extractF32Sign(float32 a);
static inline uint32_t extractF32Sign(float32 a) { return (uint32_t)(a >> 31); };
static inline uint32_t extractF16Frac(float16 a);
static inline uint32_t extractF16Frac(float16 a) { return a & 0x03FF; };
static inline int32_t  extractF16Exp(float16 a);
static inline int32_t  extractF16Exp(float16 a) { return (a >> 10) & 0x1F; };
static inline uint32_t extractF16Sign(float16 a);
static inline uint32_t extractF16Sign(float16 a) { return (uint32_t)(a >> 15); };
static inline float32 roundAndPackF32Q31(CPUTriCoreState *env,uint32_t zSign, int32_t zExp, uint32_t zSig, uint32_t rnd, int32_t *flags);
static inline float32 check_and_handle_denormal_flags_f32f32(float32 a, int32_t *flags);
static inline float32 check_and_handle_denormal_f32f32(float32 a);
static inline uint32_t check_and_handle_denormal_flags_u32f32(float32 a, int32_t *flags);
static inline uint32_t check_and_handle_denormal_u32f32(float32 a);
static inline uint32_t check_and_handle_denormal_u32u32(uint32_t a);
static inline void normalizeF16Subnormal(uint32_t aSig, int32_t * zExpPtr, uint32_t * zSigPtr);
static inline int32_t countLeadingZeros16(uint32_t a);
static inline void shift32RightJ(uint32_t a, int32_t count, uint32_t *zPtr);
static inline void shift16RightJ(uint32_t a, int32_t count, uint32_t * zPtr);
static inline void shift32Right(uint32_t a, int32_t count, uint32_t *zPtr);
static inline uint32_t roundAndPackF16(CPUTriCoreState *env,uint32_t zSign, int32_t zExp, uint32_t zSig, uint32_t rnd, int32_t *flags);
static inline uint32_t packF16(uint32_t zSign, int32_t zExp, uint32_t zSig);

static inline uint32_t packF16(uint32_t zSign, int32_t zExp, uint32_t zSig)
{
    return ((((uint32_t)(uint32_t) zSign) << 15) + (((uint32_t)(uint32_t) zExp) << 10U) + zSig);
}

static inline void shift16RightJ(uint32_t a, int32_t count, uint32_t * zPtr)
{
    uint32_t z;
    if (count == 0)
    {
        z = a;
    }
    else if (count < 16)
    {
        z = (a >> count) | (uint32_t)(((a << ((0-count) & 15)) & 0xFFFF) != 0);
    }
    else
    {
        z = (a != 0);
    }
    *zPtr = z;
}


static inline uint32_t roundAndPackF16(CPUTriCoreState *env,uint32_t zSign, int32_t zExp, uint32_t zSig, uint32_t rnd, int32_t *flags)
{
    int32_t roundingMode;
    uint32_t roundNearestEven;
    int32_t roundIncrement;
    int32_t roundBits;
    uint32_t isTiny;

    roundingMode = rnd;
    roundNearestEven = (uint32_t)(roundingMode == float_round_nearest_even);
    roundIncrement = 0x8;
    if (!roundNearestEven)
    {
        if (roundingMode == float_round_to_zero)
        {
            roundIncrement = 0;
        }
        else
        {
            roundIncrement = 0xF;
            if (zSign)
            {
                if (roundingMode == float_round_up)
                    roundIncrement = 0;
            }
            else
            {
                if (roundingMode == float_round_down)
                    roundIncrement = 0;
            }
        }
    }
    roundBits = (int32_t)(zSig & 0xF);
    if (0x1D <= (uint32_t) zExp)
    {
        if ((0x1D < zExp) || ((zExp == 0x1D) && ((int32_t) (zSig + (uint32_t)(int)roundIncrement) < 0)))
        {
            *flags|=float_flag_overflow | float_flag_inexact;
            return packF16(zSign, 0x1F, 0) - (int32_t)(roundIncrement == 0);
        }
        if (zExp < 0)
        {
            isTiny = (uint32_t)((get_float_detect_tininess(&env->fp_status)) ||
                            (zExp < -1) ||
                            (zSig + (uint32_t)(int32_t)roundIncrement < 0x8000));
            shift16RightJ(zSig, -zExp, &zSig);
            zExp = 0;
            roundBits = (int32_t)(zSig & 0xF);
            if (isTiny && roundBits)
            *flags|=float_flag_underflow;
        }
    }
    if (roundBits)
    	*flags|=float_flag_inexact;
    zSig = (zSig + (uint32_t)(int32_t)roundIncrement) >> 4;
    zSig &= ~((int32_t)((roundBits ^ 0x8) == 0) & roundNearestEven);
    if (zSig == 0)
        zExp = 0;
    return packF16(zSign, zExp, zSig);
}



static const int32_t countLeadingZerosHigh[] = {
    8, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static inline int32_t countLeadingZeros16(uint32_t a)
{
    int32_t shiftCount = 0;
    if (a < 0x100) {
        shiftCount += 8;
        a <<= 8;
    }
    shiftCount = (int32_t)(shiftCount + countLeadingZerosHigh[a>>8]);
    return shiftCount;
}

static inline void normalizeF16Subnormal(uint32_t aSig, int32_t * zExpPtr, uint32_t * zSigPtr)
{
    int32_t shiftCount;

    shiftCount = (int32_t)(countLeadingZeros16(aSig) - 5);
    *zSigPtr = (uint32_t)((uint32_t)aSig << shiftCount);
    *zExpPtr = 1 - shiftCount;
}

static inline void shift32RightJ(uint32_t a, int32_t count, uint32_t *zPtr)
{
	uint32_t z;
	if ( count == 0 ) {
		z = a;
	}
	else if ( count < 32 ) {
		z = ( a>>count ) | ( ( a<<( ( - count ) & 31 ) ) != 0 );
	}
	else {
		z = ( a != 0 );
	}
	*zPtr = z;
}

static inline void shift32Right(uint32_t a, int32_t count, uint32_t *zPtr)
{
    uint32_t z;
    if (count == 0)
    {
        z = a;
    }
    else if (count < 32)
    {
        z = a >> count;
    }
    else
    {
        z = 0;
    }
    *zPtr = z;
}

static inline float32 check_and_handle_denormal_flags_f32f32(float32 a, int32_t *flags)
{
	int32_t aExp;
	uint32_t aSig;
	aSig = extractF32Frac(a);
	aExp = extractF32Exp(a);
	if ((aExp == 0) && (aSig != 0))
	{
		*flags|=float_flag_inexact | float_flag_underflow;
		return (float32) (0x80000000 & a);
	}
	return a;
}

static inline float32 check_and_handle_denormal_f32f32(float32 a)
{
	int32_t aExp;
	uint32_t aSig;
	aSig = extractF32Frac(a);
	aExp = extractF32Exp(a);
	if ((aExp == 0) && (aSig != 0))
	{
		return (float32) (0x80000000 & a);
	}
	return a;
}

static inline uint32_t check_and_handle_denormal_flags_u32f32(float32 a, int32_t *flags)
{
	int32_t aExp;
	uint32_t aSig;
	aSig = extractF32Frac(a);
	aExp = extractF32Exp(a);
	if ((aExp == 0) && (aSig != 0))
	{
		*flags|=float_flag_inexact | float_flag_underflow;
		return (uint32_t) (0x80000000 & a);
	}
	return a;
}

static inline uint32_t check_and_handle_denormal_u32f32(float32 a)
{
	int32_t aExp;
	uint32_t aSig;
	aSig = extractF32Frac(a);
	aExp = extractF32Exp(a);
	if ((aExp == 0) && (aSig != 0))
	{
		return (uint32_t) (0x80000000 & a);
	}
	return a;
}

static inline uint32_t check_and_handle_denormal_u32u32(uint32_t a)
{
	int32_t aExp;
	uint32_t aSig;
	aSig = a & 0x007FFFFF;
	aExp = (a >> 23) & 0xFF;
	if ((aExp == 0) && (aSig != 0))
	{
		return (uint32_t) (0x80000000 & a);
	}
	return a;
}

static inline float32 roundAndPackF32Q31(CPUTriCoreState *env,uint32_t zSign, int32_t zExp, uint32_t zSig, uint32_t rnd, int32_t *flags)
{
	int32_t roundingMode;
	uint32_t roundNearestEven;
	int32_t roundIncrement, roundBits;
	uint32_t isTiny;
	float32 tempRes;
	int32_t zExpCopy = zExp;

	roundingMode = rnd;
	roundNearestEven = (uint32_t)(roundingMode == float_round_nearest_even);
	roundIncrement = 0x40;
	if (!roundNearestEven)
	{
		if (roundingMode == float_round_to_zero)
		{
			roundIncrement = 0;
		}
		else
		{
			roundIncrement = 0x7F;
			if (zSign)
			{
				if (roundingMode == float_round_up)
					roundIncrement = 0;
			}
			else
			{
				if (roundingMode == float_round_down)
					roundIncrement = 0;
			}
		}
	}
	roundBits = (int32_t)(zSig & 0x7F);
	if (0xFE <= (uint32_t) zExp)
	{
		if ((0xFE < zExp) || ((zExp == 0xFE) && ((int32_t) (zSig + (uint32_t)(int32_t)roundIncrement) < 0)))
		{
			*flags|= float_flag_overflow | float_flag_inexact;
			return packFloat32(zSign, 0xFF, 0) - (float32)(roundIncrement == 0);
		}
		if (zExp < 0)
		{
			isTiny = (uint32_t)((get_float_detect_tininess(&env->fp_status)) ||
					(zExp < -1) ||
					(zSig + (uint32_t)(int)roundIncrement < 0x80000000));

			shift32RightJ(zSig, -zExp, &zSig);
			zExp = 0;
			roundBits = (int32_t)(zSig & 0x7F);
			if (isTiny || roundBits)
			{
				*flags|=float_flag_underflow | float_flag_inexact;
			}
		}
	}
	if (roundBits)
	{
		*flags|=float_flag_inexact;
	}

	uint32_t roundval = ~((uint32_t)((roundBits ^ 0x40) == 0) & roundNearestEven);

	if (roundNearestEven && (zExp == 0))
	{
		roundIncrement = 0x80;
		roundval = ~((uint32_t)((zSig & (uint32_t)(int)roundIncrement) == 0x0) & roundNearestEven);
	}

	zSig = (zSig + (uint32_t)(int)roundIncrement) >> 7;
	zSig &= roundval;

	if ((zExp == 0) && (zSig == 0x7FFFFF))
	{
		zSig = 0x800000;
	}
	tempRes = packFloat32(zSign, zExp, zSig);
	if ((tempRes == 0x7F800000) || (tempRes == 0xFF800000))
	{
		*flags|=float_flag_overflow;
	}
	if ((tempRes == 0x00800000)
			&& ((roundingMode == float_round_down) || (roundingMode == float_round_to_zero))
			&& (zExpCopy == 0x0))
	{
		return 0x0;
	}
	if ((tempRes == 0x80800000)
			&& ((roundingMode == float_round_up) || (roundingMode == float_round_to_zero))
			&& (zExpCopy == 0x0))
	{
		return 0x80000000;
	}
	return tempRes;
}


/*
FTOQ31 D[c], D[a], D[b] (RR)
arg_a = denorm_to_zero(f_real(D[a]);
if(is_nan(D[a])) then result = 0;
else precise_result = mul(arg_a, 2-D[b][8:0]);
if(precise_result > q_real(7FFFFFFFH)) then result = 7FFFFFFFH;
else if(precise_result < -1.0) then result = 80000000H;
else result = round_to_q31(precise_result);
D[c] = result[31:0]
arg0=Da, arg1=Db
 */

static uint32_t ftoq31xx(CPUTriCoreState *env, uint32_t arg1, uint32_t arg2,uint32_t rnd)
{

	int32_t aExp;
	uint32_t aSig;
	int32_t aSign;
	int32_t flags;
	uint32_t roundingBits;
	int32_t expAdj = 0;
	uint32_t Result1 = 0;
	uint32_t Result2 = 0;
	uint32_t Result4 = 0;
	float32 f_arg1;
	uint32_t rounding_mode=rnd;
#ifdef DBG_FPU_HELPER
	fprintf(stderr,"ftoq31xx %8.8x %8.8x %8.8x %d\n",env->PC,arg1,arg2,rounding_mode);
#endif

	flags = f_get_excp_flags(env);
	flags &= ~float_flag_invalid;
	flags &= ~float_flag_inexact;

	arg1 = check_and_handle_denormal_u32u32(arg1);
	f_arg1= make_float32(arg1);

	if (float32_is_any_nan(f_arg1))
	{
		flags=float_flag_invalid;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"1\n");
#endif
		return 0x0;
	}

	expAdj = arg2 & 0x1FF;

	if ((expAdj & 0x100) == 0x100)
	{
		expAdj = ~(uint32_t)expAdj & 0x1FF;
		expAdj = expAdj + 1;
		expAdj = -expAdj;
	}

	aSig = arg1 & 0x007FFFFFu;
	aExp = (arg1>>23) & 0xFFu;
	aSign = arg1>>31;

	if ((arg1 == 0x80000000) || (arg1== 0x0))
	{
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"2\n");
#endif
		return 0;
	}

	if (arg1 == 0x7F800000)
	{
		flags=float_flag_invalid;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"3\n");
#endif
		return 0x7FFFFFFF;
	}

	if (arg1 == 0xFF800000)
	{
		flags=float_flag_invalid;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"4\n");
#endif
		return 0x80000000;
	}

	if ((arg1 == 0xBF800000) && (arg2 == 0x0))
	{
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"5\n");
#endif
		return 0x80000000;
	}

	if ((arg1 == 0x3F800000) && (arg2 == 0x0))
	{
		flags=float_flag_invalid;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"6\n");
#endif
		return 0x7FFFFFFF;
	}

	if ((aSign == 1) && ((aExp - expAdj) == 0x5F)
			&& (rounding_mode == float_round_nearest_even) && (aSig == 0))
	{
		//update inexact only if FI=0 and FZ=0
		//		if (((env->FPU_FI & 0x80000000)==0) && ((env->FPU_FZ & 0x80000000)==0))
		//		{
		flags=float_flag_inexact;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
		//		}
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"7\n");
#endif
		return 0;
	}
	if ((aSign == 0) && ((aExp - expAdj) == 0x5F)
			&& (rounding_mode == float_round_nearest_even) && (aSig == 0))
	{
		//update inexact only if FI=0 and FZ=0
		//		if (((env->FPU_FI & 0x80000000)==0) && ((env->FPU_FZ & 0x80000000)==0))
		//		{
		flags=float_flag_inexact;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
		//		}
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"8\n");
#endif
		return 0;
	}
	if ((aSign == 1) && ((aExp - expAdj) == 127) && (aSig == 0))
	{
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"9\n");
#endif
		return 0x80000000;
	}
	if ((aSign == 1) && ((aExp - expAdj) > 126))
	{
		flags=float_flag_invalid;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"10\n");
#endif
		return 0x80000000;
	}
	if ((aSign == 0) && ((aExp - expAdj) > 126))
	{
		flags=float_flag_invalid;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"11\n");
#endif
		return 0x7FFFFFFF;
	}

	if (((aExp - expAdj) < 96) && (((rounding_mode == float_round_nearest_even) && (((aExp - expAdj) != 0x5F))) ||
			((rounding_mode == float_round_down)
					&& (aSign == 0x0))
					|| (rounding_mode == float_round_to_zero)))
	{
		//update inexact only if FI=0 and FZ=0
		//    	if (((env->FPU_FI & 0x80000000)==0) && ((env->FPU_FZ & 0x80000000)==0))
		//    	{
		flags=float_flag_inexact;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
		//    	}
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"12\n");
#endif
		return 0;
	}

	if (((aExp - expAdj) < 96) && ( ((rounding_mode == float_round_nearest_even)
			&& ((aExp - expAdj) == 0x5F)
			&& (aSign == 0x0))
			|| ((rounding_mode == float_round_up)
					&& (aSign == 0x0))
	))
	{
		//update inexact only if FI=0 and FZ=0
		//    	if (((env->FPU_FI & 0x80000000)==0) && ((env->FPU_FZ & 0x80000000)==0))
		//    	{
		flags=float_flag_inexact;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
		//    	}
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"13\n");
#endif
		return 0x00000001;
	}

	if (((aExp - expAdj) < 96) && (((rounding_mode == float_round_nearest_even)
			&& ((aExp - expAdj) != 0x5F))
			|| ((rounding_mode == float_round_up)
					&& (aSign == 0x1))
					|| (rounding_mode == float_round_to_zero)))
	{
		//update inexact only if FI=0 and FZ=0
		//    	if (((env->FPU_FI & 0x80000000)==0) && ((env->FPU_FZ & 0x80000000)==0))
		//    	{
		flags=float_flag_inexact;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
		//    	}
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"14\n");
#endif
		return 0x0;
	}

	if (((aExp - expAdj) < 96) && ( ((rounding_mode == float_round_nearest_even)
			&& ((aExp - expAdj) == 0x5F)
			&& (aSign == 0x1) )
			|| ((rounding_mode == float_round_down)
					&& (aSign == 0x1))
	))
	{
		//update inexact only if FI=0 and FZ=0
		//    	if (((env->FPU_FI & 0x80000000)==0) && ((env->FPU_FZ & 0x80000000)==0))
		//    	{
		flags=float_flag_inexact;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
		//    	}
#ifdef    DBG_FPU_HELPER
		fprintf(stderr,"15\n");
#endif
		return 0xFFFFFFFF;
	}

	aSig = aSig << 8;

	if (aSign == 0x0)
	{
		roundingBits = aSig << ((23 - ((127 - (aExp - expAdj)))) + 9);
		Result1 = (0x80000000 >> (127 - (aExp - expAdj)));
		Result2 = (aSig >> ((127 - (aExp - expAdj))));
		Result4 = Result1 | Result2;
		if (roundingBits != 0x0)
		{
			//update inexact only if FI=0 and FZ=0
			//        	if (((env->FPU_FI & 0x80000000)==0) && ((env->FPU_FZ & 0x80000000)==0))
			//        	{
			flags=float_flag_inexact;
			if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
			//        	}
#ifdef    DBG_FPU_HELPER
			fprintf(stderr,"16\n");
#endif
		}
	}
	else
	{
		roundingBits = aSig << ((23 - ((127 - (aExp - expAdj)))) + 9);
		Result1 = (0x80000000 >> (127 - (aExp - expAdj)));
		Result2 = (aSig >> ((127 - (aExp - expAdj))));
		Result4 = Result1 | Result2;
		Result4 = ((~Result4) + 1);
		if (roundingBits != 0x0)
		{
			//update inexact only if FI=0 and FZ=0
			//        	if (((env->FPU_FI & 0x80000000)==0) && ((env->FPU_FZ & 0x80000000)==0))
			//        	{
			flags=float_flag_inexact;
			if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
			//        	}
#ifdef    DBG_FPU_HELPER
			fprintf(stderr,"17\n");
#endif
		}
	}
	if (roundingBits)
	{
		if ((Result4 & 0x80000000) == 0x80000000)
		{
			switch (rounding_mode)
			{
			case float_round_nearest_even:
				if (roundingBits == 0x80000000)
				{
					if ((Result4 & 0x1) == 0x1)
					{
						Result4--;
					}
				}
				if (roundingBits > 0x80000000)
				{
					Result4--;
				}
				break;
			case float_round_down:
				Result4--;
				break;
			case float_round_up:
				break;
			case float_round_to_zero:
				break;
			default:
				assert(0);
				break;
			}
		}
		else
		{
			switch (rounding_mode)
			{
			case float_round_nearest_even:
				if (roundingBits == 0x80000000)
				{
					if ((Result4 & 0x1) == 0x1)
					{
						Result4++;
					}
				}
				if (roundingBits > 0x80000000)
				{
					Result4++;
				}
				break;
			case float_round_up:
				Result4++;
				break;
			case float_round_down:
				break;
			case float_round_to_zero:
				break;
			default:
				assert(0);
				break;
			}
		}
	}
	if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
	fprintf(stderr,"E\n");
#endif
	return Result4;
}

uint32_t helper_ftoq31(CPUTriCoreState *env, uint32_t arg1, uint32_t arg2)
{
    uint32_t res;
	uint32_t rounding_mode_tc=(env->PSW>>24) & 0x3;
	uint32_t rounding_mode_host=(env->PSW>>24) & 0x3;
    //Tricore Rounding Modes
	//00 Round to nearest.
	//01 Round toward +inf
	//10 Round toward -inf
	//11 Round toward zero
	switch (rounding_mode_tc)
	{
	case 0x0: rounding_mode_host=float_round_nearest_even; break;
	case 0x1: rounding_mode_host=float_round_up; break;
	case 0x2: rounding_mode_host=float_round_down; break;
	case 0x3: rounding_mode_host=float_round_to_zero; break;
	default: break;
	}
	res=ftoq31xx(env,arg1,arg2,rounding_mode_host);
    return res;
}


uint32_t helper_ftoq31z(CPUTriCoreState *env, uint32_t arg1, uint32_t arg2)
{
    uint32_t res;
    //round to zero
    res=ftoq31xx(env,arg1,arg2,0x3);
    return res;
}



uint32_t helper_q31tof(CPUTriCoreState *env, uint32_t arg1, uint32_t arg2)
{
	uint32_t result;
	int32_t flags;
	int32_t temparg1 = (int32_t) arg1;
	int32_t ResSign = (uint32_t)(arg1 >> 31);
	int32_t expAdj = 0;
	int32_t shiftcnt = 1;
	int32_t ResExp;
	uint32_t ResSignificand;
	uint32_t rounding_mode_tc;

	switch ((env->PSW>>24) & 0x3)
	{
	case 0x0: rounding_mode_tc=float_round_nearest_even; break;
	case 0x1: rounding_mode_tc=float_round_up; break;
	case 0x2: rounding_mode_tc=float_round_down; break;
	case 0x3: rounding_mode_tc=float_round_to_zero; break;
	default: break;
	}

#ifdef DBG_FPU_HELPER
	fprintf(stderr,"q31tof %8.8x %8.8x %8.8x %d\n",env->PC,arg1,arg2,rounding_mode_tc);
#endif
	flags = f_get_excp_flags(env);
	flags &= ~float_flag_inexact;
	flags &= ~float_flag_overflow;
	flags &= ~float_flag_underflow;

	if ((arg1 == 0x80000000) && ((arg2 & 0x000001FF) == 0x00000181))
	{
		flags=float_flag_underflow | float_flag_inexact;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
			fprintf(stderr,"1\n");
#endif
			return 0x80000000;
	}
	if ((arg1 == 0x80000081) && ((arg2 & 0x000001FF) == 0x00000182)
			&& (rounding_mode_tc != float_round_down))
	{
		flags=float_flag_underflow | float_flag_inexact;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
			fprintf(stderr,"2\n");
#endif
			return 0x80000000;
	}
	if ((arg1 == 0x80000081) && ((arg2 & 0x000001FF) == 0x00000182)
			&& (rounding_mode_tc == float_round_down))
	{
		flags=float_flag_underflow | float_flag_inexact;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
			fprintf(stderr,"3\n");
#endif
			return 0x80800000;
	}
	if ((arg1 == 0x7FFFFF7F) && ((arg2 & 0x000001FF) == 0x00000182)
			&& (rounding_mode_tc == float_round_up))
	{
		flags=float_flag_underflow | float_flag_inexact;
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
			fprintf(stderr,"4\n");
#endif
			return 0x00800000;
	}

	if (arg1 == 0)
	{
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
			fprintf(stderr,"5\n");
#endif
			return 0;
	}

	expAdj = arg2 & 0x1FF;
	if ((expAdj & 0x100) == 0x100)
	{
		expAdj = ~(uint32_t)expAdj & 0x1FF;
		expAdj = expAdj + 1;
		expAdj = -expAdj;
	}

	if ((arg1 & 0x80000000) == 0x80000000)
	{
		arg1 = ~arg1;
		arg1 = arg1 + 1;
	}

	if ((arg1 == 0x80000000))
	{
        result=check_and_handle_denormal_flags_u32f32(roundAndPackF32Q31
                                          (env,ResSign, (127 + expAdj), 0, rounding_mode_tc,&flags),&flags);
		if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
			fprintf(stderr,"6\n");
#endif
		return result;
	}

	if (ResSign == 1)
	{
		temparg1 = -temparg1;
		arg1 = (uint32_t)temparg1;
	}

	arg1 = arg1 << 1;

	while ((arg1 & 0x80000000) != 0x80000000)
	{
		arg1 = arg1 << 1;
		shiftcnt++;
	}

	if (((uint32_t)(expAdj - shiftcnt) < 0xFFFFFF82) && ((uint32_t)(expAdj - shiftcnt) > 0x80000000))
	{
		flags=float_flag_underflow | float_flag_inexact;
#ifdef    DBG_FPU_HELPER
			fprintf(stderr,"7\n");
#endif
	}

	if (((uint32_t)(expAdj - shiftcnt) > 127) && ((uint32_t)(expAdj - shiftcnt) < 0x80000000))
	{
		flags=float_flag_overflow | float_flag_inexact;
#ifdef    DBG_FPU_HELPER
			fprintf(stderr,"8\n");
#endif
	}
	arg1 = (arg1 >> 1) & 0x3FFFFFFF;
	ResExp = (int32_t)((127 - (int32_t)shiftcnt) + expAdj);
	ResSignificand = arg1;
    result=check_and_handle_denormal_flags_u32f32(roundAndPackF32Q31
                                      (env,ResSign, ResExp, ResSignificand,rounding_mode_tc,&flags),&flags);
    if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
			fprintf(stderr,"E\n");
#endif
    return result;
}

uint32_t helper_hptof(CPUTriCoreState *env, uint32_t arg)
{
    float16 a;
    uint32_t aSign;
    int32_t aExp;
    uint32_t aSig;
    uint32_t zSig;
	uint32_t result;
	int32_t flags;

#ifdef DBG_FPU_HELPER
	fprintf(stderr,"hptof %8.8x %8.8x \n",env->PC,arg);
#endif
	flags = f_get_excp_flags(env);
	flags &= ~float_flag_invalid;

    a=(float16) (arg & 0xFFFF);

    aSig = extractF16Frac(a);
    aExp = extractF16Exp(a);
    aSign = extractF16Sign(a);

    if (aExp == 0x1F)
    {
        if (aSig)
        {
            zSig = (((uint32_t)aSig & 0x300) << 13 ) | ((uint32_t)aSig & 0xFF);
            if ( (aSig & 0x200) == 0 )
                flags |=float_flag_invalid;
            result=packFloat32(aSign, 0xFF, zSig);
            if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
            return result;
        }
        result=packFloat32(aSign, 0xFF, 0);
        if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
        return result;
    }
    if (aExp == 0)
    {
        if (aSig == 0)
        {
        result=packFloat32(aSign, 0, 0);
        if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
        return result;
        }
        normalizeF16Subnormal(aSig, &aExp, &aSig);
        --aExp;
    }
    shift32Right((uint32_t)aSig << 16, 3, &zSig);
    result=packFloat32(aSign, (int32_t)aExp + 0x70, zSig);
    if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
			fprintf(stderr,"E\n");
#endif
	return result;
}

uint32_t helper_ftohp(CPUTriCoreState *env, uint32_t arg)
{
    uint32_t aSign;
    int32_t aExp;
    uint32_t aSig, zSig;
	uint32_t result;
	int32_t flags;
	uint32_t rounding_mode_tc;

	switch ((env->PSW>>24) & 0x3)
	{
	case 0x0: rounding_mode_tc=float_round_nearest_even; break;
	case 0x1: rounding_mode_tc=float_round_up; break;
	case 0x2: rounding_mode_tc=float_round_down; break;
	case 0x3: rounding_mode_tc=float_round_to_zero; break;
	default: break;
	}
#ifdef DBG_FPU_HELPER
	fprintf(stderr,"ftohp %8.8x %8.8x %d\n",env->PC,arg,rounding_mode_tc);
#endif
	flags = f_get_excp_flags(env);
	flags &= ~float_flag_inexact;
	flags &= ~float_flag_invalid;
	flags &= ~float_flag_underflow;
	flags &= ~float_flag_overflow;

    arg = check_and_handle_denormal_u32u32(arg);

    aSig  = arg & 0x007FFFFF;
    aExp  = (arg >> 23) & 0xFF;
    aSign = arg >> 31;
    if (aExp == 0xFF)
    {
        if (aSig)
        {
            zSig = ((aSig & 0x00600000) >> 13 ) | (aSig & 0xFF);
            if (zSig == 0)
            {
                zSig = 0x100;
            }
            if ( (aSig & 0x00400000) == 0 )
                flags |=float_flag_invalid;
            result=packF16(aSign, 0x1F, (uint32_t)zSig);
            if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
            return result;
        }

        result=packF16(aSign, 0x1F, 0);
        if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
        return result;
    }
    shift32RightJ(aSig, 9, &zSig);
    if (aExp)
        zSig |= 0x4000;
    result=roundAndPackF16(env,aSign, aExp - 0x71, (uint32_t)zSig, rounding_mode_tc, &flags);
    if (flags) { f_update_psw_flags(env, flags); } else { env->FPU_FS = 0; }
#ifdef    DBG_FPU_HELPER
			fprintf(stderr,"E\n");
#endif
    return result;
}
