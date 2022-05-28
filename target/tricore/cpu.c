/*
 *  TriCore emulation for qemu: main translation routines.
 *
 *  Copyright (c) 2012-2014 Bastian Koppelmann C-Lab/University Paderborn
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
#include "qapi/error.h"
#include "cpu.h"
#include "exec/exec-all.h"
#include "exec/gdbstub.h"
#include "qemu/error-report.h"

static inline void set_feature(CPUTriCoreState *env, int feature)
{
    env->features = feature;
}


static gchar *tricore_gdb_arch_name(CPUState *cs)
{
    TriCoreCPU *cpu = TRICORE_CPU(cs);
    CPUTriCoreState *env = &cpu->env;
    if (tricore_feature(env, TRICORE_FEATURE_162)) return g_strdup("TriCore:V1_6_2");
    if (tricore_feature(env, TRICORE_FEATURE_161)) return g_strdup("TriCore:V1_6_1");
    if (tricore_feature(env, TRICORE_FEATURE_16)) return g_strdup("TriCore:V1_6");
    if (tricore_feature(env, TRICORE_FEATURE_131)) return g_strdup("TriCore:V1_3_1");
    if (tricore_feature(env, TRICORE_FEATURE_13)) return g_strdup("TriCore:V1_3");
    return g_strdup("Tricore:Unknown");
}

static void tricore_cpu_set_pc(CPUState *cs, vaddr value)
{
    TriCoreCPU *cpu = TRICORE_CPU(cs);
    CPUTriCoreState *env = &cpu->env;

    env->PC = value & ~(target_ulong)1;
}

static void tricore_cpu_synchronize_from_tb(CPUState *cs,
                                            const TranslationBlock *tb)
{
    TriCoreCPU *cpu = TRICORE_CPU(cs);
    CPUTriCoreState *env = &cpu->env;

    env->PC = tb->pc;
}

static void tricore_cpu_reset(DeviceState *dev)
{
    CPUState *s = CPU(dev);
    TriCoreCPU *cpu = TRICORE_CPU(s);
    TriCoreCPUClass *tcc = TRICORE_CPU_GET_CLASS(cpu);
    CPUTriCoreState *env = &cpu->env;

    tcc->parent_reset(dev);

    cpu_state_reset(env);
}



static bool tricore_cpu_has_work(CPUState *cs)
{
    return true;
}

static void tricore_cpu_realizefn(DeviceState *dev, Error **errp)
{
    CPUState *cs = CPU(dev);
    TriCoreCPUClass *tcc = TRICORE_CPU_GET_CLASS(dev);
    Error *local_err = NULL;

    cpu_exec_realizefn(cs, &local_err);
    if (local_err != NULL) {
        error_propagate(errp, local_err);
        return;
    }

    cpu_reset(cs);
    qemu_init_vcpu(cs);

    tcc->parent_realize(dev, errp);
}


static void tricore_cpu_initfn(Object *obj)
{
    TriCoreCPU *cpu = TRICORE_CPU(obj);

    cpu_set_cpustate_pointers(cpu);
}

static ObjectClass *tricore_cpu_class_by_name(const char *cpu_model)
{
    ObjectClass *oc;
    char *typename;

    typename = g_strdup_printf(TRICORE_CPU_TYPE_NAME("%s"), cpu_model);
    oc = object_class_by_name(typename);
    g_free(typename);
    if (!oc || !object_class_dynamic_cast(oc, TYPE_TRICORE_CPU) ||
        object_class_is_abstract(oc)) {
        return NULL;
    }
    return oc;
}

static void tc1791_initfn(Object *obj)
{
    TriCoreCPU *cpu = TRICORE_CPU(obj);

    set_feature(&cpu->env, TRICORE_FEATURE_161);
}

static void tc1796_initfn(Object *obj)
{
    TriCoreCPU *cpu = TRICORE_CPU(obj);

    set_feature(&cpu->env, TRICORE_FEATURE_13);
}

static void tc1797_initfn(Object *obj)
{
    TriCoreCPU *cpu = TRICORE_CPU(obj);

    set_feature(&cpu->env, TRICORE_FEATURE_131);
}

static void tc27x_initfn(Object *obj)
{
    TriCoreCPU *cpu = TRICORE_CPU(obj);

    set_feature(&cpu->env, TRICORE_FEATURE_161);
}

static void tc161_initfn(Object *obj)
{
    TriCoreCPU *cpu = TRICORE_CPU(obj);

    set_feature(&cpu->env, TRICORE_FEATURE_161);
}

static void tc162_initfn(Object *obj)
{
    TriCoreCPU *cpu = TRICORE_CPU(obj);

    set_feature(&cpu->env, TRICORE_FEATURE_162);
}

static void tc16_initfn(Object *obj)
{
    TriCoreCPU *cpu = TRICORE_CPU(obj);

    set_feature(&cpu->env, TRICORE_FEATURE_16);
}

static void tc13_initfn(Object *obj)
{
    TriCoreCPU *cpu = TRICORE_CPU(obj);

    set_feature(&cpu->env, TRICORE_FEATURE_13);
}

static void tc131_initfn(Object *obj)
{
    TriCoreCPU *cpu = TRICORE_CPU(obj);

    set_feature(&cpu->env, TRICORE_FEATURE_131);
}
#include "hw/core/sysemu-cpu-ops.h"

static const struct SysemuCPUOps tricore_sysemu_ops = {
    .get_phys_page_debug = tricore_cpu_get_phys_page_debug,
};

#include "hw/core/tcg-cpu-ops.h"

static const struct TCGCPUOps tricore_tcg_ops = {
    .initialize = tricore_tcg_init,
    .synchronize_from_tb = tricore_cpu_synchronize_from_tb,
    .tlb_fill = tricore_cpu_tlb_fill,
    .do_interrupt = tricore_cpu_do_interrupt,
    .do_unaligned_access = tricore_cpu_do_unaligned_access,
};


void tricore_cpu_do_unaligned_access(CPUState *cs, vaddr addr,
                                   MMUAccessType access_type,
                                   int mmu_idx, uintptr_t retaddr)
{
    cs->exception_index = EXCP_UNALIGN;
    cpu_loop_exit(cs);
}

void tricore_cpu_do_interrupt(CPUState *cs)
{
	  TriCoreCPU *cpu = TRICORE_CPU(cs);
	  CPUTriCoreState *env = &cpu->env;
		switch (cs->exception_index)
		{
		case EXCP_EXIT:
		{
			uint32_t exit_arg;
			qemu_log_mask(LOG_GUEST_ERROR,"tricore_cpu_do_interrupt EXCP_EXIT %x %x\n",env->PC,env->gpr_a[14]);
			if (env->gpr_a[14]==0x900d) exit_arg=0; else exit_arg=env->gpr_a[14];
			gdb_exit(exit_arg);
			exit(exit_arg);
			break;
		}
		case EXCP_UNALIGN:
		{
			qemu_log_mask(LOG_GUEST_ERROR,"tricore_cpu_do_interrupt EXCP_UNALIGN %x\n",env->PC);
			cs->exception_index=0;
			tricore_raise_exception_sync(env, TRAPC_INSN_ERR, TIN2_ALN);
			break;
		}

		case EXCP_SEMIHOST:
		{
			qemu_log_mask(LOG_GUEST_ERROR,"tricore_cpu_do_interrupt EXCP_SEMIHOST %x %d \n",env->PC,env->gpr_d[12]);
			qemu_log_mask(LOG_GUEST_ERROR,"a4 %x\n",env->gpr_a[4]);
			qemu_log_mask(LOG_GUEST_ERROR,"d4 %x\n",env->gpr_d[4]);
			qemu_log_mask(LOG_GUEST_ERROR,"d5 %x\n",env->gpr_d[5]);
			qemu_log_mask(LOG_GUEST_ERROR,"d12 %x\n",env->gpr_d[12]);
			env->PC += 2;
			cs->exception_index=0;
			do_tricore_semihosting (cs);
			break;
		}
		}
}

static void tricore_cpu_disas_set_info(CPUState *cs, disassemble_info *info)
{
	TriCoreCPU *cpu = TRICORE_CPU(cs);
	CPUTriCoreState *env = &cpu->env;
	info->mach = bfd_arch_tricore;
	switch (env->features) {
	case TRICORE_FEATURE_13:
		info->flags = EF_EABI_TRICORE_V1_3;
		break;
	case TRICORE_FEATURE_131:
		info->flags = EF_EABI_TRICORE_V1_3_1;
		break;
	case TRICORE_FEATURE_16:
		info->flags = EF_EABI_TRICORE_V1_6;
		break;
	case TRICORE_FEATURE_161:
		info->flags = EF_EABI_TRICORE_V1_6_1;
		break;
	case TRICORE_FEATURE_162:
		info->flags = EF_EABI_TRICORE_V1_6_2;
		break;
	default:
		info->flags = EF_EABI_TRICORE_V1_6_2;
		break;
	}

    info->print_insn = print_insn_tricore;
}

static void tricore_cpu_class_init(ObjectClass *c, void *data)
{
    TriCoreCPUClass *mcc = TRICORE_CPU_CLASS(c);
    CPUClass *cc = CPU_CLASS(c);
    DeviceClass *dc = DEVICE_CLASS(c);

    device_class_set_parent_realize(dc, tricore_cpu_realizefn,
                                    &mcc->parent_realize);

    device_class_set_parent_reset(dc, tricore_cpu_reset, &mcc->parent_reset);
    cc->class_by_name = tricore_cpu_class_by_name;
    cc->has_work = tricore_cpu_has_work;
    cc->gdb_read_register = tricore_cpu_gdb_read_register;
    cc->gdb_write_register = tricore_cpu_gdb_write_register;
    cc->gdb_core_xml_file = "tricore-core.xml";
    cc->gdb_num_core_regs = 44;
    cc->gdb_arch_name = tricore_gdb_arch_name;
    cc->disas_set_info = tricore_cpu_disas_set_info;
    cc->dump_state = tricore_cpu_dump_state;
    cc->set_pc = tricore_cpu_set_pc;
    cc->sysemu_ops = &tricore_sysemu_ops;
    cc->tcg_ops = &tricore_tcg_ops;
    tricore_vio_init();
}

#define DEFINE_TRICORE_CPU_TYPE(cpu_model, initfn) \
    {                                              \
        .parent = TYPE_TRICORE_CPU,                \
        .instance_init = initfn,                   \
        .name = TRICORE_CPU_TYPE_NAME(cpu_model),  \
    }

static const TypeInfo tricore_cpu_type_infos[] = {
    {
        .name = TYPE_TRICORE_CPU,
        .parent = TYPE_CPU,
        .instance_size = sizeof(TriCoreCPU),
        .instance_init = tricore_cpu_initfn,
        .abstract = true,
        .class_size = sizeof(TriCoreCPUClass),
        .class_init = tricore_cpu_class_init,
    },
    /*added all cpus*/
    DEFINE_TRICORE_CPU_TYPE("tc1791", tc1791_initfn),
	  DEFINE_TRICORE_CPU_TYPE("tc1796", tc1796_initfn),
    DEFINE_TRICORE_CPU_TYPE("tc1797", tc1797_initfn),
    DEFINE_TRICORE_CPU_TYPE("tc27x", tc27x_initfn),
    DEFINE_TRICORE_CPU_TYPE("tc161", tc161_initfn),
    DEFINE_TRICORE_CPU_TYPE("tc162", tc162_initfn),
    DEFINE_TRICORE_CPU_TYPE("tc16", tc16_initfn),
    DEFINE_TRICORE_CPU_TYPE("tc131", tc131_initfn),
    DEFINE_TRICORE_CPU_TYPE("tc13", tc13_initfn),
};

DEFINE_TYPES(tricore_cpu_type_infos)
