/* Tricore opcode library for QEMU.
   Copyright (C) 2012-2016 Free Software Foundation, Inc.
   Contributed by Nigel Gray (ngray@altera.com).
   Contributed by Mentor Graphics, Inc.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA  02110-1301, USA.  */

/* This file resembles a concatenation of the following files from
   binutils.
   It has been derived from the original patches which have been
   relicensed by the contributors as GPL version 2 for inclusion
   in QEMU.  */

#ifndef _TRICORE_H_
#define _TRICORE_H_

#include "qemu/osdep.h"
#include "disas/dis-asm.h"

/* Instruction set architecture V1.1.  */
#define EF_TRICORE_V1_1	        0x00000001
#define EF_EABI_TRICORE_V1_1	0x80000000

/* Instruction set architecture V1.2.  */
#define EF_TRICORE_V1_2	        0x00000002
#define EF_EABI_TRICORE_V1_2	0x40000000

/* Instruction set architecture V1.3  */
#define EF_TRICORE_V1_3		0x00000004
#define EF_EABI_TRICORE_V1_3	0x20000000

/* Instruction set architecture V1.3.1  */

#define EF_TRICORE_V1_3_1	0x00000100
#define EF_EABI_TRICORE_V1_3_1	0x00800000

/* Instruction set architecture V1.6.  */

#define EF_TRICORE_V1_6		0x00000200
#define EF_EABI_TRICORE_V1_6	0x00400000

/* Instruction set architecture V1.6.1.  */

#define EF_TRICORE_V1_6_1	0x00000400
#define EF_EABI_TRICORE_V1_6_1	0x00200000

/* Instruction set architecture V1.6.2.  */

#define EF_TRICORE_V1_6_2	0x00000800
#define EF_EABI_TRICORE_V1_6_2	0x00100000

/* PCP co-processor.  */

#define EF_TRICORE_PCP		0x00000010
#define EF_EABI_TRICORE_PCP	0x01000000

/* PCP co-processor, version 2.  */

#define EF_TRICORE_PCP2		0x00000020
#define EF_EABI_TRICORE_PCP2	0x02000000

#define EF_TRICORE_CORE_MASK    	0x00000f0f
#define EF_EABI_TRICORE_CORE_MASK	0xf0f00000


#define SEC_PCP 0x10000000


typedef enum _tricore_opcode_arch_val
{
  TRICORE_GENERIC = 0x00000000,
  TRICORE_RIDER_A = 0x00000001,
#define TRICORE_V1_1    TRICORE_RIDER_A
  TRICORE_V1_2 	  = 0x00000002,
  TRICORE_V1_3    = 0x00000004,
  TRICORE_V1_3_1  = 0x00000100,
  TRICORE_V1_6    = 0x00000200,
  TRICORE_V1_6_1  = 0x00000400,
  TRICORE_V1_6_2  = 0x00000800,
  TRICORE_PCP     = 0x00000010,
  TRICORE_PCP2    = 0x00000020
} tricore_isa;
#define TRICORE_ISA_MASK        0x00000f0f

/* Some handy definitions for upward/downward compatibility of insns.  */

//#define TRICORE_V2_UP      TRICORE_V2
#define TRICORE_V1_6_2_UP (TRICORE_V1_6_2)
#define TRICORE_V1_6_1_UP (TRICORE_V1_6_1 | TRICORE_V1_6_2_UP)
#define TRICORE_V1_6_UP   (TRICORE_V1_6 | TRICORE_V1_6_1_UP)
#define TRICORE_V1_3_1_UP (TRICORE_V1_3_1 | TRICORE_V1_6_UP)
#define TRICORE_V1_3_UP   (TRICORE_V1_3 | TRICORE_V1_3_1_UP)
#define TRICORE_V1_2_UP   (TRICORE_V1_2 | TRICORE_V1_3_UP)

#define TRICORE_V1_2_DN    TRICORE_V1_2
#define TRICORE_V1_3_DN   (TRICORE_V1_3 | TRICORE_V1_2_DN )
#define TRICORE_V1_3_X_DN (TRICORE_V1_3 | TRICORE_V1_2_DN | TRICORE_V1_3_1)
#define TRICORE_V1_3_1_DN (TRICORE_V1_3_1 | TRICORE_V1_3_DN)
#define TRICORE_V1_6_DN   (TRICORE_V1_6 | TRICORE_V1_3_1_DN)
#define TRICORE_V1_6_1_DN (TRICORE_V1_6_1 | TRICORE_V1_6_DN)
#define TRICORE_V1_6_2_DN (TRICORE_V1_6_2 | TRICORE_V1_6_1_DN)

/* The various instruction formats of the TriCore architecture.  */

typedef enum _tricore_fmt
{
  /* 32-bit formats */

  TRICORE_FMT_ABS,
  TRICORE_FMT_ABSB,
  TRICORE_FMT_B,
  TRICORE_FMT_BIT,
  TRICORE_FMT_BO,
  TRICORE_FMT_BOL,
  TRICORE_FMT_BRC,
  TRICORE_FMT_BRN,
  TRICORE_FMT_BRR,
  TRICORE_FMT_RC,
  TRICORE_FMT_RCPW,
  TRICORE_FMT_RCR,
  TRICORE_FMT_RCRR,
  TRICORE_FMT_RCRW,
  TRICORE_FMT_RLC,
  TRICORE_FMT_RR,
  TRICORE_FMT_RR1,
  TRICORE_FMT_RR2,
  TRICORE_FMT_RRPW,
  TRICORE_FMT_RRR,
  TRICORE_FMT_RRR1,
  TRICORE_FMT_RRR2,
  TRICORE_FMT_RRRR,
  TRICORE_FMT_RRRW,
  TRICORE_FMT_SYS,

  /* 16-bit formats */

  TRICORE_FMT_SB,
  TRICORE_FMT_SBC,
  TRICORE_FMT_SBR,
  TRICORE_FMT_SBRN,
  TRICORE_FMT_SC,
  TRICORE_FMT_SLR,
  TRICORE_FMT_SLRO,
  TRICORE_FMT_SR,
  TRICORE_FMT_SRC,
  TRICORE_FMT_SRO,
  TRICORE_FMT_SRR,
  TRICORE_FMT_SRRS,
  TRICORE_FMT_SSR,
  TRICORE_FMT_SSRO,
  TRICORE_FMT_MAX /* Sentinel.  */
} tricore_fmt;

#if defined(__STDC__) || defined(ALMOST_STDC)
# define F(x) TRICORE_FMT_ ## x
#else
# define F(x) TRICORE_FMT_/**/x
#endif


/* Opcode masks for TriCore's various instruction formats.  */

unsigned long tricore_mask_abs;
unsigned long tricore_mask_absb;
unsigned long tricore_mask_b;
unsigned long tricore_mask_bit;
unsigned long tricore_mask_bo;
unsigned long tricore_mask_bol;
unsigned long tricore_mask_brc;
unsigned long tricore_mask_brn;
unsigned long tricore_mask_brr;
unsigned long tricore_mask_rc;
unsigned long tricore_mask_rcpw;
unsigned long tricore_mask_rcr;
unsigned long tricore_mask_rcrr;
unsigned long tricore_mask_rcrw;
unsigned long tricore_mask_rlc;
unsigned long tricore_mask_rr;
unsigned long tricore_mask_rr1;
unsigned long tricore_mask_rr2;
unsigned long tricore_mask_rrpw;
unsigned long tricore_mask_rrr;
unsigned long tricore_mask_rrr1;
unsigned long tricore_mask_rrr2;
unsigned long tricore_mask_rrrr;
unsigned long tricore_mask_rrrw;
unsigned long tricore_mask_sys;
unsigned long tricore_mask_sb;
unsigned long tricore_mask_sbc;
unsigned long tricore_mask_sbr;
unsigned long tricore_mask_sbrn;
unsigned long tricore_mask_sc;
unsigned long tricore_mask_slr;
unsigned long tricore_mask_slro;
unsigned long tricore_mask_sr;
unsigned long tricore_mask_src;
unsigned long tricore_mask_sro;
unsigned long tricore_mask_srr;
unsigned long tricore_mask_srrs;
unsigned long tricore_mask_ssr;
unsigned long tricore_mask_ssro;
unsigned long tricore_opmask[TRICORE_FMT_MAX];


/* This structure describes TriCore opcodes.  */

struct tricore_opcode
{
  const char *name;		/* The opcode's mnemonic name.  */
  const int len32;		/* 1 if it's a 32-bit insn.  */
  const unsigned long opcode;	/* The binary code of this opcode.  */
  const unsigned long lose;	/* Mask for bits that must not be set.  */
  const tricore_fmt format;	/* The instruction format.  */
  const int nr_operands;	/* The number of operands.  */
  const char *args;	/* Kinds of operands (see below).  */
  const char *fields;	/* Where to put the operands (see below).  */
  const tricore_isa isa;	/* Instruction set architecture.  */
  int insind;			/* The insn's index (computed at runtime).  */
  int inslast;			/* Index of last insn w/ that name (dito).  */
};

extern struct tricore_opcode tricore_opcodes[];
extern const int tricore_numopcodes;

/* This structure describes PCP/PCP2 opcodes.  */

struct pcp_opcode
{
  const char *name;		/* The opcode's mnemonic name.  */
  const int len32;		/* 1 if it's a 32-bit insn.  */
  const unsigned long opcode;	/* The binary code of this opcode.  */
  const unsigned long lose;	/* Mask for bits that must not be set.  */
  const int fmt_group;		/* The group ID of the instruction format.  */
  const int ooo;		/* 1 if operands may be given out of order.  */
  const int nr_operands;	/* The number of operands.  */
  const char *args;	/* Kinds of operands (see below),  */
  const tricore_isa isa;	/* PCP instruction set architecture.  */
  int insind;			/* The insn's index (computed at runtime).  */
  int inslast;			/* Index of last insn w/ that name (dito).  */
};

extern struct pcp_opcode pcp_opcodes[];
extern const int pcp_numopcodes;

/* This structure describes TriCore core registers (SFRs).  */

struct tricore_core_register
{
  const char *name;		/* The name of the register ($-prepended).  */
  const unsigned long addr;	/* The memory address of the register.  */
  const tricore_isa isa;	/* Instruction set architecture.  */
};

extern const struct tricore_core_register tricore_sfrs[];
extern const int tricore_numsfrs;

/* Kinds of operands for TriCore instructions:
   d  A simple data register (%d0-%d15).
   g  A simple data register with an 'l' suffix.
   G  A simple data register with an 'u' suffix.
   -  A simple data register with an 'll' suffix.
   +  A simple data register with an 'uu' suffix.
   l  A simple data register with an 'lu' suffix.
   L  A simple data register with an 'ul' suffix.
   D  An extended data register (d-register pair; %e0, %e2, ..., %e14).
   i  Implicit data register %d15.
   a  A simple address register (%a0-%a15).
   A  An extended address register (a-register pair; %a0, %a2, ..., %a14).
   I  Implicit address register %a15.
   P  Implicit stack register %a10.
   c  A core register ($psw, $pc etc.).
   1  A 1-bit zero-extended constant.
   2  A 2-bit zero-extended constant.
   3  A 3-bit zero-extended constant.
   4  A 4-bit sign-extended constant.
   f  A 4-bit zero-extended constant.
   5  A 5-bit zero-extended constant.
   F  A 5-bit sign-extended constant.
   v  A 5-bit zero-extended constant with bit 0 == 0 (=> 4bit/2).
   6  A 6-bit zero-extended constant with bits 0,1 == 0 (=> 4bit/4).
   8  A 8-bit zero-extended constant.
   9  A 9-bit sign-extended constant.
   n  A 9-bit zero-extended constant.
   h  A 10-bit zero-extended constant.
   k  A 10-bit zero-extended constant with bits 0,1 == 0 (=> 8bit/4).
   0  A 10-bit sign-extended constant.
   q  A 15-bit zero-extended constant.
   w  A 16-bit sign-extended constant.
   W  A 16-bit zero-extended constant.
   M  A 32-bit memory address.
   m  A 4-bit PC-relative offset (zero-extended, /2).
   r  A 4-bit PC-relative offset (one-extended, /2).
   x  A 5-bit PC-relative offset (zero-extended, /2).
   Z  A 5-bit PC-relative offset 0x1x (zero-extended, /2).
   R  A 8-bit PC-relative offset (sign-extended, /2).
   o  A 15-bit PC-relative offset (sign-extended, /2).
   O  A 24-bit PC-relative offset (sign-extended, /2).
   t  A 18-bit absolute memory address (segmented).
   T  A 24-bit absolute memory address (segmented, /2).
   V  A 18-bit absolute memory address (lower 14-bit zero).
   U  A symbol whose value isn't known yet.
   @  Register indirect ([%an]).
   &  SP indirect ([%sp] or [%a10]).
   <  Pre-incremented register indirect ([+%an]).
   >  Post-incremented register indirect ([%an+]).
   *  Circular address mode ([%An+c]).
   #  Bitreverse address mode ([%An+r]).
   ?  Indexed address mode ([%An+i]).
   S  Implicit base ([%a15]).
*/

/* The instruction fields where operands are stored.  */

#define FMT_ABS_NONE	        '0'
#define FMT_ABS_OFF18	        '1'     /* 18-bit absolute segmented address 0xf0003fff */
#define FMT_ABS_OFF18_14        '5'     /* 18-bit absolute address 0xffffc000 */
#define FMT_ABS_S1_D	        '2'
#define FMT_ABS_OFF18_MSK       0xf3fff000
#define FMT_ABS_S1_D_MSK        0x00000f00

#define FMT_ABSB_NONE	'0'
#define FMT_ABSB_OFF18	'1'
#define FMT_ABSB_B	'2'
#define FMT_ABSB_BPOS3	'3'
#define FMT_ABSB_OFF18_MSK      0xf3fff000
#define FMT_ABSB_B_MSK	        0x00000800
#define FMT_ABSB_BPOS3_MSK	0x00000700

#define FMT_B_NONE	'0'
#define FMT_B_DISP24	'1'
#define FMT_B_DISP24_MSK	0xffffff00

#define FMT_BIT_NONE	'0'
#define FMT_BIT_D	'1'
#define FMT_BIT_P2	'2'
#define FMT_BIT_P1	'3'
#define FMT_BIT_S2	'4'
#define FMT_BIT_S1	'5'
#define FMT_BIT_D_MSK	        0xf0000000
#define FMT_BIT_P2_MSK	        0x0f800000
#define FMT_BIT_P1_MSK	        0x001f0000
#define FMT_BIT_S2_MSK	        0x0000f000
#define FMT_BIT_S1_MSK	        0x00000f00

#define FMT_BO_NONE	'0'
#define FMT_BO_OFF10	'1'
#define FMT_BO_S2	'2'
#define FMT_BO_S1_D	'3'
#define FMT_BO_OFF10_MSK	0xf03f0000
#define FMT_BO_S2_MSK	        0x0000f000
#define FMT_BO_S1_D_MSK	        0x00000f00

#define FMT_BOL_NONE	'0'
#define FMT_BOL_OFF16	'1'
#define FMT_BOL_S2	'2'
#define FMT_BOL_S1_D	'3'
#define FMT_BOL_OFF16_MSK	0xffff0000
#define FMT_BOL_S2_MSK	        0x0000f000
#define FMT_BOL_S1_D_MSK	0x00000f00

#define FMT_BRC_NONE	'0'
#define FMT_BRC_DISP15	'1'
#define FMT_BRC_CONST4	'2'
#define FMT_BRC_S1	'3'
#define FMT_BRC_DISP15_MSK	0x7fff0000
#define FMT_BRC_CONST4_MSK	0x0000f000
#define FMT_BRC_S1_MSK	        0x00000f00

#define FMT_BRN_NONE	'0'
#define FMT_BRN_DISP15	'1'
#define FMT_BRN_N	'2'
#define FMT_BRN_S1	'3'
#define FMT_BRN_DISP15_MSK	0x7fff0000
#define FMT_BRN_N_MSK	        0x0000f080
#define FMT_BRN_S1_MSK	        0x00000f00

#define FMT_BRR_NONE	'0'
#define FMT_BRR_DISP15	'1'
#define FMT_BRR_S2	'2'
#define FMT_BRR_S1	'3'
#define FMT_BRR_DISP15_MSK	0x7fff0000
#define FMT_BRR_S2_MSK	        0x0000f000
#define FMT_BRR_S1_MSK	        0x00000f00

#define FMT_RC_NONE	'0'
#define FMT_RC_D	'1'
#define FMT_RC_CONST9	'2'
#define FMT_RC_S1	'3'
#define FMT_RC_CONST10	'4'
#define FMT_RC_D_MSK	        0xf0000000
#define FMT_RC_CONST9_MSK	0x001ff000
#define FMT_RC_S1_MSK	        0x00000f00
#define FMT_RC_CONST10_MSK	0x003ff000

#define FMT_RCPW_NONE	'0'
#define FMT_RCPW_D	'1'
#define FMT_RCPW_P	'2'
#define FMT_RCPW_W	'3'
#define FMT_RCPW_CONST4	'4'
#define FMT_RCPW_S1	'5'
#define FMT_RCPW_D_MSK	        0xf0000000
#define FMT_RCPW_P_MSK	        0x0f800000
#define FMT_RCPW_W_MSK	        0x001f0000
#define FMT_RCPW_CONST4_MSK	0x0000f000
#define FMT_RCPW_S1_MSK	        0x00000f00

#define FMT_RCR_NONE	'0'
#define FMT_RCR_D	'1'
#define FMT_RCR_S3	'2'
#define FMT_RCR_CONST9	'3'
#define FMT_RCR_S1	'4'
#define FMT_RCR_D_MSK	        0xf0000000
#define FMT_RCR_S3_MSK	        0x0f000000
#define FMT_RCR_CONST9_MSK	0x001ff000
#define FMT_RCR_S1_MSK	        0x00000f00

#define FMT_RCRR_NONE	'0'
#define FMT_RCRR_D	'1'
#define FMT_RCRR_S3	'2'
#define FMT_RCRR_CONST4	'3'
#define FMT_RCRR_S1	'4'
#define FMT_RCRR_D_MSK	        0xf0000000
#define FMT_RCRR_S3_MSK	        0x0f000000
#define FMT_RCRR_CONST4_MSK	0x0000f000
#define FMT_RCRR_S1_MSK	        0x00000f00

#define FMT_RCRW_NONE	'0'
#define FMT_RCRW_D	'1'
#define FMT_RCRW_S3	'2'
#define FMT_RCRW_W	'3'
#define FMT_RCRW_CONST4	'4'
#define FMT_RCRW_S1	'5'
#define FMT_RCRW_D_MSK	        0xf0000000
#define FMT_RCRW_S3_MSK	        0x0f000000
#define FMT_RCRW_W_MSK	        0x001f0000
#define FMT_RCRW_CONST4_MSK	0x0000f000
#define FMT_RCRW_S1_MSK	        0x00000f00

#define FMT_RLC_NONE	'0'
#define FMT_RLC_D	'1'
#define FMT_RLC_CONST16	'2'
#define FMT_RLC_S1	'3'
#define FMT_RLC_D_MSK	        0xf0000000
#define FMT_RLC_CONST16_MSK	0x0ffff000
#define FMT_RLC_S1_MSK	        0x00000f00

#define FMT_RR_NONE	'0'
#define FMT_RR_D	'1'
#define FMT_RR_N	'2'
#define FMT_RR_S2	'3'
#define FMT_RR_S1	'4'
#define FMT_RR_D_S1	'5'
#define FMT_RR_D_MSK	        0xf0000000
#define FMT_RR_N_MSK	        0x00030000
#define FMT_RR_S2_MSK	        0x0000f000
#define FMT_RR_S1_MSK	        0x00000f00
#define FMT_RR_D_S1_MSK	        0xf0000f00

#define FMT_RR1_NONE	'0'
#define FMT_RR1_D	'1'
#define FMT_RR1_N	'2'
#define FMT_RR1_S2	'3'
#define FMT_RR1_S1	'4'
#define FMT_RR1_D_MSK	        0xf0000000
#define FMT_RR1_N_MSK	        0x00030000
#define FMT_RR1_S2_MSK	        0x0000f000
#define FMT_RR1_S1_MSK	        0x00000f00

#define FMT_RR2_NONE	'0'
#define FMT_RR2_D	'1'
#define FMT_RR2_S2	'2'
#define FMT_RR2_S1	'3'
#define FMT_RR2_D_MSK	        0xf0000000
#define FMT_RR2_S2_MSK	        0x0000f000
#define FMT_RR2_S1_MSK	        0x00000f00

#define FMT_RRPW_NONE	'0'
#define FMT_RRPW_D	'1'
#define FMT_RRPW_P	'2'
#define FMT_RRPW_W	'3'
#define FMT_RRPW_S2	'4'
#define FMT_RRPW_S1	'5'
#define FMT_RRPW_D_MSK	        0xf0000000
#define FMT_RRPW_P_MSK	        0x0f800000
#define FMT_RRPW_W_MSK	        0x001f0000
#define FMT_RRPW_S2_MSK	        0x0000f000
#define FMT_RRPW_S1_MSK	        0x00000f00

#define FMT_RRR_NONE	'0'
#define FMT_RRR_D	'1'
#define FMT_RRR_S3	'2'
#define FMT_RRR_N	'3'
#define FMT_RRR_S2	'4'
#define FMT_RRR_S1	'5'
#define FMT_RRR_D_MSK	        0xf0000000
#define FMT_RRR_S3_MSK	        0x0f000000
#define FMT_RRR_N_MSK	        0x00030000
#define FMT_RRR_S2_MSK	        0x0000f000
#define FMT_RRR_S1_MSK	        0x00000f00

#define FMT_RRR1_NONE	'0'
#define FMT_RRR1_D	'1'
#define FMT_RRR1_S3	'2'
#define FMT_RRR1_N	'3'
#define FMT_RRR1_S2	'4'
#define FMT_RRR1_S1	'5'
#define FMT_RRR1_D_MSK	        0xf0000000
#define FMT_RRR1_S3_MSK	        0x0f000000
#define FMT_RRR1_N_MSK	        0x00030000
#define FMT_RRR1_S2_MSK	        0x0000f000
#define FMT_RRR1_S1_MSK	        0x00000f00

#define FMT_RRR2_NONE	'0'
#define FMT_RRR2_D	'1'
#define FMT_RRR2_S3	'2'
#define FMT_RRR2_S2	'3'
#define FMT_RRR2_S1	'4'
#define FMT_RRR2_D_MSK	        0xf0000000
#define FMT_RRR2_S3_MSK	        0x0f000000
#define FMT_RRR2_S2_MSK	        0x0000f000
#define FMT_RRR2_S1_MSK	        0x00000f00

#define FMT_RRRR_NONE	'0'
#define FMT_RRRR_D	'1'
#define FMT_RRRR_S3	'2'
#define FMT_RRRR_S2	'3'
#define FMT_RRRR_S1	'4'
#define FMT_RRRR_D_MSK	        0xf0000000
#define FMT_RRRR_S3_MSK	        0x0f000000
#define FMT_RRRR_S2_MSK	        0x0000f000
#define FMT_RRRR_S1_MSK	        0x00000f00

#define FMT_RRRW_NONE	'0'
#define FMT_RRRW_D	'1'
#define FMT_RRRW_S3	'2'
#define FMT_RRRW_W	'3'
#define FMT_RRRW_S2	'4'
#define FMT_RRRW_S1	'5'
#define FMT_RRRW_D_MSK	        0xf0000000
#define FMT_RRRW_S3_MSK	        0x0f000000
#define FMT_RRRW_W_MSK	        0x001f0000
#define FMT_RRRW_S2_MSK	        0x0000f000
#define FMT_RRRW_S1_MSK	        0x00000f00

#define FMT_SYS_NONE	'0'
#define FMT_SYS_S1_D	'1'
#define FMT_SYS_S1_D_MSK	0x00000f00

#define FMT_SB_NONE	'0'
#define FMT_SB_DISP8	'1'
#define FMT_SB_DISP8_MSK	0xff00

#define FMT_SBC_NONE	'0'
#define FMT_SBC_CONST4	'1'
#define FMT_SBC_DISP4	'2'
#define FMT_SBC_CONST4_MSK	0xf000
#define FMT_SBC_DISP4_MSK	0x0f00

#define FMT_SBR_NONE	'0'
#define FMT_SBR_S2	'1'
#define FMT_SBR_DISP4	'2'
#define FMT_SBR_S2_MSK	        0xf000
#define FMT_SBR_DISP4_MSK	0x0f00

#define FMT_SBRN_NONE	'0'
#define FMT_SBRN_N	'1'
#define FMT_SBRN_DISP4	'2'
#define FMT_SBRN_N_MSK	        0xf000
#define FMT_SBRN_DISP4_MSK	0x0f00

#define FMT_SC_NONE	'0'
#define FMT_SC_CONST8	'1'
#define FMT_SC_CONST8_MSK	0xff00

#define FMT_SLR_NONE	'0'
#define FMT_SLR_S2	'1'
#define FMT_SLR_D	'2'
#define FMT_SLR_S2_MSK	        0xf000
#define FMT_SLR_D_MSK	        0x0f00

#define FMT_SLRO_NONE	'0'
#define FMT_SLRO_OFF4	'1'
#define FMT_SLRO_D	'2'
#define FMT_SLRO_OFF4_MSK	0xf000
#define FMT_SLRO_D_MSK	        0x0f00

#define FMT_SR_NONE	'0'
#define FMT_SR_S1_D	'1'
#define FMT_SR_S1_D_MSK	        0x0f00

#define FMT_SRC_NONE	'0'
#define FMT_SRC_CONST4	'1'
#define FMT_SRC_S1_D	'2'
#define FMT_SRC_CONST4_MSK	0xf000
#define FMT_SRC_S1_D_MSK        0x0f00

#define FMT_SRO_NONE	'0'
#define FMT_SRO_S2	'1'
#define FMT_SRO_OFF4	'2'
#define FMT_SRO_S2_MSK	        0xf000
#define FMT_SRO_OFF4_MSK	0x0f00

#define FMT_SRR_NONE	'0'
#define FMT_SRR_S2	'1'
#define FMT_SRR_S1_D	'2'
#define FMT_SRR_S2_MSK	        0xf000
#define FMT_SRR_S1_D_MSK	0x0f00

#define FMT_SRRS_NONE	'0'
#define FMT_SRRS_S2	'1'
#define FMT_SRRS_S1_D	'2'
#define FMT_SRRS_N	'3'
#define FMT_SRRS_S2_MSK	        0xf000
#define FMT_SRRS_S1_D_MSK	0x0f00
#define FMT_SRRS_N_MSK	        0x00c0

#define FMT_SSR_NONE	'0'
#define FMT_SSR_S2	'1'
#define FMT_SSR_S1	'2'
#define FMT_SSR_S2_MSK	        0xf000
#define FMT_SSR_S1_MSK	        0x0f00

#define FMT_SSRO_NONE	'0'
#define FMT_SSRO_OFF4	'1'
#define FMT_SSRO_S1	'2'
#define FMT_SSRO_OFF4_MSK	0xf000
#define FMT_SSRO_S1_MSK	        0x0f00

/* Kinds of operands for PCP instructions:
   a  Condition code 0-7 (CONDCA).
   b  Condition code 8-15 (CONDCB).
   c  CNC=[0,1,2].
   d  DST{+,-}.
   e  A constant expression.
   E  An indirect constant expression.
   f  SIZE=[8,16,32].
   g  ST=[0,1].
   h  EC=[0,1].
   i  INT=[0,1].
   j  EP=[0,1].
   k  SET (const value 1).
   l  CLR (const value 0).
   m  DAC=[0,1].
   n  CNT0=[1..8] for COPY, or [2,4,8] for BCOPY.
   o  RTA=[0,1].
   p  EDA=[0,1].
   q  SDB=[0,1].
   r  A direct register (R0-R7).
   R  An indirect register ([R0]-[R7]).
   s  SRC{+,-}.
   u  A direct symbol whose value isn't known yet.
   U  An indirect symbol whose value isn't known yet.
*/

#endif /* _TRICORE_H */

/* The TriCore has a number of special function registers, which are
   described below.  Their actual address is some implementation
   specific base address, plus their 16-bit offset.  */

const struct tricore_core_register tricore_sfrs[] =
{
  {"$mmucon",	0x8000, TRICORE_V1_3_UP},
  {"$mmu_con",	0x8000, TRICORE_V1_3_UP},
  {"$asi",	0x8004, TRICORE_V1_3_UP},
  {"$mmu_asi",	0x8004, TRICORE_V1_3_UP},
  {"$mmuid",	0x8008, TRICORE_V1_3_UP},
  {"$mmu_id",	0x8008, TRICORE_V1_3_UP},
  {"$tva",	0x800c, TRICORE_V1_3_UP},
  {"$mmu_tva",	0x800c, TRICORE_V1_3_UP},
  {"$tpa",	0x8010, TRICORE_V1_3_UP},
  {"$mmu_tpa",	0x8010, TRICORE_V1_3_UP},
  {"$tpx",	0x8014, TRICORE_V1_3_UP},
  {"$mmu_tpx",	0x8014, TRICORE_V1_3_UP},
  {"$tfa",	0x8018, TRICORE_V1_3_UP},
  {"$mmu_tfa",	0x8018, TRICORE_V1_3_UP},


  {"$pma0",     0x801c, TRICORE_V1_6_UP },
  {"$mmu_tfas", 0x8020, TRICORE_V1_6_UP },

  {"$dcon2",    0x9000, TRICORE_V1_6_UP },
  {"$bmacon", 	0x9004, TRICORE_V1_3_1_UP },
  {"$dcon1",    0x9008, TRICORE_V1_6_UP },
  {"$smacon", 	0x900c, TRICORE_V1_6_UP },
  {"$dstr",     0x9010, TRICORE_V1_6_UP },
  {"$datr",     0x9018, TRICORE_V1_6_UP },
  {"$deadd",    0x901c, TRICORE_V1_6_UP },
  {"$diear", 	0x9020, TRICORE_V1_3_1_UP },
  {"$dietr", 	0x9024, TRICORE_V1_3_1_UP },
  {"$ccdier", 	0x9028, TRICORE_V1_3_1_UP },
  {"$smacon", 	0x9040, TRICORE_V1_3_1},
  {"$dcon0",    0x9040, TRICORE_V1_6_UP },
  {"$miecon", 	0x9044, TRICORE_V1_3_1_UP },
  {"$pstr", 	0x9200, TRICORE_V1_6_UP },
  {"$pcon1", 	0x9204, TRICORE_V1_6_UP },
  {"$pcon2", 	0x9208, TRICORE_V1_6_UP },
  {"$pcon0", 	0x920c, TRICORE_V1_6_UP },
  {"$piear", 	0x9210, TRICORE_V1_3_1_UP },
  {"$pietr", 	0x9214, TRICORE_V1_3_1_UP },
  {"$ccpier", 	0x9218, TRICORE_V1_3_1|TRICORE_V1_6 },
  {"$compat", 	0x9400, TRICORE_V1_3_1_UP },

  {"$fpu_trap_con", 	0xa000, TRICORE_V1_3_1_UP},
  {"$fpu_trap_pc", 	0xa004, TRICORE_V1_3_1_UP},
  {"$fpu_trap_opc", 	0xa008, TRICORE_V1_3_1_UP},
  {"$fpu_trap_src1", 	0xa010, TRICORE_V1_3_1_UP},
  {"$fpu_trap_src2", 	0xa014, TRICORE_V1_3_1_UP},
  {"$fpu_trap_src3", 	0xa018, TRICORE_V1_3_1_UP},
  {"$fpu_id", 	        0xa020, TRICORE_V1_3_1},

  /* Protection Registers */
  {"$dpr0_0l",	0xc000, TRICORE_V1_6_DN},
  {"$dpr0_0u",	0xc004, TRICORE_V1_6_DN},
  {"$dpr0_1l",	0xc008, TRICORE_V1_6_DN},
  {"$dpr0_1u",	0xc00c, TRICORE_V1_6_DN},
  {"$dpr0_2l",	0xc010, TRICORE_V1_6_DN},
  {"$dpr0_2u",	0xc014, TRICORE_V1_6_DN},
  {"$dpr0_3l",	0xc018, TRICORE_V1_6_DN},
  {"$dpr0_3u",	0xc01c, TRICORE_V1_6_DN},

  {"$dpr1_0l",	0xc400, TRICORE_V1_6_DN},
  {"$dpr1_0u",	0xc404, TRICORE_V1_6_DN},
  {"$dpr1_1l",	0xc408, TRICORE_V1_6_DN},
  {"$dpr1_1u",	0xc40c, TRICORE_V1_6_DN},
  {"$dpr1_2l",	0xc410, TRICORE_V1_6_DN},
  {"$dpr1_2u",	0xc414, TRICORE_V1_6_DN},
  {"$dpr1_3l",	0xc418, TRICORE_V1_6_DN},
  {"$dpr1_3u",	0xc41c, TRICORE_V1_6_DN},

  {"$dpr2_0l",	0xc800, TRICORE_V1_6_DN},
  {"$dpr2_0u",	0xc804, TRICORE_V1_6_DN},
  {"$dpr2_1l",	0xc808, TRICORE_V1_6_DN},
  {"$dpr2_1u",	0xc80c, TRICORE_V1_6_DN},
  {"$dpr2_2l",	0xc810, TRICORE_V1_6_DN},
  {"$dpr2_2u",	0xc814, TRICORE_V1_6_DN},
  {"$dpr2_3l",	0xc818, TRICORE_V1_6_DN},
  {"$dpr2_3u",	0xc81c, TRICORE_V1_6_DN},

  {"$dpr3_0l",	0xcc00, TRICORE_V1_6_DN},
  {"$dpr3_0u",	0xcc04, TRICORE_V1_6_DN},
  {"$dpr3_1l",	0xcc08, TRICORE_V1_6_DN},
  {"$dpr3_1u",	0xcc0c, TRICORE_V1_6_DN},
  {"$dpr3_2l",	0xcc10, TRICORE_V1_6_DN},
  {"$dpr3_2u",	0xcc14, TRICORE_V1_6_DN},
  {"$dpr3_3l",	0xcc18, TRICORE_V1_6_DN},
  {"$dpr3_3u",	0xcc1c, TRICORE_V1_6_DN},

  {"$cpr0_0l",	0xd000, TRICORE_V1_6_DN},
  {"$cpr0_0u",	0xd004, TRICORE_V1_6_DN},
  {"$cpr0_1l",	0xd008, TRICORE_V1_6_DN},
  {"$cpr0_1u",	0xd00c, TRICORE_V1_6_DN},
  {"$cpr0_2l",	0xd010, TRICORE_V1_6_DN},
  {"$cpr0_2u",	0xd014, TRICORE_V1_6_DN},
  {"$cpr0_3l",	0xd018, TRICORE_V1_6_DN},
  {"$cpr0_3u",	0xd01c, TRICORE_V1_6_DN},

  {"$cpr1_0l",	0xd400, TRICORE_V1_6_DN},
  {"$cpr1_0u",	0xd404, TRICORE_V1_6_DN},
  {"$cpr1_1l",	0xd408, TRICORE_V1_6_DN},
  {"$cpr1_1u",	0xd40c, TRICORE_V1_6_DN},
  {"$cpr1_2l",	0xd410, TRICORE_V1_6_DN},
  {"$cpr1_2u",	0xd414, TRICORE_V1_6_DN},
  {"$cpr1_3l",	0xd418, TRICORE_V1_6_DN},
  {"$cpr1_3u",	0xd41c, TRICORE_V1_6_DN},

  {"$cpr2_0l",	0xd800, TRICORE_V1_6_DN},
  {"$cpr2_0u",	0xd804, TRICORE_V1_6_DN},
  {"$cpr2_1l",	0xd808, TRICORE_V1_6_DN},
  {"$cpr2_1u",	0xd80c, TRICORE_V1_6_DN},
  {"$cpr2_2l",	0xd810, TRICORE_V1_6_DN},
  {"$cpr2_2u",	0xd814, TRICORE_V1_6_DN},
  {"$cpr2_3l",	0xd818, TRICORE_V1_6_DN},
  {"$cpr2_3u",	0xd81c, TRICORE_V1_6_DN},

  {"$cpr3_0l",	0xdc00, TRICORE_V1_6_DN},
  {"$cpr3_0u",	0xdc04, TRICORE_V1_6_DN},
  {"$cpr3_1l",	0xdc08, TRICORE_V1_6_DN},
  {"$cpr3_1u",	0xdc0c, TRICORE_V1_6_DN},
  {"$cpr3_2l",	0xdc10, TRICORE_V1_6_DN},
  {"$cpr3_2u",	0xdc14, TRICORE_V1_6_DN},
  {"$cpr3_3l",	0xdc18, TRICORE_V1_6_DN},
  {"$cpr3_3u",	0xdc1c, TRICORE_V1_6_DN},

  {"$dpm0_0",	0xe000, TRICORE_V1_3_1_DN},
  {"$dpm0_1",	0xe001, TRICORE_V1_3_1_DN},
  {"$dpm0_2",	0xe002, TRICORE_V1_3_1_DN},
  {"$dpm0_3",	0xe003, TRICORE_V1_3_1_DN},

  {"$dpm1_0",	0xe080, TRICORE_V1_3_1_DN},
  {"$dpm1_1",	0xe081, TRICORE_V1_3_1_DN},
  {"$dpm1_2",	0xe082, TRICORE_V1_3_1_DN},
  {"$dpm1_3",	0xe083, TRICORE_V1_3_1_DN},

  {"$dpm0",	0xe000, TRICORE_V1_6},
  {"$dpm1",	0xe080, TRICORE_V1_6},
  {"$dpm2",	0xe100, TRICORE_V1_6},
  {"$dpm3",	0xe180, TRICORE_V1_6},

  {"$cpm0_0",	0xe200, TRICORE_V1_3_1_DN},
  {"$cpm0_1",	0xe201, TRICORE_V1_3_1_DN},

  {"$cpm1_0",	0xe280, TRICORE_V1_3_1_DN},
  {"$cpm1_1",	0xe281, TRICORE_V1_3_1_DN},

  {"$cpm0",	0xe200, TRICORE_V1_6},
  {"$cpm1",	0xe280, TRICORE_V1_6},
  {"$cpm2",	0xe300, TRICORE_V1_6},
  {"$cpm3",	0xe380, TRICORE_V1_6},

  {"$dpr0_l",	0xc000, TRICORE_V1_6_1_UP},
  {"$dpr0_u",	0xc004, TRICORE_V1_6_1_UP},
  {"$dpr1_l",	0xc008, TRICORE_V1_6_1_UP},
  {"$dpr1_u",	0xc00c, TRICORE_V1_6_1_UP},
  {"$dpr2_l",	0xc010, TRICORE_V1_6_1_UP},
  {"$dpr2_u",	0xc014, TRICORE_V1_6_1_UP},
  {"$dpr3_l",	0xc018, TRICORE_V1_6_1_UP},
  {"$dpr3_u",	0xc01c, TRICORE_V1_6_1_UP},
  {"$dpr4_l",	0xc020, TRICORE_V1_6_1_UP},
  {"$dpr4_u",	0xc024, TRICORE_V1_6_1_UP},
  {"$dpr5_l",	0xc028, TRICORE_V1_6_1_UP},
  {"$dpr5_u",	0xc02c, TRICORE_V1_6_1_UP},
  {"$dpr6_l",	0xc030, TRICORE_V1_6_1_UP},
  {"$dpr6_u",	0xc034, TRICORE_V1_6_1_UP},
  {"$dpr7_l",	0xc038, TRICORE_V1_6_1_UP},
  {"$dpr7_u",	0xc03c, TRICORE_V1_6_1_UP},
  {"$dpr8_l",	0xc040, TRICORE_V1_6_1_UP},
  {"$dpr8_u",	0xc044, TRICORE_V1_6_1_UP},
  {"$dpr9_l",	0xc048, TRICORE_V1_6_1_UP},
  {"$dpr9_u",	0xc04c, TRICORE_V1_6_1_UP},
  {"$dpr10_l",	0xc050, TRICORE_V1_6_1_UP},
  {"$dpr10_u",	0xc054, TRICORE_V1_6_1_UP},
  {"$dpr11_l",	0xc058, TRICORE_V1_6_1_UP},
  {"$dpr11_u",	0xc05c, TRICORE_V1_6_1_UP},
  {"$dpr12_l",	0xc060, TRICORE_V1_6_1_UP},
  {"$dpr12_u",	0xc064, TRICORE_V1_6_1_UP},
  {"$dpr13_l",	0xc068, TRICORE_V1_6_1_UP},
  {"$dpr13_u",	0xc06c, TRICORE_V1_6_1_UP},
  {"$dpr14_l",	0xc070, TRICORE_V1_6_1_UP},
  {"$dpr14_u",	0xc074, TRICORE_V1_6_1_UP},
  {"$dpr15_l",	0xc078, TRICORE_V1_6_1_UP},
  {"$dpr15_u",	0xc07c, TRICORE_V1_6_1_UP},

  {"$cpr0_l",	0xd000, TRICORE_V1_6_1_UP},
  {"$cpr0_u",	0xd004, TRICORE_V1_6_1_UP},
  {"$cpr1_l",	0xd008, TRICORE_V1_6_1_UP},
  {"$cpr1_u",	0xd00c, TRICORE_V1_6_1_UP},
  {"$cpr2_l",	0xd010, TRICORE_V1_6_1_UP},
  {"$cpr2_u",	0xd014, TRICORE_V1_6_1_UP},
  {"$cpr3_l",	0xd018, TRICORE_V1_6_1_UP},
  {"$cpr3_u",	0xd01c, TRICORE_V1_6_1_UP},
  {"$cpr4_l",	0xd020, TRICORE_V1_6_1_UP},
  {"$cpr4_u",	0xd024, TRICORE_V1_6_1_UP},
  {"$cpr5_l",	0xd028, TRICORE_V1_6_1_UP},
  {"$cpr5_u",	0xd02c, TRICORE_V1_6_1_UP},
  {"$cpr6_l",	0xd030, TRICORE_V1_6_1_UP},
  {"$cpr6_u",	0xd034, TRICORE_V1_6_1_UP},
  {"$cpr7_l",	0xd038, TRICORE_V1_6_1_UP},
  {"$cpr7_u",	0xd03c, TRICORE_V1_6_1_UP},
  {"$cpr8_l",	0xd040, TRICORE_V1_6_1_UP},
  {"$cpr8_u",	0xd044, TRICORE_V1_6_1_UP},
  {"$cpr9_l",	0xd048, TRICORE_V1_6_1_UP},
  {"$cpr9_u",	0xd04c, TRICORE_V1_6_1_UP},
  {"$cpr10_l",	0xd050, TRICORE_V1_6_1_UP},
  {"$cpr10_u",	0xd054, TRICORE_V1_6_1_UP},
  {"$cpr11_l",	0xd058, TRICORE_V1_6_1_UP},
  {"$cpr11_u",	0xd05c, TRICORE_V1_6_1_UP},
  {"$cpr12_l",	0xd060, TRICORE_V1_6_1_UP},
  {"$cpr12_u",	0xd064, TRICORE_V1_6_1_UP},
  {"$cpr13_l",	0xd068, TRICORE_V1_6_1_UP},
  {"$cpr13_u",	0xd06c, TRICORE_V1_6_1_UP},
  {"$cpr14_l",	0xd070, TRICORE_V1_6_1_UP},
  {"$cpr14_u",	0xd074, TRICORE_V1_6_1_UP},
  {"$cpr15_l",	0xd078, TRICORE_V1_6_1_UP},
  {"$cpr15_u",	0xd07c, TRICORE_V1_6_1_UP},

  {"$cpxe_0",	0xe000, TRICORE_V1_6_1_UP},
  {"$cpxe_1",	0xe004, TRICORE_V1_6_1_UP},
  {"$cpxe_2",	0xe008, TRICORE_V1_6_1_UP},
  {"$cpxe_3",	0xe00c, TRICORE_V1_6_1_UP},

  {"$cpxe_4",	0xe040, TRICORE_V1_6_2_UP},
  {"$cpxe_5",	0xe044, TRICORE_V1_6_2_UP},
  {"$cpxe_6",	0xe048, TRICORE_V1_6_2_UP},
  {"$cpxe_7",	0xe04c, TRICORE_V1_6_2_UP},

  {"$dpre_0",	0xe010, TRICORE_V1_6_1_UP},
  {"$dpre_1",	0xe014, TRICORE_V1_6_1_UP},
  {"$dpre_2",	0xe018, TRICORE_V1_6_1_UP},
  {"$dpre_3",	0xe01c, TRICORE_V1_6_1_UP},

  {"$dpre_4",	0xe050, TRICORE_V1_6_2_UP},
  {"$dpre_5",	0xe054, TRICORE_V1_6_2_UP},
  {"$dpre_6",	0xe058, TRICORE_V1_6_2_UP},
  {"$dpre_7",	0xe05c, TRICORE_V1_6_2_UP},

  {"$dpwe_0",	0xe020, TRICORE_V1_6_1_UP},
  {"$dpwe_1",	0xe024, TRICORE_V1_6_1_UP},
  {"$dpwe_2",	0xe028, TRICORE_V1_6_1_UP},
  {"$dpwe_3",	0xe02c, TRICORE_V1_6_1_UP},

  {"$dpwe_4",	0xe060, TRICORE_V1_6_2_UP},
  {"$dpwe_5",	0xe064, TRICORE_V1_6_2_UP},
  {"$dpwe_6",	0xe068, TRICORE_V1_6_2_UP},
  {"$dpwe_7",	0xe06c, TRICORE_V1_6_2_UP},

  {"$tps_con",	0xe400, TRICORE_V1_6_1_UP},
  {"$tps_timer0",0xe404, TRICORE_V1_6_1_UP},
  {"$tps_timer1",0xe408, TRICORE_V1_6_1_UP},
  {"$tps_timer2",0xe40c, TRICORE_V1_6_1_UP},

  {"$tps_extim_entry_cval", 0xe440, TRICORE_V1_6_2_UP},
  {"$tps_extim_entry_lval", 0xe444, TRICORE_V1_6_2_UP},
  {"$tps_extim_exit_cval",  0xe448, TRICORE_V1_6_2_UP},
  {"$tps_extim_exit_lval",  0xe44c, TRICORE_V1_6_2_UP},
  {"$tps_extim_class_en",   0xe450, TRICORE_V1_6_2_UP},
  {"$tps_extim_stat",       0xe454, TRICORE_V1_6_2_UP},
  {"$tps_extim_fcx",        0xe458, TRICORE_V1_6_2_UP},

  {"$dbgsr",	0xfd00, TRICORE_GENERIC},
  {"$gprwb",	0xfd04, TRICORE_GENERIC},
  {"$exevt",	0xfd08, TRICORE_GENERIC},
  {"$crevt",	0xfd0c, TRICORE_GENERIC},
  {"$swevt",	0xfd10, TRICORE_GENERIC},
  {"$tr0evt",	0xfd20, TRICORE_GENERIC},
  {"$tr1evt",	0xfd24, TRICORE_GENERIC},

  {"$pcxi",		0xfe00, TRICORE_GENERIC},
  {"$psw",		0xfe04, TRICORE_GENERIC},
  {"$pc",		0xfe08, TRICORE_GENERIC},
  {"$dbiten",	0xfe0c, TRICORE_RIDER_A},
  {"$syscon",	0xfe14, TRICORE_GENERIC},
  {"$cpuid",	0xfe18, TRICORE_V1_2_UP},
  {"$cpu_id",	0xfe18, TRICORE_V1_2_UP},
  {"$core_id",	0xfe1c, TRICORE_V1_6_1_UP},
  {"$biv",		0xfe20, TRICORE_GENERIC},
  {"$btv",		0xfe24, TRICORE_GENERIC},
  {"$isp",		0xfe28, TRICORE_GENERIC},
  {"$icr",		0xfe2c, TRICORE_GENERIC},
  {"$fcx",		0xfe38, TRICORE_GENERIC},
  {"$lcx",		0xfe3c, TRICORE_GENERIC},

  /* These are not core SFRs, but they can be accessed using the
     18-bit absolute address mode.  */

  {"$pwrclc",	  0xf0000000, TRICORE_V1_2_DN},
  {"$pwrid",	  0xf0000008, TRICORE_V1_2_DN},
  {"$rstreq",	  0xf0000010, TRICORE_V1_2_DN},
  {"$rstsr",	  0xf0000014, TRICORE_V1_2_DN},

  {"$wdtcon0",	 0xf0000020, TRICORE_V1_3_DN},
  {"$wdtcon1",	 0xf0000024, TRICORE_V1_3_DN},
  {"$wdtsr",	 0xf0000028, TRICORE_V1_3_DN},

  {"$wdtcon0",	0xf00005f0, TRICORE_V1_3_1 | TRICORE_V1_6 },
  {"$wdtcon1",	0xf00005f4, TRICORE_V1_3_1 | TRICORE_V1_6 },
  {"$wdtsr",	0xf00005f8, TRICORE_V1_3_1 | TRICORE_V1_6 },

  {"$stmclc",	0xf0000200, TRICORE_V1_3 | TRICORE_V1_3_1 | TRICORE_V1_6 },
  {"$stmid",	0xf0000208, TRICORE_V1_3 | TRICORE_V1_3_1 | TRICORE_V1_6 },
  {"$systim0",	0xf0000210, TRICORE_V1_3 | TRICORE_V1_3_1 | TRICORE_V1_6 },
  {"$systim1",	0xf0000214, TRICORE_V1_3 | TRICORE_V1_3_1 | TRICORE_V1_6 },
  {"$systim2",	0xf0000218, TRICORE_V1_3 | TRICORE_V1_3_1 | TRICORE_V1_6 },
  {"$systim3",	0xf000021c, TRICORE_V1_3 | TRICORE_V1_3_1 | TRICORE_V1_6 },
  {"$systim4",	0xf0000220, TRICORE_V1_3 | TRICORE_V1_3_1 | TRICORE_V1_6 },
  {"$systim5",	0xf0000224, TRICORE_V1_3 | TRICORE_V1_3_1 | TRICORE_V1_6 },
  {"$systim6",	0xf0000228, TRICORE_V1_3 | TRICORE_V1_3_1 | TRICORE_V1_6 },


  {"$nmisr",	0xf000002c, TRICORE_V1_2_DN},
  {"$pmcon",	0xf0000030, TRICORE_V1_2_DN},
  {"$pmcsr",	0xf0000034, TRICORE_V1_2_DN},
  {"$pllclc",	0xf0000040, TRICORE_V1_2_DN},
  {"$eckclc",	0xf0000044, TRICORE_V1_2_DN},
  {"$icuclc",	0xf0000048, TRICORE_V1_2_DN},

  {"$stmclc",	0xf0000300, TRICORE_V1_2_DN},
  {"$stmid",	0xf0000308, TRICORE_V1_2_DN},
  {"$systim0",	0xf0000320, TRICORE_V1_2_DN},
  {"$systim1",	0xf0000324, TRICORE_V1_2_DN},
  {"$systim2",	0xf0000328, TRICORE_V1_2_DN},
  {"$systim3",	0xf000032c, TRICORE_V1_2_DN},
  {"$systim4",	0xf0000330, TRICORE_V1_2_DN},
  {"$systim5",	0xf0000334, TRICORE_V1_2_DN},
  {"$systim6",	0xf0000338, TRICORE_V1_2_DN},
  {"$systim7",	0xf000033c, TRICORE_V1_2_DN},

  {"$jdpid",	0xf0000408, TRICORE_V1_2_DN},
  {"$comdata",	0xf0000468, TRICORE_V1_2_DN},
  {"$iosr",		0xf000046c, TRICORE_V1_2_DN},

  {"$ebucon",	0xf0000510, TRICORE_V1_2_DN},
  {"$drmcon",	0xf0000514, TRICORE_V1_2_DN},
  {"$drmstat",	0xf0000518, TRICORE_V1_2_DN},
  {"$addsel0",	0xf0000520, TRICORE_V1_2_DN},
  {"$addsel1",	0xf0000524, TRICORE_V1_2_DN},
  {"$addsel2",	0xf0000528, TRICORE_V1_2_DN},
  {"$addsel3",	0xf000052c, TRICORE_V1_2_DN},
  {"$addsel4",	0xf0000530, TRICORE_V1_2_DN},
  {"$addsel5",	0xf0000534, TRICORE_V1_2_DN},
  {"$addsel6",	0xf0000538, TRICORE_V1_2_DN},
  {"$addsel7",	0xf000053c, TRICORE_V1_2_DN},

  {"$buscon0",	0xf0000560, TRICORE_V1_2_DN},
  {"$buscon1",	0xf0000564, TRICORE_V1_2_DN},
  {"$buscon2",	0xf0000568, TRICORE_V1_2_DN},
  {"$buscon3",	0xf000056c, TRICORE_V1_2_DN},
  {"$buscon4",	0xf0000570, TRICORE_V1_2_DN},
  {"$buscon5",	0xf0000574, TRICORE_V1_2_DN},
  {"$buscon6",	0xf0000578, TRICORE_V1_2_DN},
  {"$buscon7",	0xf000057c, TRICORE_V1_2_DN},

  {"$gtclc",	0xf0000700, TRICORE_V1_2_DN},
  {"$gtid",		0xf0000708, TRICORE_V1_2_DN},
  {"$t01irs",	0xf0000710, TRICORE_V1_2_DN},
  {"$t01ots",	0xf0000714, TRICORE_V1_2_DN},
  {"$t2con",	0xf0000718, TRICORE_V1_2_DN},
  {"$t2rccon",	0xf000071c, TRICORE_V1_2_DN},
  {"$t2ais",	0xf0000720, TRICORE_V1_2_DN},
  {"$t2bis",	0xf0000724, TRICORE_V1_2_DN},
  {"$t2es",		0xf0000728, TRICORE_V1_2_DN},
  {"$gtosel",	0xf000072c, TRICORE_V1_2_DN},
  {"$gtout",	0xf0000730, TRICORE_V1_2_DN},
  {"$t0dcba",	0xf0000734, TRICORE_V1_2_DN},
  {"$t0cba",	0xf0000738, TRICORE_V1_2_DN},
  {"$t0rdcba",	0xf000073c, TRICORE_V1_2_DN},
  {"$t0rcba",	0xf0000740, TRICORE_V1_2_DN},
  {"$t1dcba",	0xf0000744, TRICORE_V1_2_DN},
  {"$t1cba",	0xf0000748, TRICORE_V1_2_DN},
  {"$t1rdcba",	0xf000074c, TRICORE_V1_2_DN},
  {"$t1rcba",	0xf0000750, TRICORE_V1_2_DN},
  {"$t2",		0xf0000754, TRICORE_V1_2_DN},
  {"$t2rc0",	0xf0000758, TRICORE_V1_2_DN},
  {"$t2rc1",	0xf000075c, TRICORE_V1_2_DN},
  {"$t012run",	0xf0000760, TRICORE_V1_2_DN},

  {"$gtsrsel",	0xf00007dc, TRICORE_V1_2_DN},
  {"$gtsrc0",	0xf00007e0, TRICORE_V1_2_DN},
  {"$gtsrc1",	0xf00007e4, TRICORE_V1_2_DN},
  {"$gtsrc2",	0xf00007e8, TRICORE_V1_2_DN},
  {"$gtsrc3",	0xf00007ec, TRICORE_V1_2_DN},
  {"$gtsrc4",	0xf00007f0, TRICORE_V1_2_DN},
  {"$gtsrc5",	0xf00007f4, TRICORE_V1_2_DN},
  {"$gtsrc6",	0xf00007f8, TRICORE_V1_2_DN},
  {"$gtsrc7",	0xf00007fc, TRICORE_V1_2_DN},

  {"$pcpclc",	0xf0003f00, TRICORE_V1_2_DN},
  {"$pcpid",	0xf0003f08, TRICORE_V1_2_DN},
  {"$pcpcs",	0xf0003f10, TRICORE_V1_2_DN},
  {"$pcpes",	0xf0003f14, TRICORE_V1_2_DN},
  {"$pcpicr",	0xf0003f20, TRICORE_V1_2_DN},
  {"$pcpsrc3",	0xf0003ff0, TRICORE_V1_2_DN},
  {"$pcpsrc2",	0xf0003ff4, TRICORE_V1_2_DN},
  {"$pcpsrc1",	0xf0003ff8, TRICORE_V1_2_DN},
  {"$pcpsrc0",	0xf0003ffc, TRICORE_V1_2_DN}
};

const int tricore_numsfrs = sizeof tricore_sfrs / sizeof tricore_sfrs[0];

/* Here are the opcodes for the TriCore CPU.  The assembler requires that
   all instances of the same mnemonic must be consecutive (16-bit versions
   before 32-bit, BOL before BO).  If they aren't, the assembler will bomb
   at runtime.  The disassembler shouldn't care, though.  */

struct tricore_opcode tricore_opcodes[] =
{
#define INDICES 0, 0
  {"abs",        1, 0x01c0000b, 0x0e3f0ff4, F(RR),   2, "dd",    "13",
		 TRICORE_GENERIC, INDICES},
  {"abs.b",      1, 0x05c0000b, 0x0a3f0ff4, F(RR),   2, "dd",    "13",
		 TRICORE_GENERIC, INDICES},
  {"abs.h",      1, 0x07c0000b, 0x083f0ff4, F(RR),   2, "dd",    "13",
		 TRICORE_GENERIC, INDICES},
  {"absdif",     1, 0x00e0000b, 0x0f1f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"absdif",     1, 0x01c0008b, 0x0e200074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"absdif.b",   1, 0x04e0000b, 0x0b1f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"absdif.h",   1, 0x06e0000b, 0x091f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"absdifs",    1, 0x00f0000b, 0x0f0f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"absdifs",    1, 0x01e0008b, 0x0e000074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"absdifs.b",  1, 0x04f0000b, 0x0b0f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"absdifs.h",  1, 0x06f0000b, 0x090f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"abss",       1, 0x01d0000b, 0x0e2f0ff4, F(RR),   2, "dd",    "13",
		 TRICORE_GENERIC, INDICES},
  {"abss.b",     1, 0x05d0000b, 0x0a2f0ff4, F(RR),   2, "dd",    "13",
		 TRICORE_RIDER_A, INDICES},
  {"abss.h",     1, 0x07d0000b, 0x082f0ff4, F(RR),   2, "dd",    "13",
		 TRICORE_GENERIC, INDICES},
  {"add",        0, 0x00000012, 0xffff00ed, F(SRR),  3, "did",   "201",
		 TRICORE_V1_2_UP, INDICES},
  {"add",        0, 0x00000092, 0xffff006d, F(SRC),  3, "di4",   "201",
		 TRICORE_V1_2_UP, INDICES},
  {"add",        0, 0x0000001a, 0xffff00e5, F(SRR),  3, "idd",   "021",
		 TRICORE_GENERIC, INDICES},
  {"add",        0, 0x00000042, 0xffff00bd, F(SRR),  2, "dd",    "21",
		 TRICORE_GENERIC, INDICES},
  {"add",        0, 0x0000009a, 0xffff0065, F(SRC),  3, "id4",   "021",
		 TRICORE_GENERIC, INDICES},
  {"add",        0, 0x000000c2, 0xffff003d, F(SRC),  2, "d4",    "21",
		 TRICORE_GENERIC, INDICES},
  {"add",        1, 0x0000000b, 0x0fff00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"add",        1, 0x0000008b, 0x0fe00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"add.a",      0, 0x00000030, 0xffff00cf, F(SRR),  2, "aa",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"add.a",      0, 0x000000b0, 0xffff004f, F(SRC),  2, "a4",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"add.a",      1, 0x00100001, 0x0fef00fe, F(RR),   3, "aaa",   "143",
		 TRICORE_GENERIC, INDICES},
  {"add.b",      1, 0x0400000b, 0x0bff00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"add.f",      1, 0x0021006b, 0x00def094, F(RRR),  3, "ddd",   "125",
  		 TRICORE_V1_3_UP, INDICES},
  {"add.h",      1, 0x0600000b, 0x09ff00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"addc",       1, 0x0050000b, 0x0faf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"addc",       1, 0x00a0008b, 0x0f400074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"addi",       1, 0x0000001b, 0x000000e4, F(RLC),  3, "ddw",   "132",
		 TRICORE_GENERIC, INDICES},
  {"addih",      1, 0x0000009b, 0x00000064, F(RLC),  3, "ddW",   "132",
		 TRICORE_GENERIC, INDICES},
  {"addih.a",    1, 0x00000011, 0x000000ee, F(RLC),  3, "aaW",   "132",
		 TRICORE_GENERIC, INDICES},
  {"adds",       0, 0x00000022, 0xffff00dd, F(SRR),  2, "dd",    "21",
		 TRICORE_GENERIC, INDICES},
  {"adds",       1, 0x0020000b, 0x0fdf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"adds",       1, 0x0040008b, 0x0fa00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"adds.b",     1, 0x0420000b, 0x0bdf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"adds.bu",    1, 0x0430000b, 0x0bcf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"adds.h",     1, 0x0620000b, 0x09df00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"adds.hu",    1, 0x0630000b, 0x09cf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"adds.u",     1, 0x0030000b, 0x0fcf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"adds.u",     1, 0x0060008b, 0x0f800074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"addsc.a",    0, 0x00000010, 0xffff002f, F(SRRS), 3, "ad2",   "213",
		 TRICORE_RIDER_A, INDICES},
  {"addsc.a",    0, 0x00000010, 0xffff002f, F(SRRS), 4, "aai2",  "2103",
		 TRICORE_V1_2_UP, INDICES},
  {"addsc.a",    1, 0x06000001, 0x09fc00fe, F(RR),   4, "aad2",  "1432",
		 TRICORE_RIDER_A, INDICES},
  {"addsc.a",    1, 0x06000001, 0x09fc00fe, F(RR),   4, "aad2",  "1342",
		 TRICORE_V1_2_UP, INDICES},
  {"addsc.a",    1, 0x06010001, 0x09fc00fe, F(RR),   4, "aad2",  "1342",
		 TRICORE_V1_2_UP, INDICES},
  {"addsc.a",    1, 0x06020001, 0x09fc00fe, F(RR),   4, "aad2",  "1342",
		 TRICORE_V1_2_UP, INDICES},
  {"addsc.a",    1, 0x06030001, 0x09fc00fe, F(RR),   4, "aad2",  "1342",
		 TRICORE_V1_2_UP, INDICES},
  {"addsc.at",   1, 0x06200001, 0x09df00fe, F(RR),   3, "aad",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"addsc.at",   1, 0x06200001, 0x09df00fe, F(RR),   3, "aad",   "134",
		 TRICORE_V1_2_UP, INDICES},
  {"addx",       1, 0x0040000b, 0x0fbf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"addx",       1, 0x0080008b, 0x0f600074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"and",        0, 0x00000016, 0xffff00e9, F(SRR),  2, "dd",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"and",        0, 0x00000026, 0xffff00d9, F(SRR),  2, "dd",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"and",        0, 0x00000096, 0xffff0069, F(SC),   2, "i8",    "01",
		 TRICORE_RIDER_A, INDICES},
  {"and",        0, 0x00000016, 0xffff00e9, F(SC),   2, "i8",    "01",
		 TRICORE_V1_2_UP, INDICES},
  {"and",        1, 0x0080000f, 0x0f7f00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"and",        1, 0x0100008f, 0x0ee00070, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"and.and.t",  1, 0x00000047, 0x006000b8, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"and.andn.t", 1, 0x00600047, 0x000000b8, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"and.eq",     1, 0x0200000b, 0x0dff00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"and.eq",     1, 0x0400008b, 0x0be00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"and.ge",     1, 0x0240000b, 0x0dbf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"and.ge",     1, 0x0480008b, 0x0b600074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"and.ge.u",   1, 0x0250000b, 0x0daf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"and.ge.u",   1, 0x04a0008b, 0x0b400074, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"and.lt",     1, 0x0220000b, 0x0ddf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"and.lt",     1, 0x0440008b, 0x0ba00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"and.lt.u",   1, 0x0230000b, 0x0dcf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"and.lt.u",   1, 0x0460008b, 0x0b800074, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"and.ne",     1, 0x0210000b, 0x0def00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"and.ne",     1, 0x0420008b, 0x0bc00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"and.nor.t",  1, 0x00400047, 0x002000b8, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"and.or.t",   1, 0x00200047, 0x004000b8, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"and.t",      1, 0x00000087, 0x00600078, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"andn",       1, 0x00e0000f, 0x0f1f00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"andn",       1, 0x01c0008f, 0x0e200070, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"andn.t",     1, 0x00600087, 0x00000078, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"bisr",       0, 0x000000c0, 0xffff003f, F(SC),   1, "8",     "1",
		 TRICORE_RIDER_A, INDICES},
  {"bisr",       0, 0x000000e0, 0xffff001f, F(SC),   1, "8",     "1",
		 TRICORE_V1_2_UP, INDICES},
  {"bisr",       1, 0x000000ad, 0xffe00f52, F(RC),   1, "n",     "2",
		 TRICORE_GENERIC, INDICES},
  {"bisr",       1, 0x002000ad, 0xffc00f52, F(RC),   1, "h",     "4",
		 TRICORE_V1_6_1, INDICES},
  {"bmerge",     1, 0x0000004b, 0x0fff00b4, F(RR),   3, "ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"bmerge",     1, 0x0010004b, 0x0fef00b4, F(RR),   3, "ddd",   "143",
		 TRICORE_V1_2_UP, INDICES},
  {"bsplit",     1, 0x0600004b, 0x09fff0b4, F(RR),   2, "Dd",    "14",
		 TRICORE_RIDER_A, INDICES},
  {"bsplit",     1, 0x0090004b, 0x0f6ff0b4, F(RR),   2, "Dd",    "14",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.i",   1, 0x03800089, 0x0c400f76, F(BO),   2, ">0",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.i",   1, 0x038000a9, 0xfc7f0f56, F(BO),   1, "#",     "2",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.i",   1, 0x07800089, 0x08400f76, F(BO),   2, "<0",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.i",   1, 0x078000a9, 0x08400f56, F(BO),   2, "*0",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.i",   1, 0x0b800089, 0x04400f76, F(BO),   2, "@0",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.w",   1, 0x03000089, 0x0cc00f76, F(BO),   2, ">0",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.w",   1, 0x030000a9, 0xfcff0f56, F(BO),   1, "#",     "2",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.w",   1, 0x07000089, 0x08c00f76, F(BO),   2, "<0",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.w",   1, 0x070000a9, 0x08c00f56, F(BO),   2, "*0",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.w",   1, 0x0b000089, 0x04c00f76, F(BO),   2, "@0",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.wi",  1, 0x03400089, 0x0c800f76, F(BO),   2, ">0",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.wi",  1, 0x034000a9, 0xfcbf0f56, F(BO),   1, "#",     "2",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.wi",  1, 0x07400089, 0x08800f76, F(BO),   2, "<0",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.wi",  1, 0x074000a9, 0x08800f56, F(BO),   2, "*0",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"cachea.wi",  1, 0x0b400089, 0x04800f76, F(BO),   2, "@0",    "21",
		 TRICORE_V1_2_UP, INDICES},

  {"cachei.i",   1, 0x02800089, 0x0d400f76, F(BO),   2, ">0",    "21",
  		 TRICORE_V1_6_UP, INDICES},
  {"cachei.i",   1, 0x06800089, 0x09400f76, F(BO),   2, "<0",    "21",
  		 TRICORE_V1_6_UP, INDICES},
  {"cachei.i",   1, 0x0a800089, 0x05400f76, F(BO),   2, "@0",    "21",
  		 TRICORE_V1_6_UP, INDICES},
  {"cachei.w",   1, 0x02c00089, 0x0d000f76, F(BO),   2, ">0",    "21",
  		 TRICORE_V1_3_1_UP, INDICES},
  {"cachei.w",   1, 0x06c00089, 0x09000f76, F(BO),   2, "<0",    "21",
  		 TRICORE_V1_3_1_UP, INDICES},
  {"cachei.w",   1, 0x0ac00089, 0x05000f76, F(BO),   2, "@0",    "21",
  		 TRICORE_V1_3_1_UP, INDICES},
  {"cachei.wi",  1, 0x03c00089, 0x0c000f76, F(BO),   2, ">0",    "21",
  		 TRICORE_V1_3_1_UP, INDICES},
  {"cachei.wi",  1, 0x07c00089, 0x08000f76, F(BO),   2, "<0",    "21",
  		 TRICORE_V1_3_1_UP, INDICES},
  {"cachei.wi",  1, 0x0bc00089, 0x04000f76, F(BO),   2, "@0",    "21",
  		 TRICORE_V1_3_1_UP, INDICES},

  {"cadd",       0, 0x0000000a, 0xffff00f5, F(SRR),  3, "did",   "201",
		 TRICORE_RIDER_A, INDICES},
  {"cadd",       0, 0x0000008a, 0xffff0075, F(SRC),  3, "di4",   "201",
		 TRICORE_GENERIC, INDICES},
  {"cadd",       1, 0x0000002b, 0x00ff00d4, F(RRR),  4, "dddd",  "1254",
		 TRICORE_GENERIC, INDICES},
  {"cadd",       1, 0x000000ab, 0x00e00054, F(RCR),  4, "ddd9",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"cadd.a",     1, 0x00000021, 0x00ff00de, F(RRR),  4, "adaa",  "1254",
		 TRICORE_RIDER_A, INDICES},
  {"cadd.a",     1, 0x000000a1, 0x00e0005e, F(RCR),  4, "ada9",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"caddn",      0, 0x0000004a, 0xffff00b5, F(SRR),  3, "did",   "201",
		 TRICORE_RIDER_A, INDICES},
  {"caddn",      0, 0x000000ca, 0xffff0035, F(SRC),  3, "di4",   "201",
		 TRICORE_GENERIC, INDICES},
  {"caddn",      1, 0x0010002b, 0x00ef00d4, F(RRR),  4, "dddd",  "1254",
		 TRICORE_GENERIC, INDICES},
  {"caddn",      1, 0x002000ab, 0x00c00054, F(RCR),  4, "ddd9",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"caddn.a",    1, 0x00100021, 0x00ef00de, F(RRR),  4, "adaa",  "1254",
		 TRICORE_RIDER_A, INDICES},
  {"caddn.a",    1, 0x002000a1, 0x00c0005e, F(RCR),  4, "ada9",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"call",       0, 0x0000005c, 0xffff00a3, F(SB),   1, "R",     "1",
		 TRICORE_V1_2_UP, INDICES},
  {"call",       1, 0x0000006d, 0x00000092, F(B),    1, "O",     "1",
		 TRICORE_GENERIC, INDICES},
  {"calla",      1, 0x000000ed, 0x00000012, F(B),    1, "T",     "1",
		 TRICORE_GENERIC, INDICES},
  {"calli",      1, 0x0000002d, 0xffff0fd2, F(RR),   1, "a",     "3",
		 TRICORE_RIDER_A, INDICES},
  {"calli",      1, 0x0000002d, 0xfffff0d2, F(RR),   1, "a",     "4",
		 TRICORE_V1_2_UP, INDICES},
  {"clo",        1, 0x01c0000f, 0x0e3ff0f0, F(RR),   2, "dd",    "14",
		 TRICORE_GENERIC, INDICES},
  {"clo.b",      1, 0x03d0000f, 0x0c2ff0f0, F(RR),   2, "dd",    "14",
		 TRICORE_RIDER_A, INDICES},
  {"clo.h",      1, 0x07d0000f, 0x082ff0f0, F(RR),   2, "dd",    "14",
		 TRICORE_GENERIC, INDICES},
  {"cls",        1, 0x01d0000f, 0x0e2ff0f0, F(RR),   2, "dd",    "14",
		 TRICORE_GENERIC, INDICES},
  {"cls.b",      1, 0x03e0000f, 0x0c1ff0f0, F(RR),   2, "dd",    "14",
		 TRICORE_RIDER_A, INDICES},
  {"cls.h",      1, 0x07e0000f, 0x081ff0f0, F(RR),   2, "dd",    "14",
		 TRICORE_GENERIC, INDICES},
  {"clz",        1, 0x01b0000f, 0x0e4ff0f0, F(RR),   2, "dd",    "14",
		 TRICORE_GENERIC, INDICES},
  {"clz.b",      1, 0x03c0000f, 0x0c3ff0f0, F(RR),   2, "dd",    "14",
		 TRICORE_RIDER_A, INDICES},
  {"clz.h",      1, 0x07c0000f, 0x083ff0f0, F(RR),   2, "dd",    "14",
		 TRICORE_GENERIC, INDICES},
  {"cmov",       0, 0x0000002a, 0xffff00d5, F(SRR),  3, "did",   "201",
		 TRICORE_GENERIC, INDICES},
  {"cmov",       0, 0x000000aa, 0xffff0055, F(SRC),  3, "di4",   "201",
		 TRICORE_GENERIC, INDICES},
  {"cmovn",      0, 0x0000006a, 0xffff0095, F(SRR),  3, "did",   "201",
		 TRICORE_GENERIC, INDICES},
  {"cmovn",      0, 0x000000ea, 0xffff0015, F(SRC),  3, "di4",   "201",
		 TRICORE_GENERIC, INDICES},
  {"cmp.f",      1, 0x0001004b, 0x0ffe00b4, F(RR),   3, "ddd",   "143",
  		 TRICORE_V1_3_UP, INDICES},
  {"cmpswap.w",  1, 0x08c00049, 0x070000b6, F(BO),   3, "@0D",   "213",
  		 TRICORE_V1_6_1_UP, INDICES}, /* base + offset */
  {"cmpswap.w",  1, 0x00c00069, 0xff3f0096, F(BO),   2, "#D",    "23",
  		 TRICORE_V1_6_1_UP, INDICES}, /* bit reverse */
  {"cmpswap.w",  1, 0x04c00069, 0x0b000096, F(BO),   3, "*0D",    "213",
  		 TRICORE_V1_6_1_UP, INDICES}, /* circular */
  {"cmpswap.w",  1, 0x00c00049, 0x0f0000b6, F(BO),   3, ">0D",    "213",
  		 TRICORE_V1_6_1_UP, INDICES}, /* post increment */
  {"cmpswap.w",  1, 0x04c00049, 0x0b0000b6, F(BO),   3, "<0D",    "213",
  		 TRICORE_V1_6_1_UP, INDICES}, /* pre increment */
  {"crc32.b",    1, 0x0060004b, 0x0f9f00b4, F(RR),   3, "ddd",    "134",
  		 TRICORE_V1_6_2_UP, INDICES},
  {"crc32b.w",   1, 0x0030004b, 0x0fcf00b4, F(RR),   3, "ddd",    "134",
  		 TRICORE_V1_6_2_UP, INDICES},
  {"crc32l.w",   1, 0x0070004b, 0x0f8f00b4, F(RR),   3, "ddd",    "134",
  		 TRICORE_V1_6_2_UP, INDICES},
  {"crcn",       1, 0x0010006b, 0x00ef0094, F(RRR),  4, "dddd",   "1254",
  		 TRICORE_V1_6_2_UP, INDICES},
  {"crc32",      1, 0x0030004b, 0x0fcf00b4, F(RR),   3, "ddd",    "134",
  		 TRICORE_V1_6_1_UP, INDICES},
  {"csub",       1, 0x0020002b, 0x00df00d4, F(RRR),  4, "dddd",  "1254",
		 TRICORE_GENERIC, INDICES},
  {"csub.a",     1, 0x00200021, 0x00df00de, F(RRR),  4, "adaa",  "1254",
		 TRICORE_RIDER_A, INDICES},
  {"csubn",      1, 0x0030002b, 0x00cf00d4, F(RRR),  4, "dddd",  "1254",
		 TRICORE_GENERIC, INDICES},
  {"csubn.a",    1, 0x00300021, 0x00cf00de, F(RRR),  4, "adaa",  "1254",
		 TRICORE_RIDER_A, INDICES},
  {"debug",      0, 0x0000a000, 0xffff5fff, F(SR),   0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"debug",      1, 0x0100000d, 0xfefffff2, F(SYS),  0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"dextr",      1, 0x00000077, 0x007f0088, F(RRPW), 4, "ddd5",  "1542",
		 TRICORE_GENERIC, INDICES},
  {"dextr",      1, 0x00800017, 0x007f00e8, F(RRRR), 4, "dddd",  "1432",
		 TRICORE_GENERIC, INDICES},
  {"difsc.a",    1, 0x05000001, 0x0afc00fe, F(RR),   4, "daa2",  "1432",
		 TRICORE_RIDER_A, INDICES},
  {"disable",    1, 0x0340000d, 0xfcbffff2, F(SYS),  0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"disable",    1, 0x03c0000d, 0xfc3ff0f2, F(SYS),  1, "d",     "1",
  		 TRICORE_V1_6_UP, INDICES},
  {"div",        1, 0x0201004b, 0x0dfe00b4, F(RR),   3, "Ddd",   "143",
		 TRICORE_V1_6_UP, INDICES},
  {"div.u",      1, 0x0211004b, 0x0dee00b4, F(RR),   3, "Ddd",   "143",
		 TRICORE_V1_6_UP, INDICES},
  {"div.f",      1, 0x0051004b, 0x0fae00b4, F(RR),   3, "ddd",   "143",
  		 TRICORE_V1_3_UP, INDICES},
  {"dsync",      1, 0x0480000d, 0xfb7ffff2, F(SYS),  0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"dvadj",      0, 0x00000072, 0xffff008d, F(SRR),  2, "Dd",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"dvadj",      1, 0x0080002b, 0x007f0fd4, F(RRR),  3, "DDd",   "124",
		 TRICORE_RIDER_A, INDICES},
  {"dvadj",      1, 0x00d0006b, 0x002f0f94, F(RRR),  3, "DDd",   "124",
		 TRICORE_V1_2_UP, INDICES},
  {"dvinit",     1, 0x0000004f, 0x0fff00b0, F(RR),   3, "Ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"dvinit",     1, 0x01a0004b, 0x0e5f00b4, F(RR),   3, "Ddd",   "143",
		 TRICORE_V1_2_UP, INDICES},
  {"dvinit.b",   1, 0x0040004f, 0x0fbf00b0, F(RR),   3, "Ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"dvinit.b",   1, 0x05a0004b, 0x0a5f00b4, F(RR),   3, "Ddd",   "143",
		 TRICORE_V1_2_UP, INDICES},
  {"dvinit.bu",  1, 0x0050004f, 0x0faf00b0, F(RR),   3, "Ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"dvinit.bu",  1, 0x04a0004b, 0x0b5f00b4, F(RR),   3, "Ddd",   "143",
		 TRICORE_V1_2_UP, INDICES},
  {"dvinit.h",   1, 0x0020004f, 0x0fdf00b0, F(RR),   3, "Ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"dvinit.h",   1, 0x03a0004b, 0x0c5f00b4, F(RR),   3, "Ddd",   "143",
		 TRICORE_V1_2_UP, INDICES},
  {"dvinit.hu",  1, 0x0030004f, 0x0fcf00b0, F(RR),   3, "Ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"dvinit.hu",  1, 0x02a0004b, 0x0d5f00b4, F(RR),   3, "Ddd",   "143",
		 TRICORE_V1_2_UP, INDICES},
  {"dvinit.u",   1, 0x0010004f, 0x0fef00b0, F(RR),   3, "Ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"dvinit.u",   1, 0x00a0004b, 0x0f5f00b4, F(RR),   3, "Ddd",   "143",
		 TRICORE_V1_2_UP, INDICES},
  {"dvstep",     0, 0x00000032, 0xffff00cd, F(SRR),  2, "Dd",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"dvstep",     1, 0x0090002b, 0x006f0fd4, F(RRR),  3, "DDd",   "124",
		 TRICORE_RIDER_A, INDICES},
  {"dvstep",     1, 0x00f0006b, 0x000f0f94, F(RRR),  3, "DDd",   "124",
		 TRICORE_V1_2_UP, INDICES},
  {"dvstep.u",   0, 0x000000b2, 0xffff004d, F(SRR),  2, "Dd",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"dvstep.u",   1, 0x00a0002b, 0x005f0fd4, F(RRR),  3, "DDd",   "124",
		 TRICORE_RIDER_A, INDICES},
  {"dvstep.u",   1, 0x00e0006b, 0x001f0f94, F(RRR),  3, "DDd",   "124",
		 TRICORE_V1_2_UP, INDICES},
  {"enable",     1, 0x0300000d, 0xfcfffff2, F(SYS),  0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"eq",         0, 0x0000003a, 0xffff00c5, F(SRR),  3, "idd",   "021",
		 TRICORE_GENERIC, INDICES},
  {"eq",         0, 0x000000ba, 0xffff0045, F(SRC),  3, "id4",   "021",
		 TRICORE_GENERIC, INDICES},
  {"eq",         1, 0x0100000b, 0x0eff00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"eq",         1, 0x0200008b, 0x0de00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"eq.a",       1, 0x04000001, 0x0bff00fe, F(RR),   3, "daa",   "143",
		 TRICORE_GENERIC, INDICES},
  {"eq.b",       1, 0x0500000b, 0x0aff00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"eq.h",       1, 0x0700000b, 0x08ff00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"eq.w",       1, 0x0900000b, 0x06ff00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"eqany.b",    1, 0x0560000b, 0x0a9f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"eqany.b",    1, 0x0ac0008b, 0x05200074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"eqany.h",    1, 0x0760000b, 0x089f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"eqany.h",    1, 0x0ec0008b, 0x01200074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"eqz.a",      1, 0x04800001, 0x0b7ff0fe, F(RR),   2, "da",    "14",
		 TRICORE_GENERIC, INDICES},
  {"extr",       1, 0x00400017, 0x00bff0e8, F(RRRR), 3, "ddD",   "142",
		 TRICORE_GENERIC, INDICES},
  {"extr",       1, 0x00400037, 0x0020f0c8, F(RRPW), 4, "dd55",  "1523",
		 TRICORE_GENERIC, INDICES},
  {"extr",       1, 0x00400057, 0x00a0f0a8, F(RRRW), 4, "ddd5",  "1523",
		 TRICORE_GENERIC, INDICES},
  {"extr.u",     1, 0x00600017, 0x009ff0e8, F(RRRR), 3, "ddD",   "142",
		 TRICORE_GENERIC, INDICES},
  {"extr.u",     1, 0x00600037, 0x0000f0c8, F(RRPW), 4, "dd55",  "1523",
		 TRICORE_GENERIC, INDICES},
  {"extr.u",     1, 0x00600057, 0x0080f0a8, F(RRRW), 4, "ddd5",  "1523",
		 TRICORE_GENERIC, INDICES},
  {"fcall",      1, 0x00000061, 0x0000009e, F(B),    1, "O",     "1",
  		 TRICORE_V1_6_UP, INDICES},
  {"fcalla",     1, 0x000000e1, 0x0000001e, F(B),    1, "T",     "1",
  		 TRICORE_V1_6_UP, INDICES},
  {"fcalli",     1, 0x0010002d, 0xffeff0d2, F(RR),   1, "a",     "4",
  		 TRICORE_V1_6_UP, INDICES},
  {"fret",       0, 0x00007000, 0xffff8fff, F(SR),   0, "",     "",
  		 TRICORE_V1_6_UP, INDICES},
  {"fret",       1, 0x00c0000d, 0xff3ffff2, F(SYS),  0, "",     "",
  		 TRICORE_V1_6_UP, INDICES},
  {"ftoi",       1, 0x0101004b, 0x0efef0b4, F(RR),   2, "dd",    "14",
  		 TRICORE_V1_3_UP, INDICES},
  {"ftoq31",     1, 0x0111004b, 0x0eee00b4, F(RR),   3, "ddd",   "143",
  		 TRICORE_V1_3_UP, INDICES},
  {"ftou",       1, 0x0121004b, 0x0edef0b4, F(RR),   2, "dd",    "14",
  		 TRICORE_V1_3_UP, INDICES},

  {"ftoiz",      1, 0x0131004b, 0x0ecef0b4, F(RR),   2, "dd",    "14",
  		 TRICORE_V1_3_1_UP, INDICES},
  {"ftoq31z",     1, 0x0181004b, 0x0e7e00b4, F(RR),   3, "ddd",   "143",
  		 TRICORE_V1_3_1_UP, INDICES},
  {"ftouz",      1, 0x0171004b, 0x0e8ef0b4, F(RR),   2, "dd",    "14",
  		 TRICORE_V1_3_1_UP, INDICES},
  {"ftohp",      1, 0x0251004b, 0x0daef0b4, F(RR),   2, "dd",    "14",
  		 TRICORE_V1_6_2_UP, INDICES},


  {"ge",         1, 0x0140000b, 0x0ebf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"ge",         1, 0x0280008b, 0x0d600074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"ge.a",       1, 0x04300001, 0x0bcf00fe, F(RR),   3, "daa",   "143",
		 TRICORE_GENERIC, INDICES},
  {"ge.u",       1, 0x0150000b, 0x0eaf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"ge.u",       1, 0x02a0008b, 0x0d400074, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"hptof",      1, 0x0241004b, 0x0dbef0b4, F(RR),   2, "dd",    "14",
  		 TRICORE_V1_6_2_UP, INDICES},
  {"imask",      1, 0x00200037, 0x00400fc8, F(RRPW), 4, "Dd55",  "1423",
		 TRICORE_GENERIC, INDICES},
  {"imask",      1, 0x00200057, 0x00c00fa8, F(RRRW), 4, "Ddd5",  "1423",
		 TRICORE_GENERIC, INDICES},
  {"imask",      1, 0x002000b7, 0x00400f48, F(RCPW), 4, "Df55",  "1423",
		 TRICORE_GENERIC, INDICES},
  {"imask",      1, 0x002000d7, 0x00c00f28, F(RCRW), 4, "Dfd5",  "1423",
		 TRICORE_GENERIC, INDICES},
  {"ins.t",      1, 0x00000067, 0x00600098, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"insert",     1, 0x00000017, 0x00ff00e8, F(RRRR), 4, "dddD",  "1432",
		 TRICORE_GENERIC, INDICES},
  {"insert",     1, 0x00000037, 0x006000c8, F(RRPW), 5, "ddd55", "15423",
		 TRICORE_GENERIC, INDICES},
  {"insert",     1, 0x00000057, 0x00e000a8, F(RRRW), 5, "dddd5", "15423",
		 TRICORE_GENERIC, INDICES},
  {"insert",     1, 0x00000097, 0x00ff0068, F(RCRR), 4, "ddfD",  "1432",
		 TRICORE_GENERIC, INDICES},
  {"insert",     1, 0x000000b7, 0x00600048, F(RCPW), 5, "ddf55", "15423",
		 TRICORE_GENERIC, INDICES},
  {"insert",     1, 0x000000d7, 0x00e00028, F(RCRW), 5, "ddfd5", "15423",
		 TRICORE_GENERIC, INDICES},
  {"insn.t",     1, 0x00200067, 0x00400098, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"isync",      1, 0x04c0000d, 0xfb3ffff2, F(SYS),  0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"itof",       1, 0x0141004b, 0x0ebef0b4, F(RR),   2, "dd",    "14",
		 TRICORE_V1_3_UP, INDICES},
  {"ixmax",      1, 0x00a0006b, 0x005f0f94, F(RRR),  3, "DDd",   "124",
		 TRICORE_V1_3_UP, INDICES},
  {"ixmax.u",    1, 0x00b0006b, 0x004f0f94, F(RRR),  3, "DDd",   "124",
		 TRICORE_V1_3_UP, INDICES},
  {"ixmin",      1, 0x0080006b, 0x007f0f94, F(RRR),  3, "DDd",   "124",
		 TRICORE_V1_3_UP, INDICES},
  {"ixmin.u",    1, 0x0090006b, 0x006f0f94, F(RRR),  3, "DDd",   "124",
		 TRICORE_V1_3_UP, INDICES},
  {"j",          0, 0x0000005c, 0xffff00a3, F(SB),   1, "R",     "1",
		 TRICORE_RIDER_A, INDICES},
  {"j",          0, 0x0000003c, 0xffff00c3, F(SB),   1, "R",     "1",
		 TRICORE_V1_2_UP, INDICES},
  {"j",          1, 0x0000001d, 0x000000e2, F(B),    1, "O",     "1",
		 TRICORE_GENERIC, INDICES},
  {"ja",         1, 0x0000009d, 0x00000062, F(B),    1, "T",     "1",
		 TRICORE_GENERIC, INDICES},
  {"jeq",        0, 0x0000001e, 0xffff00e1, F(SBR),  3, "idm",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"jeq",        0, 0x0000006e, 0xffff0091, F(SBC),  3, "i4m",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"jeq",        0, 0x000000be, 0xffff0041, F(SBR),  3, "idx",   "012",
  		 TRICORE_V1_6_UP, INDICES},
  {"jeq",        0, 0x0000009e, 0xffff0061, F(SBC),  3, "i4x",   "012",
  		 TRICORE_V1_6_UP, INDICES},
  {"jeq",        0, 0x0000003e, 0xffff00c1, F(SBR),  3, "idm",   "012",
		 TRICORE_V1_3_UP, INDICES},
  {"jeq",        0, 0x0000001e, 0xffff00e1, F(SBC),  3, "i4m",   "012",
		 TRICORE_V1_2_UP, INDICES},
  {"jeq",        1, 0x0000005f, 0x800000a0, F(BRR),  3, "ddo",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jeq",        1, 0x000000df, 0x80000020, F(BRC),  3, "d4o",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jeq.a",      1, 0x0000007d, 0x80000082, F(BRR),  3, "aao",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jge",        1, 0x0000007f, 0x80000080, F(BRR),  3, "ddo",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jge",        1, 0x000000ff, 0x80000000, F(BRC),  3, "d4o",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jge.u",      1, 0x8000007f, 0x00000080, F(BRR),  3, "ddo",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jge.u",      1, 0x800000ff, 0x00000000, F(BRC),  3, "dfo",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jgez",       0, 0x000000fe, 0xffff0001, F(SBR),  2, "dm",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"jgez",       0, 0x000000ce, 0xffff0031, F(SBR),  2, "dm",    "12",
		 TRICORE_V1_2_UP, INDICES},
  {"jgtz",       0, 0x0000007e, 0xffff0081, F(SBR),  2, "dm",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"jgtz",       0, 0x0000004e, 0xffff00b1, F(SBR),  2, "dm",    "12",
		 TRICORE_V1_2_UP, INDICES},
  {"ji",         0, 0x0000003c, 0xffff0fc3, F(SBR),  1, "a",     "1",
		 TRICORE_RIDER_A, INDICES},
  {"ji",         0, 0x000000dc, 0xfffff023, F(SR),   1, "a",     "1",
		 TRICORE_V1_2_UP, INDICES},
  {"ji",         1, 0x0030002d, 0xffcf0fd2, F(RR),   1, "a",     "3",
		 TRICORE_RIDER_A, INDICES},
  {"ji",         1, 0x0030002d, 0xffcff0d2, F(RR),   1, "a",     "4",
		 TRICORE_V1_2_UP, INDICES},
  {"jl",         1, 0x0000005d, 0x000000a2, F(B),    1, "O",     "1",
		 TRICORE_GENERIC, INDICES},
  {"jla",        1, 0x000000dd, 0x00000022, F(B),    1, "T",     "1",
		 TRICORE_GENERIC, INDICES},
  {"jlez",       0, 0x000000be, 0xffff0041, F(SBR),  2, "dm",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"jlez",       0, 0x0000008e, 0xffff0071, F(SBR),  2, "dm",    "12",
		 TRICORE_V1_2_UP, INDICES},
  {"jli",        1, 0x0020002d, 0xffdf0fd2, F(RR),   1, "a",     "3",
		 TRICORE_RIDER_A, INDICES},
  {"jli",        1, 0x0020002d, 0xffdff0d2, F(RR),   1, "a",     "4",
		 TRICORE_V1_2_UP, INDICES},
  {"jlt",        1, 0x0000003f, 0x800000c0, F(BRR),  3, "ddo",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jlt",        1, 0x000000bf, 0x80000040, F(BRC),  3, "d4o",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jlt.u",      1, 0x8000003f, 0x000000c0, F(BRR),  3, "ddo",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jlt.u",      1, 0x800000bf, 0x00000040, F(BRC),  3, "dfo",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jltz",       0, 0x0000003e, 0xffff00c1, F(SBR),  2, "dm",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"jltz",       0, 0x0000000e, 0xffff00f1, F(SBR),  2, "dm",    "12",
		 TRICORE_V1_2_UP, INDICES},
  {"jne",        0, 0x0000009e, 0xffff0061, F(SBR),  3, "idm",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"jne",        0, 0x000000ee, 0xffff0011, F(SBC),  3, "i4m",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"jne",        0, 0x000000fe, 0xffff0001, F(SBR),  3, "idx",   "012",
  		 TRICORE_V1_6_UP, INDICES},
  {"jne",        0, 0x000000de, 0xffff0021, F(SBC),  3, "i4x",   "012",
  		 TRICORE_V1_6_UP, INDICES},
  {"jne",        0, 0x0000007e, 0xffff0081, F(SBR),  3, "idm",   "012",
		 TRICORE_V1_2_UP, INDICES},
  {"jne",        0, 0x0000005e, 0xffff00a1, F(SBC),  3, "i4m",   "012",
		 TRICORE_V1_2_UP, INDICES},
  {"jne",        1, 0x8000005f, 0x000000a0, F(BRR),  3, "ddo",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jne",        1, 0x800000df, 0x00000020, F(BRC),  3, "d4o",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jne.a",      1, 0x8000007d, 0x00000082, F(BRR),  3, "aao",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jned",       1, 0x8000001f, 0x000000e0, F(BRR),  3, "ddo",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jned",       1, 0x8000009f, 0x00000060, F(BRC),  3, "d4o",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jnei",       1, 0x0000001f, 0x800000e0, F(BRR),  3, "ddo",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jnei",       1, 0x0000009f, 0x80000060, F(BRC),  3, "d4o",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jnz",        0, 0x000000ae, 0xffff0051, F(SB),   2, "iR",    "01",
		 TRICORE_RIDER_A, INDICES},
  {"jnz",        0, 0x000000ee, 0xffff0011, F(SB),   2, "iR",    "01",
		 TRICORE_V1_2_UP, INDICES},
  {"jnz",        0, 0x000000de, 0xffff0021, F(SBR),  2, "dm",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"jnz",        0, 0x000000f6, 0xffff0009, F(SBR),  2, "dm",    "12",
		 TRICORE_V1_2_UP, INDICES},
  {"jnz.a",      0, 0x0000007c, 0xffff0083, F(SBR),  2, "am",    "12",
  		 TRICORE_RIDER_A | TRICORE_V1_2_UP, INDICES},
  {"jnz.a",      1, 0x800000bd, 0x0000f042, F(BRR),  2, "ao",    "31",
		 TRICORE_GENERIC, INDICES},
  {"jnz.t",      0, 0x0000004e, 0xffff0031, F(SBRN), 3, "i5m",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"jnz.t",      0, 0x000000ae, 0xffff0051, F(SBRN), 3, "ifm",   "012",
		 TRICORE_V1_2_UP, INDICES},
  {"jnz.t",      1, 0x8000006f, 0x00000010, F(BRN),  3, "d5o",   "321",
		 TRICORE_GENERIC, INDICES},
  {"jz",         0, 0x0000002e, 0xffff00d1, F(SB),   2, "iR",    "01",
		 TRICORE_RIDER_A, INDICES},
  {"jz",         0, 0x0000006e, 0xffff0091, F(SB),   2, "iR",    "01",
		 TRICORE_V1_2_UP, INDICES},
  {"jz",         0, 0x0000005e, 0xffff00a1, F(SBR),  2, "dm",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"jz",         0, 0x00000076, 0xffff0089, F(SBR),  2, "dm",    "12",
		 TRICORE_V1_2_UP, INDICES},
  {"jz.a",       0, 0x000000bc, 0xffff0043, F(SBR),  2, "am",    "12",
		 TRICORE_GENERIC, INDICES},
  {"jz.a",       1, 0x000000bd, 0x8000f042, F(BRR),  2, "ao",    "31",
		 TRICORE_GENERIC, INDICES},
  {"jz.t",       0, 0x0000000e, 0xffff0071, F(SBRN), 3, "i5m",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"jz.t",       0, 0x0000002e, 0xffff00d1, F(SBRN), 3, "ifm",   "012",
		 TRICORE_V1_2_UP, INDICES},
  {"jz.t",       1, 0x0000006f, 0x80000010, F(BRN),  3, "d5o",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.a",       0, 0x000000d8, 0xffff0027, F(SC),   3, "I&k",   "001",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.a",       0, 0x0000000c, 0xffff00f3, F(SLRO), 3, "aS6",   "201",
		 TRICORE_RIDER_A, INDICES},
  {"ld.a",       0, 0x000000c8, 0xffff0037, F(SLRO), 3, "aS6",   "201",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.a",       0, 0x00000028, 0xffff00d7, F(SRO),  3, "I@6",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"ld.a",       0, 0x000000cc, 0xffff0033, F(SRO),  3, "I@6",   "012",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.a",       0, 0x00000064, 0xffff009b, F(SLR),  2, "a>",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"ld.a",       0, 0x000000c4, 0xffff003b, F(SLR),  2, "a>",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.a",       0, 0x000000b8, 0xffff0047, F(SLR),  2, "a@",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"ld.a",       0, 0x000000d4, 0xffff002b, F(SLR),  2, "a@",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.a",       1, 0x00000099, 0x00000066, F(BOL),  3, "a@w",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.a",       1, 0x01800009, 0x0e4000f6, F(BO),   3, "a>0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.a",       1, 0x01800029, 0xfe7f00d6, F(BO),   2, "a#",    "32",
		 TRICORE_GENERIC, INDICES},
  {"ld.a",       1, 0x05800009, 0x0a4000f6, F(BO),   3, "a<0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.a",       1, 0x05800029, 0x0a4000d6, F(BO),   3, "a*0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.a",       1, 0x08000085, 0x0400007a, F(ABS),  2, "at",    "21",
		 TRICORE_GENERIC, INDICES},
  {"ld.a",       1, 0x09800009, 0x064000f6, F(BO),   3, "a@0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.b",       0, 0x00000008, 0xffff00f7, F(SRO),  3, "i@f",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"ld.b",       0, 0x00000034, 0xffff00cb, F(SLRO), 3, "dSf",   "201",
		 TRICORE_RIDER_A, INDICES},
  {"ld.b",       0, 0x00000044, 0xffff00bb, F(SLR),  2, "d>",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"ld.b",       0, 0x00000098, 0xffff0067, F(SLR),  2, "d@",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"ld.b",       1, 0x00000079, 0x00000086, F(BOL),  3, "d@w",   "321",
		 TRICORE_V1_6_UP, INDICES}, // TC1.6
  {"ld.b",       1, 0x00000005, 0x0c0000fa, F(ABS),  2, "dt",    "21",
		 TRICORE_GENERIC, INDICES},
  {"ld.b",       1, 0x00000009, 0x0fc000f6, F(BO),   3, "d>0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.b",       1, 0x00000029, 0xffff00d6, F(BO),   2, "d#",    "32",
		 TRICORE_GENERIC, INDICES},
  {"ld.b",       1, 0x04000009, 0x0bc000f6, F(BO),   3, "d<0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.b",       1, 0x04000029, 0x0bc000d6, F(BO),   3, "d*0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.b",       1, 0x08000009, 0x07c000f6, F(BO),   3, "d@0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.b",       1, 0x08000009, 0xf7ff00f6, F(BO),   2, "d@",   "32",
		 TRICORE_GENERIC, INDICES},
  {"ld.bu",      0, 0x00000058, 0xffff00a7, F(SLR),  2, "d@",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"ld.bu",      0, 0x00000014, 0xffff00eb, F(SLR),  2, "d@",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.bu",      0, 0x00000088, 0xffff0077, F(SRO),  3, "i@f",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"ld.bu",      0, 0x0000000c, 0xffff00f3, F(SRO),  3, "i@f",   "012",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.bu",      0, 0x000000b4, 0xffff004b, F(SLRO), 3, "dSf",   "201",
		 TRICORE_RIDER_A, INDICES},
  {"ld.bu",      0, 0x00000008, 0xffff00f7, F(SLRO), 3, "dSf",   "201",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.bu",      0, 0x000000c4, 0xffff003b, F(SLR),  2, "d>",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"ld.bu",      0, 0x00000004, 0xffff00fb, F(SLR),  2, "d>",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.bu",      1, 0x00000039, 0x000000c6, F(BOL),  3, "d@w",   "321",
		 TRICORE_V1_6_UP, INDICES}, // TC1.6
  {"ld.bu",      1, 0x00400009, 0x0f8000f6, F(BO),   3, "d>0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.bu",      1, 0x00400029, 0xffbf00d6, F(BO),   2, "d#",    "32",
		 TRICORE_GENERIC, INDICES},
  {"ld.bu",      1, 0x04000005, 0x080000fa, F(ABS),  2, "dt",    "21",
		 TRICORE_GENERIC, INDICES},
  {"ld.bu",      1, 0x04400009, 0x0b8000f6, F(BO),   3, "d<0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.bu",      1, 0x04400029, 0x0b8000d6, F(BO),   3, "d*0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.bu",      1, 0x08400009, 0x078000f6, F(BO),   3, "d@0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.d",       1, 0x01400009, 0x0e8000f6, F(BO),   3, "D>0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.d",       1, 0x01400029, 0xfebf00d6, F(BO),   2, "D#",    "32",
		 TRICORE_GENERIC, INDICES},
  {"ld.d",       1, 0x04000085, 0x0800007a, F(ABS),  2, "Dt",    "21",
		 TRICORE_GENERIC, INDICES},
  {"ld.d",       1, 0x05400009, 0x0a8000f6, F(BO),   3, "D<0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.d",       1, 0x05400029, 0x0a8000d6, F(BO),   3, "D*0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.d",       1, 0x09400009, 0x068000f6, F(BO),   3, "D@0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.d",       1, 0x09400009, 0xf6bf00f6, F(BO),   2, "D@",    "32",
		 TRICORE_GENERIC, INDICES},
  {"ld.da",      1, 0x01c00009, 0x0e0000f6, F(BO),   3, "A>0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.da",      1, 0x01c00029, 0xfe3f00d6, F(BO),   2, "A#",    "32",
		 TRICORE_GENERIC, INDICES},
  {"ld.da",      1, 0x05c00009, 0x0a0000f6, F(BO),   3, "A<0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.da",      1, 0x05c00029, 0x0a0000d6, F(BO),   3, "A*0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.da",      1, 0x09c00009, 0x060000f6, F(BO),   3, "A@0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.da",      1, 0x09c00009, 0xf63f00f6, F(BO),   2, "A@",    "32",
		 TRICORE_GENERIC, INDICES},
  {"ld.da",      1, 0x0c000085, 0x0000007a, F(ABS),  2, "At",    "21",
		 TRICORE_GENERIC, INDICES},
  {"ld.h",       0, 0x00000024, 0xffff00db, F(SLR),  2, "d>",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"ld.h",       0, 0x00000084, 0xffff007b, F(SLR),  2, "d>",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.h",       0, 0x00000048, 0xffff00b7, F(SRO),  3, "i@v",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"ld.h",       0, 0x0000008c, 0xffff0073, F(SRO),  3, "i@v",   "012",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.h",       0, 0x00000074, 0xffff008b, F(SLRO), 3, "dSv",   "201",
		 TRICORE_RIDER_A, INDICES},
  {"ld.h",       0, 0x00000088, 0xffff0077, F(SLRO), 3, "dSv",   "201",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.h",       0, 0x000000d8, 0xffff0027, F(SLR),  2, "d@",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"ld.h",       0, 0x00000094, 0xffff006b, F(SLR),  2, "d@",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.h",       1, 0x000000c9, 0x00000036, F(BOL),  3, "d@w",   "321",
		 TRICORE_V1_6_UP, INDICES}, // TC1.6
  {"ld.h",       1, 0x00800009, 0x0f4000f6, F(BO),   3, "d>0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.h",       1, 0x00800029, 0xff7f00d6, F(BO),   2, "d#",    "32",
		 TRICORE_GENERIC, INDICES},
  {"ld.h",       1, 0x04800009, 0x0b4000f6, F(BO),   3, "d<0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.h",       1, 0x04800029, 0x0b4000d6, F(BO),   3, "d*0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.h",       1, 0x08000005, 0x040000fa, F(ABS),  2, "dt",    "21",
		 TRICORE_GENERIC, INDICES},
  {"ld.h",       1, 0x08800009, 0x074000f6, F(BO),   3, "d@0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.hu",      1, 0x000000b9, 0x00000046, F(BOL),  3, "d@w",   "321",
		 TRICORE_V1_6_UP, INDICES}, // TC1.6
  {"ld.hu",      1, 0x00c00009, 0x0f0000f6, F(BO),   3, "d>0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.hu",      1, 0x00c00029, 0xff3f00d6, F(BO),   2, "d#",    "32",
		 TRICORE_GENERIC, INDICES},
  {"ld.hu",      1, 0x04c00009, 0x0b0000f6, F(BO),   3, "d<0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.hu",      1, 0x04c00029, 0x0b0000d6, F(BO),   3, "d*0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.hu",      1, 0x08c00009, 0x070000f6, F(BO),   3, "d@0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.hu",      1, 0x08c00009, 0xf73f00f6, F(BO),   2, "d@",    "32",
		 TRICORE_GENERIC, INDICES},
  {"ld.hu",      1, 0x0c000005, 0x000000fa, F(ABS),  2, "dt",    "21",
		 TRICORE_GENERIC, INDICES},
  {"ld.q",       1, 0x00000045, 0x0c0000ba, F(ABS),  2, "dt",    "21",
		 TRICORE_GENERIC, INDICES},
  {"ld.q",       1, 0x02000009, 0x0dc000f6, F(BO),   3, "d>0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.q",       1, 0x02000029, 0xfdff00d6, F(BO),   2, "d#",    "32",
		 TRICORE_GENERIC, INDICES},
  {"ld.q",       1, 0x06000009, 0x09c000f6, F(BO),   3, "d<0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.q",       1, 0x06000029, 0x09c000d6, F(BO),   3, "d*0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.q",       1, 0x0a000009, 0x05c000f6, F(BO),   3, "d@0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.q",       1, 0x0a000009, 0xf5ff00f6, F(BO),   2, "d@",    "32",
		 TRICORE_GENERIC, INDICES},
  {"ld.w",       0, 0x00000058, 0xffff00a7, F(SC),   3, "i&k",   "001",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.w",       0, 0x00000038, 0xffff00c7, F(SLR),  2, "d@",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"ld.w",       0, 0x00000054, 0xffff00ab, F(SLR),  2, "d@",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.w",       0, 0x000000a4, 0xffff005b, F(SLR),  2, "d>",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"ld.w",       0, 0x00000044, 0xffff00bb, F(SLR),  2, "d>",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.w",       0, 0x000000c8, 0xffff0037, F(SRO),  3, "i@6",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"ld.w",       0, 0x0000004c, 0xffff00b3, F(SRO),  3, "i@6",   "012",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.w",       0, 0x000000f4, 0xffff000b, F(SLRO), 3, "dS6",   "201",
		 TRICORE_RIDER_A, INDICES},
  {"ld.w",       0, 0x00000048, 0xffff00b7, F(SLRO), 3, "dS6",   "201",
		 TRICORE_V1_2_UP, INDICES},
  {"ld.w",       1, 0x00000019, 0x000000e6, F(BOL),  3, "d@w",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.w",       1, 0x00000085, 0x0c00007a, F(ABS),  2, "dt",    "21",
		 TRICORE_GENERIC, INDICES},
  {"ld.w",       1, 0x01000009, 0x0ec000f6, F(BO),   3, "d>0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.w",       1, 0x01000029, 0xfeff00d6, F(BO),   2, "d#",    "32",
		 TRICORE_GENERIC, INDICES},
  {"ld.w",       1, 0x05000009, 0x0ac000f6, F(BO),   3, "d<0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.w",       1, 0x05000029, 0x0ac000d6, F(BO),   3, "d*0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ld.w",       1, 0x09000009, 0x06c000f6, F(BO),   3, "d@0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"ldlcx",      1, 0x08000015, 0x04000fea, F(ABS),  1, "t",     "1",
		 TRICORE_GENERIC, INDICES},
  {"ldlcx",      1, 0x09000049, 0x06c00fb6, F(BO),   2, "@0",    "21",
		 TRICORE_GENERIC, INDICES},
  {"ldmst",      1, 0x00400049, 0x0f8000b6, F(BO),   3, ">0D",   "213",
		 TRICORE_GENERIC, INDICES},
  {"ldmst",      1, 0x00400069, 0xffbf0096, F(BO),   2, "#D",    "23",
		 TRICORE_GENERIC, INDICES},
  {"ldmst",      1, 0x040000e5, 0x0800001a, F(ABS),  2, "tD",    "12",
		 TRICORE_GENERIC, INDICES},
  {"ldmst",      1, 0x04400049, 0x0b8000b6, F(BO),   3, "<0D",   "213",
		 TRICORE_GENERIC, INDICES},
  {"ldmst",      1, 0x04400069, 0x0b800096, F(BO),   3, "*0D",   "213",
		 TRICORE_GENERIC, INDICES},
  {"ldmst",      1, 0x08400049, 0x078000b6, F(BO),   3, "@0D",   "213",
		 TRICORE_GENERIC, INDICES},
  {"lducx",      1, 0x09400049, 0x06800fb6, F(BO),   2, "@0",    "21",
		 TRICORE_GENERIC, INDICES},
  {"lducx",      1, 0x0c000015, 0x00000fea, F(ABS),  1, "t",     "1",
		 TRICORE_GENERIC, INDICES},
  {"lea",        1, 0x000000c5, 0x0c00003a, F(ABS),  2, "at",    "21",
		 TRICORE_GENERIC, INDICES},
  {"lea",        1, 0x000000d9, 0x00000026, F(BOL),  3, "a@w",   "321",
		 TRICORE_GENERIC, INDICES},
  {"lea",        1, 0x0a000049, 0x05c000b6, F(BO),   3, "a@0",   "321",
		 TRICORE_GENERIC, INDICES},
  {"lha",        1, 0x040000c5, 0x0800003a, F(ABS),  2, "aV",    "25",
		 TRICORE_V1_6_2_UP, INDICES},
  {"loop",       0, 0x000000fc, 0xffff0003, F(SBR),  2, "ar",    "12",
		 TRICORE_GENERIC, INDICES},
  {"loop",       1, 0x000000fd, 0x80000f02, F(BRR),  2, "ao",    "21",
		 TRICORE_GENERIC, INDICES},
  {"loopu",      1, 0x800000fd, 0x0000ff02, F(BRR),  1, "o",     "1",
		 TRICORE_V1_2_UP, INDICES},
  {"lt",         0, 0x0000007a, 0xffff0085, F(SRR),  3, "idd",   "021",
		 TRICORE_GENERIC, INDICES},
  {"lt",         0, 0x000000fa, 0xffff0005, F(SRC),  3, "id4",   "021",
		 TRICORE_GENERIC, INDICES},
  {"lt",         1, 0x0120000b, 0x0edf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"lt",         1, 0x0240008b, 0x0da00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"lt.a",       1, 0x04200001, 0x0bdf00fe, F(RR),   3, "daa",   "143",
		 TRICORE_GENERIC, INDICES},
  {"lt.b",       1, 0x0520000b, 0x0adf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"lt.bu",      1, 0x0530000b, 0x0acf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"lt.h",       1, 0x0720000b, 0x08df00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"lt.hu",      1, 0x0730000b, 0x08cf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"lt.u",       0, 0x00000006, 0xffff00f9, F(SRR),  3, "idd",   "021",
		 TRICORE_RIDER_A, INDICES},
  {"lt.u",       0, 0x00000086, 0xffff0079, F(SRC),  3, "idf",   "021",
		 TRICORE_RIDER_A, INDICES},
  {"lt.u",       1, 0x0130000b, 0x0ecf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"lt.u",       1, 0x0260008b, 0x0d800074, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"lt.w",       1, 0x0920000b, 0x06df00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"lt.wu",      1, 0x0930000b, 0x06cf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"madd",       1, 0x000a0003, 0x00f500fc, F(RRR2), 4, "dddd",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"madd",       1, 0x00200013, 0x00c000ec, F(RCR),  4, "ddd9",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"madd",       1, 0x00600013, 0x008000ec, F(RCR),  4, "DDd9",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"madd",       1, 0x006a0003, 0x009500fc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.f",     1, 0x0061006b, 0x009e0094, F(RRR),  4, "dddd",  "1254",
		 TRICORE_V1_3_UP, INDICES},
  {"madd.h",     1, 0x00600083, 0x009c007c, F(RRR1), 5, "DDdd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"madd.h",     1, 0x00600083, 0x009c007c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.h",     1, 0x00640083, 0x0098007c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.h",     1, 0x00680083, 0x0094007c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.h",     1, 0x006c0083, 0x0090007c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.q",     1, 0x00100043, 0x00ec00bc, F(RRR1), 5, "dddd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"madd.q",     1, 0x00100043, 0x00ec00bc, F(RRR1), 5, "ddGG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.q",     1, 0x00000043, 0x00fc00bc, F(RRR1), 5, "dddG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.q",     1, 0x00040043, 0x00f800bc, F(RRR1), 5, "dddg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.q",     1, 0x00080043, 0x00f400bc, F(RRR1), 5, "dddd1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.q",     1, 0x00140043, 0x00e800bc, F(RRR1), 5, "ddgg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.q",     1, 0x00600043, 0x009c00bc, F(RRR1), 5, "DDdG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.q",     1, 0x00640043, 0x009800bc, F(RRR1), 5, "DDdg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.q",     1, 0x006c0043, 0x009000bc, F(RRR1), 5, "DDdd1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.q",     1, 0x00700043, 0x008c00bc, F(RRR1), 5, "DDGG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.q",     1, 0x00740043, 0x008800bc, F(RRR1), 5, "DDgg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.u",     1, 0x00400013, 0x00a000ec, F(RCR),  4, "DDdn",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"madd.u",     1, 0x00680003, 0x009700fc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"maddm",      1, 0x00600013, 0x008000ec, F(RCR),  4, "DDd9",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"maddm",      1, 0x006a0003, 0x009500fc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"maddm.h",    1, 0x00700083, 0x008f007c, F(RRR1), 4, "DDdd",  "1254",
		 TRICORE_RIDER_A, INDICES},
  {"maddm.h",    1, 0x00700083, 0x008c007c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddm.h",    1, 0x00740083, 0x0088007c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddm.h",    1, 0x00780083, 0x0084007c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddm.h",    1, 0x007c0083, 0x0080007c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddm.q",    1, 0x00700043, 0x008f00bc, F(RRR1), 4, "DDdd",  "1254",
		 TRICORE_RIDER_A, INDICES},
  {"maddm.u",    1, 0x00400013, 0x00a000ec, F(RCR),  4, "DDdn",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"maddm.u",    1, 0x00680003, 0x009700fc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"maddms",     1, 0x00e00013, 0x000000ec, F(RCR),  4, "DDd9",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"maddms",     1, 0x00ea0003, 0x001500fc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"maddms.h",   1, 0x00f00083, 0x000c007c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddms.h",   1, 0x00f40083, 0x0008007c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddms.h",   1, 0x00f80083, 0x0004007c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddms.h",   1, 0x00fc0083, 0x0000007c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddms.u",   1, 0x00c00013, 0x002000ec, F(RCR),  4, "DDdn",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"maddms.u",   1, 0x00e80003, 0x001700fc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"maddr.h",    1, 0x00780043, 0x008400bc, F(RRR1), 5, "dDdd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"maddr.h",    1, 0x00780043, 0x008400bc, F(RRR1), 5, "dDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddr.h",    1, 0x00300083, 0x00cc007c, F(RRR1), 5, "dddL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddr.h",    1, 0x00340083, 0x00c8007c, F(RRR1), 5, "dddl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddr.h",    1, 0x00380083, 0x00c4007c, F(RRR1), 5, "ddd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddr.h",    1, 0x003c0083, 0x00c0007c, F(RRR1), 5, "ddd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddr.q",    1, 0x00180043, 0x00e400bc, F(RRR1), 5, "dddd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"maddr.q",    1, 0x00180043, 0x00e400bc, F(RRR1), 5, "ddGG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddr.q",    1, 0x001c0043, 0x00e000bc, F(RRR1), 5, "ddgg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddrs.h",   1, 0x00f80043, 0x000400bc, F(RRR1), 5, "dDdd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"maddrs.h",   1, 0x00f80043, 0x000400bc, F(RRR1), 5, "dDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddrs.h",   1, 0x00b00083, 0x004c007c, F(RRR1), 5, "dddL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddrs.h",   1, 0x00b40083, 0x0048007c, F(RRR1), 5, "dddl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddrs.h",   1, 0x00b80083, 0x0044007c, F(RRR1), 5, "ddd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddrs.h",   1, 0x00bc0083, 0x0040007c, F(RRR1), 5, "ddd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddrs.q",   1, 0x00980043, 0x006400bc, F(RRR1), 5, "dddd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"maddrs.q",   1, 0x00980043, 0x006400bc, F(RRR1), 5, "ddGG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddrs.q",   1, 0x009c0043, 0x006000bc, F(RRR1), 5, "ddgg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds",      1, 0x008a0003, 0x007500fc, F(RRR2), 4, "dddd",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"madds",      1, 0x00a00013, 0x004000ec, F(RCR),  4, "ddd9",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"madds",      1, 0x00e00013, 0x000000ec, F(RCR),  4, "DDd9",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"madds",      1, 0x00ea0003, 0x001500fc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.h",    1, 0x00e00083, 0x001c007c, F(RRR1), 5, "DDdd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"madds.h",    1, 0x00e00083, 0x001c007c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.h",    1, 0x00e40083, 0x0018007c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.h",    1, 0x00e80083, 0x0014007c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.h",    1, 0x00ec0083, 0x0010007c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.q",    1, 0x00900043, 0x006c00bc, F(RRR1), 5, "dddd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"madds.q",    1, 0x00900043, 0x006c00bc, F(RRR1), 5, "ddGG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.q",    1, 0x00800043, 0x007c00bc, F(RRR1), 5, "dddG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.q",    1, 0x00840043, 0x007800bc, F(RRR1), 5, "dddg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.q",    1, 0x00880043, 0x007400bc, F(RRR1), 5, "dddd1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.q",    1, 0x00940043, 0x006800bc, F(RRR1), 5, "ddgg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.q",    1, 0x00e00043, 0x001c00bc, F(RRR1), 5, "DDdG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.q",    1, 0x00e40043, 0x001800bc, F(RRR1), 5, "DDdg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.q",    1, 0x00ec0043, 0x001000bc, F(RRR1), 5, "DDdd1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.q",    1, 0x00f00043, 0x000c00bc, F(RRR1), 5, "DDGG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.q",    1, 0x00f40043, 0x000800bc, F(RRR1), 5, "DDgg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.u",    1, 0x00800013, 0x006000ec, F(RCR),  4, "dddn",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"madds.u",    1, 0x00880003, 0x007700fc, F(RRR2), 4, "dddd",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"madds.u",    1, 0x00c00013, 0x002000ec, F(RCR),  4, "DDdn",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"madds.u",    1, 0x00e80003, 0x001700fc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsu.h",   1, 0x006000c3, 0x009c003c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsu.h",   1, 0x006400c3, 0x0098003c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsu.h",   1, 0x006800c3, 0x0094003c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsu.h",   1, 0x006c00c3, 0x0090003c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsum.h",  1, 0x007000c3, 0x008c003c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsum.h",  1, 0x007400c3, 0x0088003c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsum.h",  1, 0x007800c3, 0x0084003c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsum.h",  1, 0x007c00c3, 0x0080003c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsums.h", 1, 0x00f000c3, 0x000c003c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsums.h", 1, 0x00f400c3, 0x0008003c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsums.h", 1, 0x00f800c3, 0x0004003c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsums.h", 1, 0x00fc00c3, 0x0000003c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsur.h",  1, 0x003000c3, 0x00cc003c, F(RRR1), 5, "dddL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsur.h",  1, 0x003400c3, 0x00c8003c, F(RRR1), 5, "dddl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsur.h",  1, 0x003800c3, 0x00c4003c, F(RRR1), 5, "ddd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsur.h",  1, 0x003c00c3, 0x00c0003c, F(RRR1), 5, "ddd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsurs.h", 1, 0x00b000c3, 0x004c003c, F(RRR1), 5, "dddL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsurs.h", 1, 0x00b400c3, 0x0048003c, F(RRR1), 5, "dddl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsurs.h", 1, 0x00b800c3, 0x0044003c, F(RRR1), 5, "ddd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsurs.h", 1, 0x00bc00c3, 0x0040003c, F(RRR1), 5, "ddd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsus.h",  1, 0x00e000c3, 0x001c003c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsus.h",  1, 0x00e400c3, 0x0018003c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsus.h",  1, 0x00e800c3, 0x0014003c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"maddsus.h",  1, 0x00ec00c3, 0x0010003c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"max",        1, 0x01a0000b, 0x0e5f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"max",        1, 0x0340008b, 0x0ca00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"max.b",      1, 0x05a0000b, 0x0a5f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"max.bu",     1, 0x05b0000b, 0x0a4f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"max.h",      1, 0x07a0000b, 0x085f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"max.hu",     1, 0x07b0000b, 0x084f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"max.u",      1, 0x01b0000b, 0x0e4f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"max.u",      1, 0x0360008b, 0x0c800074, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"mfcr",       1, 0x0000004d, 0x00000fb2, F(RLC),  2, "dW",    "12",
		 TRICORE_GENERIC, INDICES},
  {"min",        1, 0x0180000b, 0x0e7f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"min",        1, 0x0300008b, 0x0ce00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"min.b",      1, 0x0580000b, 0x0a7f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"min.bu",     1, 0x0590000b, 0x0a6f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"min.h",      1, 0x0780000b, 0x087f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"min.hu",     1, 0x0790000b, 0x086f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"min.u",      1, 0x0190000b, 0x0e6f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"min.u",      1, 0x0320008b, 0x0cc00074, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"mov",        0, 0x00000002, 0xffff00fd, F(SRR),  2, "dd",    "21",
		 TRICORE_GENERIC, INDICES},
  {"mov",        0, 0x00000082, 0xffff007d, F(SRC),  2, "d4",    "21",
		 TRICORE_GENERIC, INDICES},
  {"mov",        0, 0x000000d2, 0xffff002d, F(SRC),  2, "D4",    "21",
  		 TRICORE_V1_6_UP, INDICES},
  {"mov",        0, 0x000000c6, 0xffff0039, F(SC),   2, "i8",    "01",
		 TRICORE_RIDER_A, INDICES},
  {"mov",        0, 0x000000da, 0xffff0025, F(SC),   2, "i8",    "01",
		 TRICORE_V1_2_UP, INDICES},
  {"mov",        1, 0x0000003b, 0x00000fc4, F(RLC),  2, "dw",    "12",
		 TRICORE_GENERIC, INDICES},
  {"mov",        1, 0x01f0000b, 0x0e0f0ff4, F(RR),   2, "dd",    "13",
		 TRICORE_GENERIC, INDICES},
  {"mov",        1, 0x000000fb, 0x00000f04, F(RLC),  2, "Dw",    "12",
  		 TRICORE_V1_6_UP, INDICES},
  {"mov",        1, 0x0800000b, 0x07ff0ff4, F(RR),   2, "Dd",    "13",
  		 TRICORE_V1_6_UP, INDICES},
  {"mov",        1, 0x0810000b, 0x07ef00f4, F(RR),   3, "Ddd",   "143",
  		 TRICORE_V1_6_UP, INDICES},
  {"mov.a",      0, 0x000000a0, 0xffff005f, F(SRC),  2, "af",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"mov.a",      0, 0x00000030, 0xffff00cf, F(SRR),  2, "ad",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"mov.a",      0, 0x00000060, 0xffff009f, F(SRR),  2, "ad",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"mov.a",      1, 0x06300001, 0x09cf0ffe, F(RR),   2, "ad",    "13",
		 TRICORE_GENERIC, INDICES},
  {"mov.aa",     0, 0x00000080, 0xffff007f, F(SRR),  2, "aa",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"mov.aa",     0, 0x00000040, 0xffff00bf, F(SRR),  2, "aa",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"mov.aa",     1, 0x00000001, 0x0fff0ffe, F(RR),   2, "aa",    "13",
		 TRICORE_GENERIC, INDICES},
  {"mov.d",      0, 0x00000020, 0xffff00df, F(SRR),  2, "da",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"mov.d",      0, 0x00000080, 0xffff007f, F(SRR),  2, "da",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"mov.d",      1, 0x04c00001, 0x0b3f0ffe, F(RR),   2, "da",    "13",
		 TRICORE_GENERIC, INDICES},
  {"mov.u",      1, 0x000000bb, 0x00000f44, F(RLC),  2, "dW",    "12",
		 TRICORE_GENERIC, INDICES},
  {"movh",       1, 0x0000007b, 0x00000f84, F(RLC),  2, "dW",    "12",
		 TRICORE_GENERIC, INDICES},
  {"movh.a",     1, 0x00000091, 0x00000f6e, F(RLC),  2, "aW",    "12",
		 TRICORE_GENERIC, INDICES},
  {"movz.a",     0, 0x00001000, 0xffffe0ff, F(SR),   1, "a",     "1",
		 TRICORE_RIDER_A, INDICES},
  {"msub",       1, 0x000a0023, 0x00f500dc, F(RRR2), 4, "dddd",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"msub",       1, 0x00200033, 0x00c000cc, F(RCR),  4, "ddd9",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"msub",       1, 0x00600033, 0x008000cc, F(RCR),  4, "DDd9",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"msub",       1, 0x006a0023, 0x009500dc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.f",     1, 0x0071006b, 0x008e0094, F(RRR),  4, "dddd",  "1254",
		 TRICORE_V1_3_UP, INDICES},
  {"msub.h",     1, 0x006000a3, 0x009c005c, F(RRR1), 5, "DDdd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"msub.h",     1, 0x006000a3, 0x009c005c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.h",     1, 0x006400a3, 0x0098005c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.h",     1, 0x006800a3, 0x0094005c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.h",     1, 0x006c00a3, 0x0090005c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.q",     1, 0x00100063, 0x00ec009c, F(RRR1), 5, "dddd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"msub.q",     1, 0x00100063, 0x00ec009c, F(RRR1), 5, "ddGG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.q",     1, 0x00000063, 0x00fc009c, F(RRR1), 5, "dddG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.q",     1, 0x00040063, 0x00f8009c, F(RRR1), 5, "dddg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.q",     1, 0x00080063, 0x00f4009c, F(RRR1), 5, "dddd1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.q",     1, 0x00140063, 0x00e8009c, F(RRR1), 5, "ddgg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.q",     1, 0x00600063, 0x009c009c, F(RRR1), 5, "DDdG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.q",     1, 0x00640063, 0x0098009c, F(RRR1), 5, "DDdg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.q",     1, 0x006c0063, 0x0090009c, F(RRR1), 5, "DDdd1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.q",     1, 0x00700063, 0x008c009c, F(RRR1), 5, "DDGG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.q",     1, 0x00740063, 0x0088009c, F(RRR1), 5, "DDgg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.u",     1, 0x00400033, 0x00a000cc, F(RCR),  4, "DDdn",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"msub.u",     1, 0x00680023, 0x009700dc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"msubad.h",   1, 0x006000e3, 0x009c001c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubad.h",   1, 0x006400e3, 0x0098001c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubad.h",   1, 0x006800e3, 0x0094001c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubad.h",   1, 0x006c00e3, 0x0090001c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadm.h",  1, 0x007000e3, 0x008c001c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadm.h",  1, 0x007400e3, 0x0088001c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadm.h",  1, 0x007800e3, 0x0084001c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadm.h",  1, 0x007c00e3, 0x0080001c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadms.h", 1, 0x00f000e3, 0x000c001c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadms.h", 1, 0x00f400e3, 0x0008001c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadms.h", 1, 0x00f800e3, 0x0004001c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadms.h", 1, 0x00fc00e3, 0x0000001c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadr.h",  1, 0x003000e3, 0x00cc001c, F(RRR1), 5, "dddL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadr.h",  1, 0x003400e3, 0x00c8001c, F(RRR1), 5, "dddl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadr.h",  1, 0x003800e3, 0x00c4001c, F(RRR1), 5, "ddd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadr.h",  1, 0x003c00e3, 0x00c0001c, F(RRR1), 5, "ddd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadrs.h", 1, 0x00b000e3, 0x004c001c, F(RRR1), 5, "dddL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadrs.h", 1, 0x00b400e3, 0x0048001c, F(RRR1), 5, "dddl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadrs.h", 1, 0x00b800e3, 0x0044001c, F(RRR1), 5, "ddd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubadrs.h", 1, 0x00bc00e3, 0x0040001c, F(RRR1), 5, "ddd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubads.h",  1, 0x00e000e3, 0x001c001c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubads.h",  1, 0x00e400e3, 0x0018001c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubads.h",  1, 0x00e800e3, 0x0014001c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubads.h",  1, 0x00ec00e3, 0x0010001c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubm",      1, 0x00600033, 0x008000cc, F(RCR),  4, "DDd9",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"msubm",      1, 0x006a0023, 0x009500dc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"msubm.h",    1, 0x007000a3, 0x008f005c, F(RRR1), 4, "DDdd",  "1254",
		 TRICORE_RIDER_A, INDICES},
  {"msubm.h",    1, 0x007000a3, 0x008c005c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubm.h",    1, 0x007400a3, 0x0088005c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubm.h",    1, 0x007800a3, 0x0084005c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubm.h",    1, 0x007c00a3, 0x0080005c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubm.q",    1, 0x00700063, 0x008f009c, F(RRR1), 4, "DDdd",  "1254",
		 TRICORE_RIDER_A, INDICES},
  {"msubm.u",    1, 0x00400033, 0x00a000cc, F(RCR),  4, "DDdn",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"msubm.u",    1, 0x00680023, 0x009700dc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"msubms",     1, 0x00e00033, 0x000000cc, F(RCR),  4, "DDd9",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"msubms",     1, 0x00ea0023, 0x001500dc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"msubms.h",   1, 0x00f000a3, 0x000c005c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubms.h",   1, 0x00f400a3, 0x0008005c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubms.h",   1, 0x00f800a3, 0x0004005c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubms.h",   1, 0x00fc00a3, 0x0000005c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubms.u",   1, 0x00c00033, 0x002000cc, F(RCR),  4, "DDdn",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"msubms.u",   1, 0x00e80023, 0x001700dc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"msubr.h",    1, 0x00780063, 0x0084009c, F(RRR1), 5, "dDdd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"msubr.h",    1, 0x00780063, 0x0084009c, F(RRR1), 5, "dDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubr.h",    1, 0x003000a3, 0x00cc005c, F(RRR1), 5, "dddL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubr.h",    1, 0x003400a3, 0x00c8005c, F(RRR1), 5, "dddl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubr.h",    1, 0x003800a3, 0x00c4005c, F(RRR1), 5, "ddd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubr.h",    1, 0x003c00a3, 0x00c0005c, F(RRR1), 5, "ddd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubr.q",    1, 0x00180063, 0x00e4009c, F(RRR1), 5, "dddd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"msubr.q",    1, 0x00180063, 0x00e4009c, F(RRR1), 5, "ddGG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubr.q",    1, 0x001c0063, 0x00e0009c, F(RRR1), 5, "ddgg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubrs.h",   1, 0x00f80063, 0x0004009c, F(RRR1), 5, "dDdd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"msubrs.h",   1, 0x00f80063, 0x0004009c, F(RRR1), 5, "dDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubrs.h",   1, 0x00b000a3, 0x004c005c, F(RRR1), 5, "dddL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubrs.h",   1, 0x00b400a3, 0x0048005c, F(RRR1), 5, "dddl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubrs.h",   1, 0x00b800a3, 0x0044005c, F(RRR1), 5, "ddd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubrs.h",   1, 0x00bc00a3, 0x0040005c, F(RRR1), 5, "ddd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubrs.q",   1, 0x00980063, 0x0064009c, F(RRR1), 5, "dddd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"msubrs.q",   1, 0x00980063, 0x0064009c, F(RRR1), 5, "ddGG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubrs.q",   1, 0x009c0063, 0x0060009c, F(RRR1), 5, "ddgg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs",      1, 0x008a0023, 0x007500dc, F(RRR2), 4, "dddd",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"msubs",      1, 0x00a00033, 0x004000cc, F(RCR),  4, "ddd9",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"msubs",      1, 0x00e00033, 0x000000cc, F(RCR),  4, "DDd9",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs",      1, 0x00ea0023, 0x001500dc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.h",    1, 0x00e000a3, 0x001c005c, F(RRR1), 5, "DDdd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"msubs.h",    1, 0x00e000a3, 0x001c005c, F(RRR1), 5, "DDdL1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.h",    1, 0x00e400a3, 0x0018005c, F(RRR1), 5, "DDdl1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.h",    1, 0x00e800a3, 0x0014005c, F(RRR1), 5, "DDd-1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.h",    1, 0x00ec00a3, 0x0010005c, F(RRR1), 5, "DDd+1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.q",    1, 0x00900063, 0x006c009c, F(RRR1), 5, "dddd1", "12543",
		 TRICORE_RIDER_A, INDICES},
  {"msubs.q",    1, 0x00900063, 0x006c009c, F(RRR1), 5, "ddGG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.q",    1, 0x00800063, 0x007c009c, F(RRR1), 5, "dddG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.q",    1, 0x00840063, 0x0078009c, F(RRR1), 5, "dddg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.q",    1, 0x00880063, 0x0074009c, F(RRR1), 5, "dddd1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.q",    1, 0x00940063, 0x0068009c, F(RRR1), 5, "ddgg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.q",    1, 0x00e00063, 0x001c009c, F(RRR1), 5, "DDdG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.q",    1, 0x00e40063, 0x0018009c, F(RRR1), 5, "DDdg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.q",    1, 0x00ec0063, 0x0010009c, F(RRR1), 5, "DDdd1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.q",    1, 0x00f00063, 0x000c009c, F(RRR1), 5, "DDGG1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.q",    1, 0x00f40063, 0x0008009c, F(RRR1), 5, "DDgg1", "12543",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.u",    1, 0x00800033, 0x006000cc, F(RCR),  4, "dddn",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"msubs.u",    1, 0x00880023, 0x007700dc, F(RRR2), 4, "dddd",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"msubs.u",    1, 0x00c00033, 0x002000cc, F(RCR),  4, "DDdn",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"msubs.u",    1, 0x00e80023, 0x001700dc, F(RRR2), 4, "DDdd",  "1243",
		 TRICORE_V1_2_UP, INDICES},
  {"mtcr",       1, 0x000000cd, 0xf0000032, F(RLC),  2, "Wd",    "23",
		 TRICORE_GENERIC, INDICES},
  {"mul",        0, 0x000000e2, 0xffff001d, F(SRR),  2, "dd",    "21",
		 TRICORE_GENERIC, INDICES},
  {"mul",        1, 0x00200053, 0x0fc000ac, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"mul",        1, 0x00a00073, 0x0f5f008c, F(RR),   3, "ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"mul",        1, 0x000a0073, 0x0ff5008c, F(RR2),  3, "ddd",   "132",
		 TRICORE_V1_2_UP, INDICES},
  {"mul",        1, 0x00600053, 0x0f8000ac, F(RC),   3, "Dd9",   "132",
		 TRICORE_V1_2_UP, INDICES},
  {"mul",        1, 0x006a0073, 0x0f95008c, F(RR2),  3, "Ddd",   "132",
		 TRICORE_V1_2_UP, INDICES},
  {"mul.f",      1, 0x0041004b, 0x0fbe00b4, F(RR),   3, "ddd",   "143",
		 TRICORE_V1_3_UP, INDICES},
  {"mul.h",      1, 0x018000b3, 0x0e7c004c, F(RR),   4, "Ddd1",  "1432",
		 TRICORE_RIDER_A, INDICES},
  {"mul.h",      1, 0x006000b3, 0x0f9c004c, F(RR1),  4, "DdL1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mul.h",      1, 0x006400b3, 0x0f98004c, F(RR1),  4, "Ddl1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mul.h",      1, 0x006800b3, 0x0f94004c, F(RR1),  4, "Dd-1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mul.h",      1, 0x006c00b3, 0x0f90004c, F(RR1),  4, "Dd+1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mul.q",      1, 0x00400093, 0x0fbc006c, F(RR),   4, "ddd1",  "1432",
		 TRICORE_RIDER_A, INDICES},
  {"mul.q",      1, 0x00000093, 0x0ffc006c, F(RR1),  4, "ddG1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mul.q",      1, 0x00040093, 0x0ff8006c, F(RR1),  4, "ddg1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mul.q",      1, 0x00080093, 0x0ff4006c, F(RR1),  4, "ddd1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mul.q",      1, 0x00100093, 0x0fec006c, F(RR1),  4, "dGG1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mul.q",      1, 0x00140093, 0x0fe8006c, F(RR1),  4, "dgg1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mul.q",      1, 0x00600093, 0x0f9c006c, F(RR1),  4, "DdG1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mul.q",      1, 0x00640093, 0x0f98006c, F(RR1),  4, "Ddg1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mul.q",      1, 0x006c0093, 0x0f90006c, F(RR1),  4, "Ddd1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mul.u",      1, 0x00400053, 0x0fa000ac, F(RC),   3, "Ddn",   "132",
		 TRICORE_V1_2_UP, INDICES},
  {"mul.u",      1, 0x00680073, 0x0f97008c, F(RR2),  3, "Ddd",   "132",
		 TRICORE_V1_2_UP, INDICES},
  {"mulm",       1, 0x00600053, 0x0f8000ac, F(RC),   3, "Dd9",   "132",
		 TRICORE_RIDER_A, INDICES},
  {"mulm",       1, 0x06a00073, 0x095f008c, F(RR),   3, "Ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"mulm.h",     1, 0x007000b3, 0x0f8c004c, F(RR1),  4, "DdL1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mulm.h",     1, 0x007400b3, 0x0f88004c, F(RR1),  4, "Ddl1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mulm.h",     1, 0x007800b3, 0x0f84004c, F(RR1),  4, "Dd-1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mulm.h",     1, 0x007c00b3, 0x0f80004c, F(RR1),  4, "Dd+1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mulm.u",     1, 0x00400053, 0x0fa000ac, F(RC),   3, "Ddn",   "132",
		 TRICORE_RIDER_A, INDICES},
  {"mulm.u",     1, 0x06800073, 0x097f008c, F(RR),   3, "Ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"mulms.h",    1, 0x00f000b3, 0x0f0c004c, F(RR1),  4, "DdL1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mulms.h",    1, 0x00f400b3, 0x0f08004c, F(RR1),  4, "Ddl1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mulms.h",    1, 0x00f800b3, 0x0f04004c, F(RR1),  4, "Dd-1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mulms.h",    1, 0x00fc00b3, 0x0f00004c, F(RR1),  4, "Dd+1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mulr.h",     1, 0x00c000b3, 0x0f3c004c, F(RR),   4, "ddd1",  "1432",
		 TRICORE_RIDER_A, INDICES},
  {"mulr.h",     1, 0x003000b3, 0x0fcc004c, F(RR1),  4, "ddL1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mulr.h",     1, 0x003400b3, 0x0fc8004c, F(RR1),  4, "ddl1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mulr.h",     1, 0x003800b3, 0x0fc4004c, F(RR1),  4, "dd-1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mulr.h",     1, 0x003c00b3, 0x0fc0004c, F(RR1),  4, "dd+1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mulr.q",     1, 0x00600093, 0x0f9c006c, F(RR),   4, "ddd1",  "1432",
		 TRICORE_RIDER_A, INDICES},
  {"mulr.q",     1, 0x00180093, 0x0fe4006c, F(RR1),  4, "dGG1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"mulr.q",     1, 0x001c0093, 0x0fe0006c, F(RR1),  4, "dgg1",  "1432",
		 TRICORE_V1_2_UP, INDICES},
  {"muls",       1, 0x00a00053, 0x0f4000ac, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"muls",       1, 0x08a00073, 0x075f008c, F(RR),   3, "ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"muls",       1, 0x008a0073, 0x0f75008c, F(RR2),  3, "ddd",   "132",
		 TRICORE_V1_2_UP, INDICES},
  {"muls.u",     1, 0x00800053, 0x0f6000ac, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"muls.u",     1, 0x08800073, 0x077f008c, F(RR),   3, "ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"muls.u",     1, 0x00880073, 0x0f77008c, F(RR2),  3, "ddd",   "132",
		 TRICORE_V1_2_UP, INDICES},
  {"nand",       1, 0x0090000f, 0x0f6f00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"nand",       1, 0x0120008f, 0x0ec00070, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"nand.t",     1, 0x00000007, 0x006000f8, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"ne",         1, 0x0110000b, 0x0eef00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"ne",         1, 0x0220008b, 0x0dc00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"ne.a",       1, 0x04100001, 0x0bef00fe, F(RR),   3, "daa",   "143",
		 TRICORE_GENERIC, INDICES},
  {"nez.a",      1, 0x04900001, 0x0b6ff0fe, F(RR),   2, "da",    "14",
		 TRICORE_GENERIC, INDICES},
  {"nop",        0, 0x00000000, 0xffffffff, F(SR),   0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"nop",        1, 0x0000000d, 0xfffffff2, F(SYS),  0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"nor",        0, 0x00000036, 0xfffff0c9, F(SR),   1, "d",     "1",
		 TRICORE_RIDER_A, INDICES},
  {"nor",        0, 0x00000046, 0xfffff0b9, F(SR),   1, "d",     "1",
		 TRICORE_V1_2_UP, INDICES},
  {"nor",        1, 0x00b0000f, 0x0f4f00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"nor",        1, 0x0160008f, 0x0e800070, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"nor.t",      1, 0x00400087, 0x00200078, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"or",         0, 0x00000056, 0xffff00a9, F(SRR),  2, "dd",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"or",         0, 0x000000a6, 0xffff0059, F(SRR),  2, "dd",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"or",         0, 0x000000d6, 0xffff0029, F(SC),   2, "i8",    "01",
		 TRICORE_RIDER_A, INDICES},
  {"or",         0, 0x00000096, 0xffff0069, F(SC),   2, "i8",    "01",
		 TRICORE_V1_2_UP, INDICES},
  {"or",         1, 0x00a0000f, 0x0f5f00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"or",         1, 0x0140008f, 0x0ea00070, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"or.and.t",   1, 0x000000c7, 0x00600038, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"or.andn.t",  1, 0x006000c7, 0x00000038, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"or.eq",      1, 0x0270000b, 0x0d8f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"or.eq",      1, 0x04e0008b, 0x0b000074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"or.ge",      1, 0x02b0000b, 0x0d4f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"or.ge",      1, 0x0560008b, 0x0a800074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"or.ge.u",    1, 0x02c0000b, 0x0d3f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"or.ge.u",    1, 0x0580008b, 0x0a600074, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"or.lt",      1, 0x0290000b, 0x0d6f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"or.lt",      1, 0x0520008b, 0x0ac00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"or.lt.u",    1, 0x02a0000b, 0x0d5f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"or.lt.u",    1, 0x0540008b, 0x0aa00074, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"or.ne",      1, 0x0280000b, 0x0d7f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"or.ne",      1, 0x0500008b, 0x0ae00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"or.nor.t",   1, 0x004000c7, 0x00200038, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"or.or.t",    1, 0x002000c7, 0x00400038, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"or.t",       1, 0x00200087, 0x00400078, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"orn",        1, 0x00f0000f, 0x0f0f00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"orn",        1, 0x01e0008f, 0x0e000070, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"orn.t",      1, 0x00200007, 0x004000f8, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"pack",       1, 0x0000006b, 0x00fff094, F(RRR),  3, "dDd",   "125",
		 TRICORE_GENERIC, INDICES},
  {"parity",     1, 0x0080004b, 0x0f7ff0b4, F(RR),   2, "dd",    "14",
		 TRICORE_RIDER_A, INDICES},
  {"parity",     1, 0x0020004b, 0x0fdff0b4, F(RR),   2, "dd",    "14",
		 TRICORE_V1_2_UP, INDICES},
  {"popcnt.w",   1, 0x0220004b, 0x0ddff0b4, F(RR),   2, "dd",    "14",
		 TRICORE_V1_6_2_UP, INDICES},
  {"q31tof",     1, 0x0151004b, 0x0eae00b4, F(RR),   3, "ddd",   "143",
		 TRICORE_V1_3_UP, INDICES},
  {"qseed.f",    1, 0x0191004b, 0x0e6ef0b4, F(RR),   2, "dd",    "14",
		 TRICORE_V1_3_UP, INDICES},
  {"restore",    1, 0x0380000d, 0xfc7ff0f2, F(SYS),  1, "d",     "1",
  		 TRICORE_V1_6_UP, INDICES},
  {"ret",        0, 0x00009000, 0xffff6fff, F(SR),   0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"ret",        1, 0x0140000d, 0xfebffff2, F(SYS),  0, "",      "",
		 TRICORE_RIDER_A, INDICES},
  {"ret",        1, 0x0180000d, 0xfe7ffff2, F(SYS),  0, "",      "",
		 TRICORE_V1_2_UP, INDICES},
  {"rfe",        0, 0x00008000, 0xffff7fff, F(SR),   0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"rfe",        1, 0x0180000d, 0xfe7ffff2, F(SYS),  0, "",      "",
		 TRICORE_RIDER_A, INDICES},
  {"rfe",        1, 0x01c0000d, 0xfe3ffff2, F(SYS),  0, "",      "",
		 TRICORE_V1_2_UP, INDICES},
  {"rfm",        1, 0x0140000d, 0xfebffff2, F(SYS),  0, "",      "",
		 TRICORE_V1_2_UP, INDICES},
  {"rslcx",      1, 0x0240000d, 0xfdbffff2, F(SYS),  0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"rstv",       1, 0x0000002f, 0xffffffd0, F(SYS),  0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"rsub",       0, 0x000050d2, 0xffffa02d, F(SR),   1, "d",     "1",
		 TRICORE_RIDER_A, INDICES},
  {"rsub",       0, 0x00005032, 0xffffa0cd, F(SR),   1, "d",     "1",
		 TRICORE_V1_2_UP, INDICES},
  {"rsub",       1, 0x0100008b, 0x0ee00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"rsubs",      1, 0x0140008b, 0x0ea00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"rsubs.u",    1, 0x0160008b, 0x0e800074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"sat.b",      0, 0x000000d2, 0xfffff02d, F(SR),   1, "d",     "1",
		 TRICORE_RIDER_A, INDICES},
  {"sat.b",      0, 0x00000032, 0xfffff0cd, F(SR),   1, "d",     "1",
		 TRICORE_V1_2_UP, INDICES},
  {"sat.b",      1, 0x05e0000b, 0x0a1ff0f4, F(RR),   2, "dd",    "14",
		 TRICORE_GENERIC, INDICES},
  {"sat.bu",     0, 0x000010d2, 0xffffe02d, F(SR),   1, "d",     "1",
		 TRICORE_RIDER_A, INDICES},
  {"sat.bu",     0, 0x00001032, 0xffffe0cd, F(SR),   1, "d",     "1",
		 TRICORE_V1_2_UP, INDICES},
  {"sat.bu",     1, 0x05f0000b, 0x0a0ff0f4, F(RR),   2, "dd",    "14",
		 TRICORE_GENERIC, INDICES},
  {"sat.h",      0, 0x000020d2, 0xffffd02d, F(SR),   1, "d",     "1",
		 TRICORE_RIDER_A, INDICES},
  {"sat.h",      0, 0x00002032, 0xffffd0cd, F(SR),   1, "d",     "1",
		 TRICORE_V1_2_UP, INDICES},
  {"sat.h",      1, 0x07e0000b, 0x081ff0f4, F(RR),   2, "dd",    "14",
		 TRICORE_GENERIC, INDICES},
  {"sat.hu",     0, 0x000030d2, 0xffffc02d, F(SR),   1, "d",     "1",
		 TRICORE_RIDER_A, INDICES},
  {"sat.hu",     0, 0x00003032, 0xffffc0cd, F(SR),   1, "d",     "1",
		 TRICORE_V1_2_UP, INDICES},
  {"sat.hu",     1, 0x07f0000b, 0x080ff0f4, F(RR),   2, "dd",    "14",
		 TRICORE_GENERIC, INDICES},
  {"sel",        1, 0x0040002b, 0x00bf00d4, F(RRR),  4, "dddd",  "1254",
		 TRICORE_GENERIC, INDICES},
  {"sel",        1, 0x008000ab, 0x00600054, F(RCR),  4, "ddd9",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"sel.a",      1, 0x00400021, 0x00bf00de, F(RRR),  4, "adaa",  "1254",
		 TRICORE_RIDER_A, INDICES},
  {"sel.a",      1, 0x008000a1, 0x0060005e, F(RCR),  4, "ada9",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"seln",       1, 0x0050002b, 0x00af00d4, F(RRR),  4, "dddd",  "1254",
		 TRICORE_GENERIC, INDICES},
  {"seln",       1, 0x00a000ab, 0x00400054, F(RCR),  4, "ddd9",  "1243",
		 TRICORE_GENERIC, INDICES},
  {"seln.a",     1, 0x00500021, 0x00af00de, F(RRR),  4, "adaa",  "1254",
		 TRICORE_RIDER_A, INDICES},
  {"seln.a",     1, 0x00a000a1, 0x0040005e, F(RCR),  4, "ada9",  "1243",
		 TRICORE_RIDER_A, INDICES},
  {"sh",         0, 0x00000026, 0xffff00d9, F(SRC),  2, "d4",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"sh",         0, 0x00000006, 0xffff00f9, F(SRC),  2, "d4",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"sh",         1, 0x0000000f, 0x0fff00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"sh",         1, 0x0000008f, 0x0fe00070, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"sh.and.t",   1, 0x00000027, 0x006000d8, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"sh.andn.t",  1, 0x00600027, 0x000000d8, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"sh.b",       1, 0x0200000f, 0x0dff00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"sh.b",       1, 0x0400008f, 0x0be00070, F(RC),   3, "dd9",   "132",
		 TRICORE_RIDER_A, INDICES},
  {"sh.eq",      1, 0x0370000b, 0x0c8f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"sh.eq",      1, 0x06e0008b, 0x09000074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"sh.ge",      1, 0x03b0000b, 0x0c4f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"sh.ge",      1, 0x0760008b, 0x08800074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"sh.ge.u",    1, 0x03c0000b, 0x0c3f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"sh.ge.u",    1, 0x0780008b, 0x08600074, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"sh.h",       1, 0x0400000f, 0x0bff00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"sh.h",       1, 0x0800008f, 0x07e00070, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"sh.lt",      1, 0x0390000b, 0x0c6f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"sh.lt",      1, 0x0720008b, 0x08c00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"sh.lt.u",    1, 0x03a0000b, 0x0c5f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"sh.lt.u",    1, 0x0740008b, 0x08a00074, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"sh.nand.t",  1, 0x000000a7, 0x00600058, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"sh.ne",      1, 0x0380000b, 0x0c7f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"sh.ne",      1, 0x0700008b, 0x08e00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"sh.nor.t",   1, 0x00400027, 0x002000d8, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"sh.or.t",    1, 0x00200027, 0x004000d8, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"sh.orn.t",   1, 0x002000a7, 0x00400058, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"sh.xnor.t",  1, 0x004000a7, 0x00200058, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"sh.xor.t",   1, 0x006000a7, 0x00000058, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"sha",        0, 0x000000a6, 0xffff0059, F(SRC),  2, "d4",    "21",
		 TRICORE_RIDER_A, INDICES},
  {"sha",        0, 0x00000086, 0xffff0079, F(SRC),  2, "d4",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"sha",        1, 0x0010000f, 0x0fef00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"sha",        1, 0x0020008f, 0x0fc00070, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"sha.b",      1, 0x0210000f, 0x0def00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"sha.b",      1, 0x0420008f, 0x0bc00070, F(RC),   3, "dd9",   "132",
		 TRICORE_RIDER_A, INDICES},
  {"sha.h",      1, 0x0410000f, 0x0bef00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"sha.h",      1, 0x0820008f, 0x07c00070, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"shas",       1, 0x0020000f, 0x0fdf00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"shas",       1, 0x0040008f, 0x0fa00070, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"shuffle",    1, 0x00e0008f, 0x0f000070, F(RC),   3, "dd9",   "132",
		 TRICORE_V1_6_2_UP, INDICES},
  {"st.a",       0, 0x000000f8, 0xffff0007, F(SC),   3, "&kI",   "010",
  		 TRICORE_V1_2_UP, INDICES},
  {"st.a",       0, 0x00000018, 0xffff00e7, F(SRO),  3, "@6I",   "120",
		 TRICORE_RIDER_A, INDICES},
  {"st.a",       0, 0x000000ec, 0xffff0013, F(SRO),  3, "@6I",   "120",
		 TRICORE_V1_2_UP, INDICES},
  {"st.a",       0, 0x0000002c, 0xffff00d3, F(SSRO), 3, "S6a",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"st.a",       0, 0x000000e8, 0xffff0017, F(SSRO), 3, "S6a",   "012",
		 TRICORE_V1_2_UP, INDICES},
  {"st.a",       0, 0x00000054, 0xffff00ab, F(SSR),  2, ">a",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"st.a",       0, 0x000000e4, 0xffff001b, F(SSR),  2, ">a",    "12",
		 TRICORE_V1_2_UP, INDICES},
  {"st.a",       0, 0x00000084, 0xffff007b, F(SSR),  2, "@a",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"st.a",       0, 0x000000f4, 0xffff000b, F(SSR),  2, "@a",    "12",
		 TRICORE_V1_2_UP, INDICES},
  {"st.a",       1, 0x000000b5, 0x0000004a, F(BOL),  3, "@wa",   "213",
		 TRICORE_V1_6_UP, INDICES}, // TC1.6
  {"st.a",       1, 0x01800089, 0x0e400076, F(BO),   3, ">0a",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.a",       1, 0x018000a9, 0xfe7f0056, F(BO),   2, "#a",    "23",
		 TRICORE_GENERIC, INDICES},
  {"st.a",       1, 0x05800089, 0x0a400076, F(BO),   3, "<0a",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.a",       1, 0x058000a9, 0x0a400056, F(BO),   3, "*0a",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.a",       1, 0x080000a5, 0x0400005a, F(ABS),  2, "ta",    "12",
		 TRICORE_GENERIC, INDICES},
  {"st.a",       1, 0x09800089, 0x06400076, F(BO),   3, "@0a",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.b",       0, 0x00000078, 0xffff0087, F(SSR),  2, "@d",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"st.b",       0, 0x00000034, 0xffff00cb, F(SSR),  2, "@d",    "12",
		 TRICORE_V1_2_UP, INDICES},
  {"st.b",       0, 0x0000008c, 0xffff0073, F(SSRO), 3, "Sfd",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"st.b",       0, 0x00000028, 0xffff00d7, F(SSRO), 3, "Sfd",   "012",
		 TRICORE_V1_2_UP, INDICES},
  {"st.b",       0, 0x000000a8, 0xffff0057, F(SRO),  3, "@fi",   "120",
		 TRICORE_RIDER_A, INDICES},
  {"st.b",       0, 0x0000002c, 0xffff00d3, F(SRO),  3, "@fi",   "120",
		 TRICORE_V1_2_UP, INDICES},
  {"st.b",       0, 0x000000e4, 0xffff001b, F(SSR),  2, ">d",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"st.b",       0, 0x00000024, 0xffff00db, F(SSR),  2, ">d",    "12",
		 TRICORE_V1_2_UP, INDICES},
  {"st.b",       1, 0x000000e9, 0x00000016, F(BOL),  3, "@wd",   "213",
		 TRICORE_V1_6_UP, INDICES}, // TC1.6
  {"st.b",       1, 0x00000025, 0x0c0000da, F(ABS),  2, "td",    "12",
		 TRICORE_GENERIC, INDICES},
  {"st.b",       1, 0x00000089, 0x0fc00076, F(BO),   3, ">0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.b",       1, 0x000000a9, 0xffff0056, F(BO),   2, "#d",    "23",
		 TRICORE_GENERIC, INDICES},
  {"st.b",       1, 0x04000089, 0x0bc00076, F(BO),   3, "<0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.b",       1, 0x040000a9, 0x0bc00056, F(BO),   3, "*0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.b",       1, 0x08000089, 0x07c00076, F(BO),   3, "@0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.d",       1, 0x01400089, 0x0e800076, F(BO),   3, ">0D",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.d",       1, 0x014000a9, 0xfebf0056, F(BO),   2, "#D",    "23",
		 TRICORE_GENERIC, INDICES},
  {"st.d",       1, 0x040000a5, 0x0800005a, F(ABS),  2, "tD",    "12",
		 TRICORE_GENERIC, INDICES},
  {"st.d",       1, 0x05400089, 0x0a800076, F(BO),   3, "<0D",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.d",       1, 0x054000a9, 0x0a800056, F(BO),   3, "*0D",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.d",       1, 0x09400089, 0x06800076, F(BO),   3, "@0D",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.d",       1, 0x09400089, 0xf6bf0076, F(BO),   2, "@D",    "23",
		 TRICORE_GENERIC, INDICES},
  {"st.da",      1, 0x01c00089, 0x0e000076, F(BO),   3, ">0A",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.da",      1, 0x01c000a9, 0xfe3f0056, F(BO),   2, "#A",    "23",
		 TRICORE_GENERIC, INDICES},
  {"st.da",      1, 0x05c00089, 0x0a000076, F(BO),   3, "<0A",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.da",      1, 0x05c000a9, 0x0a000056, F(BO),   3, "*0A",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.da",      1, 0x09c00089, 0x06000076, F(BO),   3, "@0A",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.da",      1, 0x09c00089, 0xf63f0076, F(BO),   2, "@A",    "23",
		 TRICORE_GENERIC, INDICES},
  {"st.da",      1, 0x0c0000a5, 0x0000005a, F(ABS),  2, "tA",    "12",
		 TRICORE_GENERIC, INDICES},
  {"st.h",       0, 0x00000014, 0xffff00eb, F(SSR),  2, ">d",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"st.h",       0, 0x000000a4, 0xffff005b, F(SSR),  2, ">d",    "12",
		 TRICORE_V1_2_UP, INDICES},
  {"st.h",       0, 0x0000004c, 0xffff00b3, F(SSRO), 3, "Svd",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"st.h",       0, 0x000000a8, 0xffff0057, F(SSRO), 3, "Svd",   "012",
		 TRICORE_V1_2_UP, INDICES},
  {"st.h",       0, 0x00000068, 0xffff0097, F(SRO),  3, "@vi",   "120",
		 TRICORE_RIDER_A, INDICES},
  {"st.h",       0, 0x000000ac, 0xffff0053, F(SRO),  3, "@vi",   "120",
		 TRICORE_V1_2_UP, INDICES},
  {"st.h",       0, 0x000000f8, 0xffff0007, F(SSR),  2, "@d",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"st.h",       0, 0x000000b4, 0xffff004b, F(SSR),  2, "@d",    "12",
		 TRICORE_V1_2_UP, INDICES},
  {"st.h",       1, 0x000000f9, 0x00000006, F(BOL),  3, "@wd",   "213",
		 TRICORE_V1_6_UP, INDICES}, // TC1.6
  {"st.h",       1, 0x00800089, 0x0f400076, F(BO),   3, ">0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.h",       1, 0x008000a9, 0xff7f0056, F(BO),   2, "#d",    "23",
		 TRICORE_GENERIC, INDICES},
  {"st.h",       1, 0x04800089, 0x0b400076, F(BO),   3, "<0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.h",       1, 0x048000a9, 0x0b400056, F(BO),   3, "*0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.h",       1, 0x08000025, 0x040000da, F(ABS),  2, "td",    "12",
		 TRICORE_GENERIC, INDICES},
  {"st.h",       1, 0x08800089, 0x07400076, F(BO),   3, "@0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.q",       1, 0x00000065, 0x0c00009a, F(ABS),  2, "td",    "12",
		 TRICORE_GENERIC, INDICES},
  {"st.q",       1, 0x02000089, 0x0dc00076, F(BO),   3, ">0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.q",       1, 0x020000a9, 0xfdff0056, F(BO),   2, "#d",    "23",
		 TRICORE_GENERIC, INDICES},
  {"st.q",       1, 0x06000089, 0x09c00076, F(BO),   3, "<0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.q",       1, 0x060000a9, 0x09c00056, F(BO),   3, "*0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.q",       1, 0x0a000089, 0x05c00076, F(BO),   3, "@0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.q",       1, 0x0a000089, 0xf5ff0076, F(BO),   2, "@d",    "23",
		 TRICORE_GENERIC, INDICES},
  {"st.t",       1, 0x000000d5, 0x0c00002a, F(ABSB), 3, "t31",   "132",
		 TRICORE_GENERIC, INDICES},
  {"st.w",       0, 0x00000078, 0xffff0087, F(SC),   3, "&ki",   "010",
		 TRICORE_V1_2_UP, INDICES},
  {"st.w",       0, 0x00000004, 0xffff00fb, F(SSR),  2, "@d",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"st.w",       0, 0x00000074, 0xffff008b, F(SSR),  2, "@d",    "12",
		 TRICORE_V1_2_UP, INDICES},
  {"st.w",       0, 0x00000094, 0xffff006b, F(SSR),  2, ">d",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"st.w",       0, 0x00000064, 0xffff009b, F(SSR),  2, ">d",    "12",
		 TRICORE_V1_2_UP, INDICES},
  {"st.w",       0, 0x000000cc, 0xffff0033, F(SSRO), 3, "S6d",   "012",
		 TRICORE_RIDER_A, INDICES},
  {"st.w",       0, 0x00000068, 0xffff0097, F(SSRO), 3, "S6d",   "012",
		 TRICORE_V1_2_UP, INDICES},
  {"st.w",       0, 0x000000e8, 0xffff0017, F(SRO),  3, "@6i",   "120",
		 TRICORE_RIDER_A, INDICES},
  {"st.w",       0, 0x0000006c, 0xffff0093, F(SRO),  3, "@6i",   "120",
		 TRICORE_V1_2_UP, INDICES},
  {"st.w",       1, 0x00000059, 0x000000a6, F(BOL),  3, "@wd",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.w",       1, 0x000000a5, 0x0c00005a, F(ABS),  2, "td",    "12",
		 TRICORE_GENERIC, INDICES},
  {"st.w",       1, 0x01000089, 0x0ec00076, F(BO),   3, ">0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.w",       1, 0x010000a9, 0xfeff0056, F(BO),   2, "#d",    "23",
		 TRICORE_GENERIC, INDICES},
  {"st.w",       1, 0x05000089, 0x0ac00076, F(BO),   3, "<0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.w",       1, 0x050000a9, 0x0ac00056, F(BO),   3, "*0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"st.w",       1, 0x09000089, 0x06c00076, F(BO),   3, "@0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"stlcx",      1, 0x00000015, 0x0c000fea, F(ABS),  1, "t",     "1",
		 TRICORE_GENERIC, INDICES},
  {"stlcx",      1, 0x09800049, 0x06400fb6, F(BO),   2, "@0",    "21",
		 TRICORE_GENERIC, INDICES},
  {"stucx",      1, 0x04000015, 0x08000fea, F(ABS),  1, "t",     "1",
		 TRICORE_GENERIC, INDICES},
  {"stucx",      1, 0x09c00049, 0x06000fb6, F(BO),   2, "@0",    "21",
		 TRICORE_GENERIC, INDICES},
  {"sub",        0, 0x00000052, 0xffff00ad, F(SRR),  3, "did",   "201",
		 TRICORE_V1_2_UP, INDICES},
  {"sub",        0, 0x0000005a, 0xffff00a5, F(SRR),  3, "idd",   "021",
		 TRICORE_GENERIC, INDICES},
  {"sub",        0, 0x000000a2, 0xffff005d, F(SRR),  2, "dd",    "21",
		 TRICORE_GENERIC, INDICES},
  {"sub",        1, 0x0080000b, 0x0f7f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"sub.a",      0, 0x00000040, 0xffff00bf, F(SC),   2, "P8",    "01",
		 TRICORE_RIDER_A, INDICES},
  {"sub.a",      0, 0x00000020, 0xffff00df, F(SC),   2, "P8",    "01",
		 TRICORE_V1_2_UP, INDICES},
  {"sub.a",      1, 0x00200001, 0x0fdf00fe, F(RR),   3, "aaa",   "143",
		 TRICORE_GENERIC, INDICES},
  {"sub.b",      1, 0x0480000b, 0x0b7f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"sub.f",      1, 0x0031006b, 0x00cef094, F(RRR),  3, "ddd",   "125",
		 TRICORE_V1_3_UP, INDICES},
  {"sub.h",      1, 0x0680000b, 0x097f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"subc",       1, 0x00d0000b, 0x0f2f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"subs",       0, 0x00000062, 0xffff009d, F(SRR),  2, "dd",    "21",
		 TRICORE_GENERIC, INDICES},
  {"subs",       1, 0x00a0000b, 0x0f5f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"subs.b",     1, 0x04a0000b, 0x0b5f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"subs.bu",    1, 0x04b0000b, 0x0b4f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_RIDER_A, INDICES},
  {"subs.h",     1, 0x06a0000b, 0x095f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"subs.hu",    1, 0x06b0000b, 0x094f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"subs.u",     1, 0x00b0000b, 0x0f4f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"subsc.a",    1, 0x06100001, 0x09ec00fe, F(RR),   4, "aad2",  "1432",
		 TRICORE_RIDER_A, INDICES},
  {"subx",       1, 0x00c0000b, 0x0f3f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"svlcx",      1, 0x0200000d, 0xfdfffff2, F(SYS),  0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"swap.a",     1, 0x00800049, 0x0f4000b6, F(BO),   3, ">0a",   "213",
		 TRICORE_RIDER_A, INDICES},
  {"swap.a",     1, 0x00800069, 0xff7f0096, F(BO),   2, "#a",    "23",
		 TRICORE_RIDER_A, INDICES},
  {"swap.a",     1, 0x04800049, 0x0b4000b6, F(BO),   3, "<0a",   "213",
		 TRICORE_RIDER_A, INDICES},
  {"swap.a",     1, 0x04800069, 0x0b400096, F(BO),   3, "*0a",   "213",
		 TRICORE_RIDER_A, INDICES},
  {"swap.a",     1, 0x080000e5, 0x0400001a, F(ABS),  2, "ta",    "12",
		 TRICORE_RIDER_A, INDICES},
  {"swap.a",     1, 0x08800049, 0x074000b6, F(BO),   3, "@0a",   "213",
		 TRICORE_RIDER_A, INDICES},
  {"swap.w",     1, 0x00000049, 0x0fc000b6, F(BO),   3, ">0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"swap.w",     1, 0x00000069, 0xffff0096, F(BO),   2, "#d",    "23",
		 TRICORE_GENERIC, INDICES},
  {"swap.w",     1, 0x000000e5, 0x0c00001a, F(ABS),  2, "td",    "12",
		 TRICORE_GENERIC, INDICES},
  {"swap.w",     1, 0x04000049, 0x0bc000b6, F(BO),   3, "<0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"swap.w",     1, 0x04000069, 0x0bc00096, F(BO),   3, "*0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"swap.w",     1, 0x08000049, 0x07c000b6, F(BO),   3, "@0d",   "213",
		 TRICORE_GENERIC, INDICES},
  {"swap.w",     1, 0x08000069, 0xf7ff0096, F(BO),   2, "?d",    "23",
  		 TRICORE_V1_6_UP, INDICES},
  {"swapmsk.w",    1, 0x00800049, 0x0f4000b6, F(BO),   3, ">0D",   "213",
  		 TRICORE_V1_6_1_UP, INDICES},
  {"swapmsk.w",    1, 0x00800069, 0xff7f0096, F(BO),   2, "#D",    "23",
  		 TRICORE_V1_6_1_UP, INDICES},
  {"swapmsk.w",    1, 0x04800049, 0x0b4000b6, F(BO),   3, "<0D",   "213",
  		 TRICORE_V1_6_1_UP, INDICES},
  {"swapmsk.w",    1, 0x04800069, 0x0b400096, F(BO),   3, "*0D",   "213",
  		 TRICORE_V1_6_1_UP, INDICES},
  {"swapmsk.w",    1, 0x08800049, 0x074000b6, F(BO),   3, "@0D",   "213",
  		 TRICORE_V1_6_1_UP, INDICES},
  {"swapmsk.w",    1, 0x08800069, 0xf77f0096, F(BO),   2, "?D",    "23",
  		 TRICORE_V1_6_1_UP, INDICES},
  {"syscall",    1, 0x008000ad, 0xff600f52, F(RC),   1, "n",     "2",
		 TRICORE_GENERIC, INDICES},
  {"tlbdemap",   1, 0x00000075, 0xfffff08a, F(RR),   1, "d",     "4",
		 TRICORE_V1_3_UP, INDICES},
  {"tlbflush.a", 1, 0x00400075, 0xffbfff8a, F(RR),   0, "",      "",
		 TRICORE_V1_3_UP, INDICES},
  {"tlbflush.b", 1, 0x00500075, 0xffafff8a, F(RR),   0, "",      "",
		 TRICORE_V1_3_UP, INDICES},
  {"tlbmap",     1, 0x04000075, 0xfbfff08a, F(RR),   1, "D",     "4",
		 TRICORE_V1_3_UP, INDICES},
  {"tlbprobe.a", 1, 0x00800075, 0xff7ff08a, F(RR),   1, "d",     "4",
		 TRICORE_V1_3_UP, INDICES},
  {"tlbprobe.i", 1, 0x00900075, 0xff6ff08a, F(RR),   1, "d",     "4",
		 TRICORE_V1_3_UP, INDICES},
  {"trapsv",     1, 0x0540000d, 0xfabffff2, F(SYS),  0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"trapv",      1, 0x0500000d, 0xfafffff2, F(SYS),  0, "",      "",
		 TRICORE_GENERIC, INDICES},
  {"unpack",     1, 0x0500004b, 0x0afff0b4, F(RR),   2, "Dd",    "14",
		 TRICORE_RIDER_A, INDICES},
  {"unpack",     1, 0x0080004b, 0x0f7ff0b4, F(RR),   2, "Dd",    "14",
		 TRICORE_V1_2_UP, INDICES},
  {"updfl",      1, 0x00c1004b, 0x0f3ef0b4, F(RR),   1, "d",     "5",
		 TRICORE_V1_3_UP, INDICES},
  {"utof",       1, 0x0161004b, 0x0e9ef0b4, F(RR),   2, "dd",    "14",
		 TRICORE_V1_3_UP, INDICES},
  {"wait",       1, 0x0580000d, 0xfa7ffff2, F(SYS),  0, "",      "",
		 TRICORE_V1_6_1_UP, INDICES},
  {"xnor",       1, 0x00d0000f, 0x0f2f00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"xnor",       1, 0x01a0008f, 0x0e400070, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"xnor.t",     1, 0x00400007, 0x002000f8, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
  {"xor",        0, 0x000000c6, 0xffff0039, F(SRR),  2, "dd",    "21",
		 TRICORE_V1_2_UP, INDICES},
  {"xor",        1, 0x00c0000f, 0x0f3f00f0, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"xor",        1, 0x0180008f, 0x0e600070, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"xor.eq",     1, 0x02f0000b, 0x0d0f00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"xor.eq",     1, 0x05e0008b, 0x0a000074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"xor.ge",     1, 0x0330000b, 0x0ccf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"xor.ge",     1, 0x0660008b, 0x09800074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"xor.ge.u",   1, 0x0340000b, 0x0cbf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"xor.ge.u",   1, 0x0680008b, 0x09600074, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"xor.lt",     1, 0x0310000b, 0x0cef00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"xor.lt",     1, 0x0620008b, 0x09c00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"xor.lt.u",   1, 0x0320000b, 0x0cdf00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"xor.lt.u",   1, 0x0640008b, 0x09a00074, F(RC),   3, "ddn",   "132",
		 TRICORE_GENERIC, INDICES},
  {"xor.ne",     1, 0x0300000b, 0x0cff00f4, F(RR),   3, "ddd",   "143",
		 TRICORE_GENERIC, INDICES},
  {"xor.ne",     1, 0x0600008b, 0x09e00074, F(RC),   3, "dd9",   "132",
		 TRICORE_GENERIC, INDICES},
  {"xor.t",      1, 0x00600007, 0x000000f8, F(BIT),  5, "dd5d5", "15342",
		 TRICORE_GENERIC, INDICES},
#undef INDICES
};

const int tricore_numopcodes =
  sizeof tricore_opcodes / sizeof tricore_opcodes[0];

/* Here are the opcodes for the PCP.  The assembler requires that all
   instances of the same mnemonic must be consecutive.  If they aren't,
   the assembler will bomb at runtime.  The disassembler shouldn't care,
   though.  */

struct pcp_opcode pcp_opcodes[] =
{
#define INDICES TRICORE_PCP, 0, 0
  {"add",	0, 0x6000, 0x9e00, 3, 0, 3, "arr",   INDICES},
  {"add",	0, 0x6000, 0x9e00, 3, 0, 3, "rra",   INDICES},
  {"add.f",	0, 0x2000, 0xde04, 1, 0, 3, "rRf",   INDICES},
  {"add.f",	0, 0x2000, 0xde04, 1, 0, 3, "rrf",   INDICES},
  {"add.i",	0, 0x8000, 0x7e00, 4, 0, 2, "re",    INDICES},
  {"add.pi",	0, 0x4000, 0xbe00, 2, 0, 2, "rE",    INDICES},
  {"add.pi",	0, 0x4000, 0xbe00, 2, 0, 2, "re",    INDICES},
  {"and",	0, 0x6a00, 0x9400, 3, 0, 3, "arr",   INDICES},
  {"and",	0, 0x6a00, 0x9400, 3, 0, 3, "rra",   INDICES},
  {"and.f",	0, 0x2a00, 0xd404, 1, 0, 3, "rRf",   INDICES},
  {"and.f",	0, 0x2a00, 0xd404, 1, 0, 3, "rrf",   INDICES},
  {"and.pi",	0, 0x4a00, 0xb400, 2, 0, 2, "rE",    INDICES},
  {"and.pi",	0, 0x4a00, 0xb400, 2, 0, 2, "re",    INDICES},
  {"bcopy",	0, 0x1800, 0xe013, 0, 1, 4, "dscn",  INDICES},
  {"chkb",	0, 0x9c00, 0x6200, 4, 0, 3, "rel",   INDICES},
  {"chkb",	0, 0x9c20, 0x6220, 4, 0, 3, "rek",   INDICES},
  {"clr",	0, 0x9600, 0x6820, 4, 0, 2, "re",    INDICES},
  {"clr.f",	0, 0xb000, 0x4c00, 5, 0, 3, "Ref",   INDICES},
  {"clr.f",	0, 0xb000, 0x4c00, 5, 0, 3, "ref",   INDICES},
  {"comp",	0, 0x6400, 0x9a00, 3, 0, 3, "arr",   INDICES},
  {"comp",	0, 0x6400, 0x9a00, 3, 0, 3, "rra",   INDICES},
  {"comp.f",	0, 0x2400, 0xda04, 1, 0, 3, "rRf",   INDICES},
  {"comp.f",	0, 0x2400, 0xda04, 1, 0, 3, "rrf",   INDICES},
  {"comp.i",	0, 0x8400, 0x7a00, 4, 0, 2, "re",    INDICES},
  {"comp.pi",	0, 0x4400, 0xba00, 2, 0, 2, "rE",    INDICES},
  {"comp.pi",	0, 0x4400, 0xba00, 2, 0, 2, "re",    INDICES},
  {"copy",	0, 0x0800, 0xf000, 0, 1, 5, "dscnf", INDICES},
  {"debug",	0, 0xfc00, 0x0030, 7, 1, 5, "bmopq", INDICES},
  {"debug",	0, 0xfc00, 0x0030, 7, 1, 5, "amopq", INDICES},
  {"dinit",	0, 0xc000, 0x3e07, 6, 0, 2, "rr",    INDICES},
  {"dstep",	0, 0xc200, 0x3c07, 6, 0, 2, "rr",    INDICES},
  {"exb",	0, 0x9c20, 0x6200, 4, 0, 2, "re",    INDICES},
  {"exib",	0, 0x9c00, 0x6220, 4, 0, 2, "re",    INDICES},
  {"exit",      0, 0x1000, 0xe870, 0, 1, 5, "ghijb", INDICES},
  {"exit",      0, 0x1000, 0xe870, 0, 1, 5, "ghija", INDICES},
  {"inb",	0, 0x7a00, 0x8400, 3, 0, 3, "arr",   INDICES},
  {"inb",	0, 0x7a00, 0x8400, 3, 0, 3, "rra",   INDICES},
  {"inb.i",	0, 0x9a00, 0x6420, 4, 0, 2, "re",    INDICES},
  {"jc",	0, 0xe400, 0x1800, 7, 1, 2, "be",    INDICES},
  {"jc",	0, 0xe400, 0x1800, 7, 1, 2, "ae",    INDICES},
  {"jc.a",	1, 0xe800, 0x143f, 7, 1, 2, "be",    INDICES},
  {"jc.a",	1, 0xe800, 0x143f, 7, 1, 2, "ae",    INDICES},
  {"jc.i",	0, 0xf000, 0x0c07, 7, 1, 2, "bR",    INDICES},
  {"jc.i",	0, 0xf000, 0x0c07, 7, 1, 2, "br",    INDICES},
  {"jc.i",	0, 0xf000, 0x0c07, 7, 1, 2, "aR",    INDICES},
  {"jc.i",	0, 0xf000, 0x0c07, 7, 1, 2, "ar",    INDICES},
  {"jc.ia",	0, 0xf400, 0x0807, 7, 1, 2, "bR",    INDICES},
  {"jc.ia",	0, 0xf400, 0x0807, 7, 1, 2, "br",    INDICES},
  {"jc.ia",	0, 0xf400, 0x0807, 7, 1, 2, "aR",    INDICES},
  {"jc.ia",	0, 0xf400, 0x0807, 7, 1, 2, "ar",    INDICES},
  {"jl",	0, 0xe000, 0x1c00, 7, 0, 1, "e",     INDICES},
  {"ld.f",	0, 0x3200, 0xcc04, 1, 0, 3, "rRf",   INDICES},
  {"ld.f",	0, 0x3200, 0xcc04, 1, 0, 3, "rrf",   INDICES},
  {"ld.i",	0, 0x9800, 0x6600, 4, 0, 2, "re",    INDICES},
  {"ld.if",	0, 0xb400, 0x4800, 5, 0, 3, "Ref",   INDICES},
  {"ld.if",	0, 0xb400, 0x4800, 5, 0, 3, "ref",   INDICES},
  {"ld.p",	0, 0x7200, 0x8c00, 3, 0, 3, "arR",   INDICES},
  {"ld.p",	0, 0x7200, 0x8c00, 3, 0, 3, "arr",   INDICES},
  {"ld.p",	0, 0x7200, 0x8c00, 3, 0, 3, "rRa",   INDICES},
  {"ld.p",	0, 0x7200, 0x8c00, 3, 0, 3, "rra",   INDICES},
  {"ld.pi",	0, 0x5200, 0xac00, 2, 0, 2, "rE",    INDICES},
  {"ld.pi",	0, 0x5200, 0xac00, 2, 0, 2, "re",    INDICES},
  {"ldl.dptr",	1, 0x9200, 0x6c3f, 4, 0, 3, "ree",    INDICES},
  {"ldl.il",	1, 0x9200, 0x6c3f, 4, 0, 2, "re",    INDICES},
  {"ldl.iu",	1, 0x9000, 0x6e3f, 4, 0, 2, "re",    INDICES},
  {"mclr.pi",	0, 0x4800, 0xb600, 2, 0, 2, "rE",    INDICES},
  {"mclr.pi",	0, 0x4800, 0xb600, 2, 0, 2, "re",    INDICES},
  {"minit",	0, 0xc400, 0x3a07, 6, 0, 2, "rr",    INDICES},
  {"mov",	0, 0x7800, 0x8600, 3, 0, 3, "arr",   INDICES},
  {"mov",	0, 0x7800, 0x8600, 3, 0, 3, "rra",   INDICES},
  {"mset.pi",	0, 0x4c00, 0xb200, 2, 0, 2, "rE",    INDICES},
  {"mset.pi",	0, 0x4c00, 0xb200, 2, 0, 2, "re",    INDICES},
  {"mstep.l",	0, 0xc600, 0x3807, 6, 0, 2, "rr",    INDICES},
  {"mstep.u",	0, 0xc800, 0x3607, 6, 0, 2, "rr",    INDICES},
  {"mstep32",	0, 0xc600, 0x3807, 6, 0, 2, "rr",    INDICES},
  {"mstep64",	0, 0xc800, 0x3607, 6, 0, 2, "rr",    INDICES},
  {"neg",	0, 0x6600, 0x9800, 3, 0, 3, "arr",   INDICES},
  {"neg",	0, 0x6600, 0x9800, 3, 0, 3, "rra",   INDICES},
  {"nop",	0, 0x0000, 0xffff, 0, 0, 0, "",      INDICES},
  {"not",	0, 0x6800, 0x9600, 3, 0, 3, "arr",   INDICES},
  {"not",	0, 0x6800, 0x9600, 3, 0, 3, "rra",   INDICES},
  {"or",	0, 0x6e00, 0x9000, 3, 0, 3, "arr",   INDICES},
  {"or",	0, 0x6e00, 0x9000, 3, 0, 3, "rra",   INDICES},
  {"or.f",	0, 0x2e00, 0xd004, 1, 0, 3, "rRf",   INDICES},
  {"or.f",	0, 0x2e00, 0xd004, 1, 0, 3, "rrf",   INDICES},
  {"or.pi",	0, 0x4e00, 0xb000, 2, 0, 2, "rE",    INDICES},
  {"or.pi",	0, 0x4e00, 0xb000, 2, 0, 2, "re",    INDICES},
  {"pri",	0, 0x7c00, 0x8200, 3, 0, 3, "arr",   INDICES},
  {"pri",	0, 0x7c00, 0x8200, 3, 0, 3, "rra",   INDICES},
  {"rl",	0, 0x8e00, 0x7020, 4, 0, 2, "re",    INDICES},
  {"rr",	0, 0x8c00, 0x7220, 4, 0, 2, "re",    INDICES},
  {"set",	0, 0x9400, 0x6a20, 4, 0, 2, "re",    INDICES},
  {"set.f",	0, 0xac00, 0x5000, 5, 0, 3, "Ref",   INDICES},
  {"set.f",	0, 0xac00, 0x5000, 5, 0, 3, "ref",   INDICES},
  {"shl",	0, 0x8a00, 0x7420, 4, 0, 2, "re",    INDICES},
  {"shr",	0, 0x8800, 0x7620, 4, 0, 2, "re",    INDICES},
  {"st.f",	0, 0x3400, 0xca04, 1, 0, 3, "rRf",   INDICES},
  {"st.f",	0, 0x3400, 0xca04, 1, 0, 3, "rrf",   INDICES},
  {"st.if",	0, 0xb800, 0x4400, 5, 0, 3, "Ref",   INDICES},
  {"st.if",	0, 0xb800, 0x4400, 5, 0, 3, "ref",   INDICES},
  {"st.p",	0, 0x7400, 0x8a00, 3, 0, 3, "arR",   INDICES},
  {"st.p",	0, 0x7400, 0x8a00, 3, 0, 3, "arr",   INDICES},
  {"st.p",	0, 0x7400, 0x8a00, 3, 0, 3, "rRa",   INDICES},
  {"st.p",	0, 0x7400, 0x8a00, 3, 0, 3, "rra",   INDICES},
  {"st.pi",	0, 0x5400, 0xaa00, 2, 0, 2, "rE",    INDICES},
  {"st.pi",	0, 0x5400, 0xaa00, 2, 0, 2, "re",    INDICES},
  {"sub",	0, 0x6200, 0x9c00, 3, 0, 3, "arr",   INDICES},
  {"sub",	0, 0x6200, 0x9c00, 3, 0, 3, "rra",   INDICES},
  {"sub.f",	0, 0x2200, 0xdc04, 1, 0, 3, "rRf",   INDICES},
  {"sub.f",	0, 0x2200, 0xdc04, 1, 0, 3, "rrf",   INDICES},
  {"sub.i",	0, 0x8200, 0x7c00, 4, 0, 2, "re",    INDICES},
  {"sub.pi",	0, 0x4200, 0xbc00, 2, 0, 2, "rE",    INDICES},
  {"sub.pi",	0, 0x4200, 0xbc00, 2, 0, 2, "re",    INDICES},
  {"xch.f",	0, 0x3600, 0xc804, 1, 0, 3, "rRf",   INDICES},
  {"xch.f",	0, 0x3600, 0xc804, 1, 0, 3, "rrf",   INDICES},
  {"xch.pi",	0, 0x5600, 0xa800, 2, 0, 2, "rE",    INDICES},
  {"xch.pi",	0, 0x5600, 0xa800, 2, 0, 2, "re",    INDICES},
  {"xor",	0, 0x7000, 0x8e00, 3, 0, 3, "arr",   INDICES},
  {"xor",	0, 0x7000, 0x8e00, 3, 0, 3, "rra",   INDICES},
  {"xor.f",	0, 0x3000, 0xce04, 1, 0, 3, "rRf",   INDICES},
  {"xor.f",	0, 0x3000, 0xce04, 1, 0, 3, "rrf",   INDICES},
  {"xor.pi",	0, 0x5000, 0xae00, 2, 0, 2, "rE",    INDICES},
  {"xor.pi",	0, 0x5000, 0xae00, 2, 0, 2, "re",    INDICES}
#undef INDICES
};

const int pcp_numopcodes = sizeof pcp_opcodes / sizeof pcp_opcodes[0];

#define NUMOPCS tricore_numopcodes
#define NUMSFRS tricore_numsfrs
#define NUMPCPOPCS pcp_numopcodes
#define MAX_OPS 5
#define MATCHES_ISA(isa) \
	  (((isa) == TRICORE_GENERIC) \
	   || ((isa & TRICORE_ISA_MASK) & current_isa))

/* Some handy shortcuts.  */

typedef struct tricore_opcode opcode_t;
typedef struct pcp_opcode pcp_opcode_t;
typedef const struct tricore_core_register sfr_t;

/* For faster lookup, we hash instruction opcodes and SFRs.  */

struct insnlist
{
  opcode_t *code;
  struct insnlist *next;
};

/* TriCore insns have only 6 significant bits (because of the 16-bit
   SRRS format), so the hash table needs being restricted to 64 entries.  */

static struct insnlist *insns[64];
static struct insnlist *insnlink;

/* PCP insns have only 5 significant bits (because of encoding group 0).  */

struct pcplist
{
  pcp_opcode_t *code;
  struct pcplist *next;
};

static struct pcplist *pcpinsns[32];
static struct pcplist *pcplink;

/* The hash key for SFRs is their LSB.  */

struct sfrlist
{
  sfr_t *sfr;
  struct sfrlist *next;
};

static struct sfrlist *sfrs[256];
static struct sfrlist *sfrlink;

/* 1 if the hash tables are initialized.  */

static int initialized = 0;

/* Which TriCore instruction set architecture are we dealing with?  */

static tricore_isa current_isa = TRICORE_V1_2;

/* If we can find the instruction matching a given opcode, we decode
   its operands and store them in the following structure.  */

struct decoded_insn
{
  opcode_t *code;
  unsigned long opcode;
  int regs[MAX_OPS];
  unsigned long long cexp[MAX_OPS];
};

static struct decoded_insn dec_insn;

/* Forward declarations of decoding functions.  */

static void decode_abs  (void);
static void decode_absb  (void);
static void decode_b  (void);
static void decode_bit  (void);
static void decode_bo  (void);
static void decode_bol  (void);
static void decode_brc  (void);
static void decode_brn  (void);
static void decode_brr  (void);
static void decode_rc  (void);
static void decode_rcpw  (void);
static void decode_rcr  (void);
static void decode_rcrr  (void);
static void decode_rcrw  (void);
static void decode_rlc  (void);
static void decode_rr  (void);
static void decode_rr1  (void);
static void decode_rr2  (void);
static void decode_rrpw  (void);
static void decode_rrr  (void);
static void decode_rrr1  (void);
static void decode_rrr2  (void);
static void decode_rrrr  (void);
static void decode_rrrw  (void);
static void decode_sys  (void);
static void decode_sb  (void);
static void decode_sbc  (void);
static void decode_sbr  (void);
static void decode_sbrn  (void);
static void decode_sc  (void);
static void decode_slr  (void);
static void decode_slro  (void);
static void decode_sr  (void);
static void decode_src  (void);
static void decode_sro  (void);
static void decode_srr  (void);
static void decode_srrs  (void);
static void decode_ssr  (void);
static void decode_ssro  (void);

#define xmalloc malloc
/* Array of function pointers to decoding functions.  */

static void (*decode[])  (void) =
{
  /* 32-bit formats.  */
  decode_abs, decode_absb, decode_b, decode_bit, decode_bo, decode_bol,
  decode_brc, decode_brn, decode_brr, decode_rc, decode_rcpw, decode_rcr,
  decode_rcrr, decode_rcrw, decode_rlc, decode_rr, decode_rr1, decode_rr2,
  decode_rrpw, decode_rrr, decode_rrr1, decode_rrr2, decode_rrrr,
  decode_rrrw, decode_sys,

  /* 16-bit formats.  */
  decode_sb, decode_sbc, decode_sbr, decode_sbrn, decode_sc, decode_slr,
  decode_slro, decode_sr, decode_src, decode_sro, decode_srr,
  decode_srrs, decode_ssr, decode_ssro
};

/* More forward declarations.  */

static unsigned long extract_off18  (void);
static void init_hash_tables  (void);
static const char *find_core_reg  (unsigned long);
static void print_decoded_insn  (bfd_vma, struct disassemble_info *);
int decode_tricore_insn  (bfd_vma, unsigned long, int,
					struct disassemble_info *);
int decode_pcp_insn  (bfd_vma, bfd_byte [4],
				    struct disassemble_info *);

/* Here come the decoding functions.  If you thought that the encoding
   functions in the assembler were somewhat, umm,  boring, you should
   take a serious look at their counterparts below.  They're even more so!
   *yawn*   */

static unsigned long
extract_off18 (void)
{
  unsigned long o1, o2, o3, o4;
  unsigned long val = dec_insn.opcode;

  o1 = (val & 0x003f0000) >> 16;
  o2 = (val & 0xf0000000) >> 22;
  o3 = (val & 0x03c00000) >> 12;
  o4 = (val & 0x0000f000) << 2;
  return o1 | o2 | o3 | o4;
}

static void
decode_abs (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_ABS_OFF18:
      case FMT_ABS_OFF18_14:
        dec_insn.cexp[i] = extract_off18 ();
        break;

      case FMT_ABS_S1_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf00) >> 8;
	break;
      }
}

static void
decode_absb (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_ABSB_OFF18:
        dec_insn.cexp[i] = extract_off18 ();
        break;

      case FMT_ABSB_B:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x800) >> 11;
	break;

      case FMT_ABSB_BPOS3:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x700) >> 8;
	break;
      }
}

static void
decode_b (void)
{
  int i;
  unsigned long o1, o2;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_B_DISP24:
        o1 = (dec_insn.opcode & 0xffff0000) >> 16;
	o2 = (dec_insn.opcode & 0x0000ff00) << 8;
	dec_insn.cexp[i] = o1 | o2;
	break;
      }
}

static void
decode_bit (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_BIT_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_BIT_P2:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x0f800000) >> 23;
	break;

      case FMT_BIT_P1:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x001f0000) >> 16;
        break;

      case FMT_BIT_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_BIT_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_bo (void)
{
  int i;
  unsigned long o1, o2;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_BO_OFF10:
        o1 = (dec_insn.opcode & 0x003f0000) >> 16;
	o2 = (dec_insn.opcode & 0xf0000000) >> 22;
	dec_insn.cexp[i] = o1 | o2;
        break;

      case FMT_BO_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_BO_S1_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_bol (void)
{
  int i;
  unsigned long o1, o2, o3;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_BOL_OFF16:
        o1 = (dec_insn.opcode & 0x003f0000) >> 16;
	o2 = (dec_insn.opcode & 0xf0000000) >> 22;
	o3 = (dec_insn.opcode & 0x0fc00000) >> 12;
	dec_insn.cexp[i] = o1 | o2 | o3;
        break;

      case FMT_BOL_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_BOL_S1_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_brc (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_BRC_DISP15:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x7fff0000) >> 16;
	break;

      case FMT_BRC_CONST4:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_BRC_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_brn (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_BRN_DISP15:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x7fff0000) >> 16;
	break;

      case FMT_BRN_N:
        dec_insn.cexp[i] =  (dec_insn.opcode & 0x0000f000) >> 12;
	dec_insn.cexp[i] |= (dec_insn.opcode & 0x00000080) >> 3;
	break;

      case FMT_BRN_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_brr (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_BRR_DISP15:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x7fff0000) >> 16;
	break;

      case FMT_BRR_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_BRR_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_rc (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RC_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RC_CONST9:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x001ff000) >> 12;
	break;

      case FMT_RC_CONST10:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x003ff000) >> 12;
        break;

      case FMT_RC_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
      }
}

static void
decode_rcpw (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RCPW_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RCPW_P:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x0f800000) >> 23;
	break;

      case FMT_RCPW_W:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x001f0000) >> 16;
	break;

      case FMT_RCPW_CONST4:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_RCPW_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_rcr (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RCR_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RCR_S3:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f000000) >> 24;
	break;

      case FMT_RCR_CONST9:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x001ff000) >> 12;
	break;

      case FMT_RCR_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_rcrr (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RCRR_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RCRR_S3:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f000000) >> 24;
	break;

      case FMT_RCRR_CONST4:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_RCRR_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_rcrw (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RCRW_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RCRW_S3:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f000000) >> 24;
	break;

      case FMT_RCRW_W:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x001f0000) >> 16;
	break;

      case FMT_RCRW_CONST4:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_RCRW_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_rlc (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RLC_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RLC_CONST16:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x0ffff000) >> 12;
	break;

      case FMT_RLC_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_rr (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RR_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RR_N:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x00030000) >> 16;
	break;

      case FMT_RR_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_RR_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
        break;
      case FMT_RR_D_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_rr1 (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RR1_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RR1_N:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x00030000) >> 16;
	break;

      case FMT_RR1_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_RR1_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_rr2 (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RR2_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RR2_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_RR2_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_rrpw (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RRPW_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RRPW_P:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x0f800000) >> 23;
	break;

      case FMT_RRPW_W:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x001f0000) >> 16;
	break;

      case FMT_RRPW_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_RRPW_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_rrr (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RRR_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RRR_S3:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f000000) >> 24;
	break;

      case FMT_RRR_N:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x00030000) >> 16;
	break;

      case FMT_RRR_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_RRR_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_rrr1 (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RRR1_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RRR1_S3:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f000000) >> 24;
	break;

      case FMT_RRR1_N:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x00030000) >> 16;
	break;

      case FMT_RRR1_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_RRR1_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_rrr2 (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RRR2_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RRR2_S3:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f000000) >> 24;
	break;

      case FMT_RRR2_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_RRR2_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_rrrr (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RRRR_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RRRR_S3:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f000000) >> 24;
	break;

      case FMT_RRRR_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_RRRR_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_rrrw (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_RRRW_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf0000000) >> 28;
	break;

      case FMT_RRRW_S3:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f000000) >> 24;
	break;

      case FMT_RRRW_W:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x001f0000) >> 16;
	break;

      case FMT_RRRW_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0000f000) >> 12;
	break;

      case FMT_RRRW_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_sys (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SYS_S1_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0x00000f00) >> 8;
	break;
      }
}

static void
decode_sb (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SB_DISP8:
        dec_insn.cexp[i] = (dec_insn.opcode & 0xff00) >> 8;
	break;
      }
}

static void
decode_sbc (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SBC_CONST4:
        dec_insn.cexp[i] = (dec_insn.opcode & 0xf000) >> 12;
	break;

      case FMT_SBC_DISP4:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x0f00) >> 8;
        if (dec_insn.code->args[i] == 'x')
          dec_insn.cexp[i] += (dec_insn.opcode & 0x80)? 0x10 : 0;
	break;
      }
}

static void
decode_sbr (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SBR_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf000) >> 12;
	break;

      case FMT_SBR_DISP4:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x0f00) >> 8;
        if (dec_insn.code->args[i] == 'x')
          dec_insn.cexp[i] += (dec_insn.opcode & 0x80)? 0x10 : 0;
	break;
      }
}

static void
decode_sbrn (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SBRN_N:
	if (dec_insn.code->args[i] == '5')
	  {
            dec_insn.cexp[i] =  (dec_insn.opcode & 0xf000) >> 12;
	    dec_insn.cexp[i] |= (dec_insn.opcode & 0x0080) >> 3;
	  }
	else
          dec_insn.cexp[i] =  (dec_insn.opcode & 0xf000) >> 12;
	break;

      case FMT_SBRN_DISP4:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x0f00) >> 8;
	break;
      }
}

static void
decode_sc (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SC_CONST8:
        dec_insn.cexp[i] = (dec_insn.opcode & 0xff00) >> 8;
	break;
      }
}

static void
decode_slr (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SLR_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf000) >> 12;
	break;

      case FMT_SLR_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f00) >> 8;
	break;
      }
}

static void
decode_slro (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SLRO_OFF4:
        dec_insn.cexp[i] = (dec_insn.opcode & 0xf000) >> 12;
	break;

      case FMT_SLRO_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f00) >> 8;
	break;
      }
}

static void
decode_sr (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SR_S1_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f00) >> 8;
	break;
      }
}

static void
decode_src (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SRC_CONST4:
        dec_insn.cexp[i] = (dec_insn.opcode & 0xf000) >> 12;
	break;

      case FMT_SRC_S1_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f00) >> 8;
	break;
      }
}

static void
decode_sro (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SRO_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf000) >> 12;
	break;

      case FMT_SRO_OFF4:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x0f00) >> 8;
	break;
      }
}

static void
decode_srr (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SRR_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf000) >> 12;
	break;

      case FMT_SRR_S1_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f00) >> 8;
	break;
      }
}

static void
decode_srrs (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SRRS_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf000) >> 12;
	break;

      case FMT_SRRS_S1_D:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f00) >> 8;
	break;

      case FMT_SRRS_N:
        dec_insn.cexp[i] = (dec_insn.opcode & 0x00c0) >> 6;
	break;
      }
}

static void
decode_ssr (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SSR_S2:
        dec_insn.regs[i] = (dec_insn.opcode & 0xf000) >> 12;
	break;

      case FMT_SSR_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f00) >> 8;
	break;
      }
}

static void
decode_ssro (void)
{
  int i;

  for (i = 0; i < dec_insn.code->nr_operands; ++i)
    switch (dec_insn.code->fields[i])
      {
      case FMT_SSRO_OFF4:
        dec_insn.cexp[i] = (dec_insn.opcode & 0xf000) >> 12;
	break;

      case FMT_SSRO_S1:
        dec_insn.regs[i] = (dec_insn.opcode & 0x0f00) >> 8;
	break;
      }
}

/* Initialize the hash tables for instructions and SFRs.  */

static void
init_hash_tables (void)
{
  opcode_t *pop;
  pcp_opcode_t *ppop;
  sfr_t *psfr;
  int i, idx;

  insnlink = (struct insnlist *) xmalloc (NUMOPCS * sizeof (struct insnlist));
  pcplink = (struct pcplist *) xmalloc (NUMPCPOPCS * sizeof (struct pcplist));
  sfrlink = (struct sfrlist *) xmalloc (NUMSFRS * sizeof (struct sfrlist));
  memset ((char *) insns, 0, sizeof (insns));
  memset ((char *) insnlink, 0, NUMOPCS * sizeof (struct insnlist));
  memset ((char *) pcpinsns, 0, sizeof (pcpinsns));
  memset ((char *) pcplink, 0, NUMPCPOPCS * sizeof (struct pcplist));
  memset ((char *) sfrs, 0, sizeof (sfrs));
  memset ((char *) sfrlink, 0, NUMSFRS * sizeof (struct sfrlist));

  for (i = 0, pop = tricore_opcodes; i < NUMOPCS; ++i, ++pop)
    {
      if (!MATCHES_ISA (pop->isa))
        continue;

      idx = pop->opcode & 0x3f;
      if (insns[idx])
	insnlink[i].next = insns[idx];
      insns[idx] = &insnlink[i];
      insnlink[i].code = pop;
    }

  for (i = 0, ppop = pcp_opcodes; i < NUMPCPOPCS; ++i, ++ppop)
    {
      idx = (ppop->opcode >> 11) & 0x1f;
      if (pcpinsns[idx])
        pcplink[i].next = pcpinsns[idx];
      pcpinsns[idx] = &pcplink[i];
      pcplink[i].code = ppop;
    }

  for (i = 0, psfr = tricore_sfrs; i < NUMSFRS; ++i, ++psfr)
    {
      if (!MATCHES_ISA (psfr->isa))
        continue;

      idx = psfr->addr & 0xff;
      if (sfrs[idx])
        sfrlink[i].next = sfrs[idx];
      sfrs[idx] = &sfrlink[i];
      sfrlink[i].sfr = psfr;
    }
}

/* Return the name of the core register (SFR) located at offset ADDR.  */

static const char * find_core_reg (unsigned long addr)
{
  struct sfrlist *psfr;
  int idx = addr & 0xff;

  for (psfr = sfrs[idx]; psfr != NULL; psfr = psfr->next)
    if ((psfr->sfr->addr == addr) && MATCHES_ISA (psfr->sfr->isa))
      return psfr->sfr->name;

  return (char *) 0;
}

/* Print the decoded TriCore instruction starting at MEMADDR.  */

static void
print_decoded_insn (bfd_vma memaddr, struct disassemble_info *info)
{
  opcode_t *insn = dec_insn.code;
  int i, needs_creg = 0, need_comma;
  const char *creg;
  bfd_vma abs;
  static bfd_vma next_addr = 0;
  static bfd_boolean expect_lea = FALSE;
#define NO_AREG	16
  static int load_areg[NO_AREG] = {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE};
  static unsigned long load_hi_addr[NO_AREG] = {0};
  static unsigned long load_addr = 0;
  static bfd_boolean print_symbolic_address = FALSE;
#define DPRINT (*info->fprintf_func)
#define DFILE info->stream

  /* Special cases: "nor %dn" / "nor %dn,%dn,0" -> "not %dn"  */
  if (((*insn->name == 'n') && !strcmp (insn->name, "nor"))
      && ((insn->nr_operands == 1)
          || ((insn->nr_operands == 3)
	      && (insn->args[2] == 'n')
              && (dec_insn.regs[0] == dec_insn.regs[1])
	      && (dec_insn.cexp[2] == 0))))
    {
      DPRINT (DFILE, "not %%d%d", dec_insn.regs[0]);
      return;
    }
  else
    DPRINT (DFILE, "%s ", insn->name);

  /* Being a child of the RISC generation, a TriCore-based CPU generally
     must load a 32-bit wide address in two steps, usually by executing
     an instruction sequence like "movh.a %an,hi:sym; lea %am,[%an]lo:sym"
     (an optimizing compiler performing instruction scheduling, such as
     GCC, may insert other instructions between "movh.a" and "lea", but
     that doesn't matter at all, because it doesn't change the execution
     order of the two instructions, and this function can only disassemble
     a single instruction at a time, anyway).  We would like to see which
     address is being loaded (or, more precisely, which symbol lives at
     the address being loaded), so we keep track of "movh.a" and "lea"
     instructions, and print the symbolic address after a "lea" insn
     if we can be reasonably sure that it is part of the load sequence
     described above.  Note that "lea" is used here as a generic insn;
     it actually may also be any load or store instruction.  */
  if (memaddr != next_addr)
    expect_lea = print_symbolic_address = FALSE;
  next_addr = memaddr + (insn->len32 ? 4 : 2);

  if (!strcmp (insn->name, "movh.a"))
    {
      load_areg[dec_insn.regs[0]] = TRUE;
      load_hi_addr[dec_insn.regs[0]] = dec_insn.cexp[1] << 16;
      expect_lea = TRUE;
      print_symbolic_address = FALSE;
    }
  else if (expect_lea
	   && (!strcmp (insn->name, "lea")
	       || !strncmp (insn->name, "ld.", 3)
	       || !strncmp (insn->name, "st.", 3)
	       || !strncmp (insn->name, "swap", 4)
	       || !strcmp (insn->name, "ldmst")))
    {
      if (insn->nr_operands == 3)
	{
	  if ((!strcmp (insn->name, "lea")
	       || !strncmp (insn->name, "ld.", 3)
	       || !strcmp (insn->name, "ldmst"))
		 ) {
	     if ((TRUE == load_areg[dec_insn.regs[1]]))
	    {
	      load_addr = load_hi_addr[dec_insn.regs[1]] + (short) dec_insn.cexp[2];
	      print_symbolic_address = TRUE;
	    }
      }
	  else if (TRUE == load_areg[dec_insn.regs[0]])
	    {
	      load_addr = load_hi_addr[dec_insn.regs[0]] + (short) dec_insn.cexp[1];
	      print_symbolic_address = TRUE;
	    }
	}
    }
  else
    print_symbolic_address = FALSE;

  if (!strncmp(insn->name,"ld.a",4))
		load_areg[dec_insn.regs[0]] = FALSE;
  else
  if (!strncmp(insn->name,"add.a",5)
	|| !strncmp(insn->name,"sub.a",5)
	|| !strcmp(insn->name,"mov.a")
	|| !strncmp(insn->name,"addsc.a",7))
		load_areg[dec_insn.regs[0]] = FALSE;
  else
  if (!strcmp(insn->name,"mov.aa"))
	load_areg[dec_insn.regs[0]] = load_areg[dec_insn.regs[1]];
  else
  if (!strncmp(insn->name,"call",4)) {
	int i = 0;
	for (i = 2; i < 8; i++)
		load_areg[i] = FALSE;
  }
  else
  if (!strncmp(insn->name,"ret",3)) {
	int i = 0;
	for (i = 2; i < 8; i++)
		load_areg[i] = FALSE;
	for (i = 10; i < 16; i++)
		load_areg[i] = FALSE;
  }


  if (!strcmp (insn->name, "mfcr") || !strcmp (insn->name, "mtcr"))
    needs_creg = 1;

  for (i = 0; i < insn->nr_operands; ++i)
    {
      need_comma = (i < (insn->nr_operands - 1));
      switch (insn->args[i])
        {
	case 'd':
	  DPRINT (DFILE, "%%d%d", dec_insn.regs[i]);
	  break;

	case 'g':
	  DPRINT (DFILE, "%%d%dl", dec_insn.regs[i]);
	  break;

	case 'G':
	  DPRINT (DFILE, "%%d%du", dec_insn.regs[i]);
	  break;

	case '-':
	  DPRINT (DFILE, "%%d%dll", dec_insn.regs[i]);
	  break;

	case '+':
	  DPRINT (DFILE, "%%d%duu", dec_insn.regs[i]);
	  break;

	case 'l':
	  DPRINT (DFILE, "%%d%dlu", dec_insn.regs[i]);
	  break;

	case 'L':
	  DPRINT (DFILE, "%%d%dul", dec_insn.regs[i]);
	  break;

	case 'D':
	  DPRINT (DFILE, "%%e%d", dec_insn.regs[i]);
	  break;

	case 'i':
	  DPRINT (DFILE, "%%d15");
	  break;

	case 'a':
	case 'A':
	  if (dec_insn.regs[i] == 10) {
	    DPRINT (DFILE, "%%sp");
 	  }
	  else
	    DPRINT (DFILE, "%%a%d", dec_insn.regs[i]);
	  break;

	case 'I':
	  DPRINT (DFILE, "%%a15");
	  break;

	case 'P':
	  DPRINT (DFILE, "%%sp");
	  break;

	case 'k':
        case '6':
	  dec_insn.cexp[i] <<= 1;
	  /* Fall through. */
	case 'v':
	  dec_insn.cexp[i] <<= 1;
	  /* Fall through. */
	case '1':
	case '2':
	case '3':
	case 'f':
	case '5':
	case '8':
	case 'h':
	case 'n':
	case 'M':
	  DPRINT (DFILE, "%llu", dec_insn.cexp[i]);
	  break;

	case '4':
	  if (dec_insn.cexp[i] & 0x8)
	    dec_insn.cexp[i] |= ~0xf;
	  DPRINT (DFILE, "%lld", dec_insn.cexp[i]);
	  break;

	case 'F':
	  if (dec_insn.cexp[i] & 0x10)
	    dec_insn.cexp[i] |= ~0x1f;
	  DPRINT (DFILE, "%lld", dec_insn.cexp[i]);
	  break;

	case '9':
	  if (dec_insn.cexp[i] & 0x100)
	    dec_insn.cexp[i] |= ~0x1ff;
	  DPRINT (DFILE, "%lld", dec_insn.cexp[i]);
	  break;

	case '0':
	  if (dec_insn.cexp[i] & 0x200)
	    dec_insn.cexp[i] |= ~0x3ff;
	  DPRINT (DFILE, "%lld", dec_insn.cexp[i]);
	  if (print_symbolic_address)
	    {
	      DPRINT (DFILE, " <");
	      (*info->print_address_func) (load_addr, info);
	      DPRINT (DFILE, ">");
	    }
	  break;

	case 'w':
	  if (dec_insn.cexp[i] & 0x8000)
	    dec_insn.cexp[i] |= ~0xffff;
	  DPRINT (DFILE, "%lld", dec_insn.cexp[i]);
	  if (print_symbolic_address)
	    {
	      DPRINT (DFILE, " <");
	      (*info->print_address_func) (load_addr, info);
	      DPRINT (DFILE, ">");
	    }
	  break;

	case 't':
	  abs =  (dec_insn.cexp[i] & 0x00003fff);
	  abs |= (dec_insn.cexp[i] & 0x0003c000) << 14;
	  (*info->print_address_func) (abs, info);
	  break;

	case 'T':
	  abs =  (dec_insn.cexp[i] & 0x000fffff) << 1;
	  abs |= (dec_insn.cexp[i] & 0x00f00000) << 8;
	  (*info->print_address_func) (abs, info);
	  break;

	case 'V':
	  abs =  (dec_insn.cexp[i] & 0x0003ffff) << 14;
	  (*info->print_address_func) (abs, info);
	  break;

	case 'o':
	  if (dec_insn.cexp[i] & 0x4000)
	    dec_insn.cexp[i] |= ~0x7fff;
	  abs = (dec_insn.cexp[i] << 1) + memaddr;
	  (*info->print_address_func) (abs, info);
	  break;

	case 'O':
	  if (dec_insn.cexp[i] & 0x800000)
	    dec_insn.cexp[i] |= ~0xffffff;
	  abs = (dec_insn.cexp[i] << 1) + memaddr;
	  (*info->print_address_func) (abs, info);
	  break;

	case 'R':
	  if (dec_insn.cexp[i] & 0x80)
	    dec_insn.cexp[i] |= ~0xff;
	  abs = (dec_insn.cexp[i] << 1) + memaddr;
	  (*info->print_address_func) (abs, info);
	  break;

	case 'r':
	  dec_insn.cexp[i] |= ~0xf;
	  /* Fall through. */
	case 'm':
	case 'x':
	  abs = (dec_insn.cexp[i] << 1) + memaddr;
	  (*info->print_address_func) (abs, info);
	  break;

	case 'c':
	  needs_creg = 1;
	  /* Fall through. */
	case 'W':
	  if (needs_creg)
	    {
	      creg = find_core_reg (dec_insn.cexp[i]);
	      if (creg)
	        DPRINT (DFILE, "%s", creg);
	      else
	        DPRINT (DFILE, "$0x%04llx (unknown SFR)", dec_insn.cexp[i]);
	    }
	  else
	    DPRINT (DFILE, "%lld", dec_insn.cexp[i]);
	  break;

	case '&':
	  dec_insn.regs[i] = 10;
	  /* Fall through. */
	case '@':
	  if (dec_insn.regs[i] == 10)
	    DPRINT (DFILE, "[%%sp]");
	  else
	    DPRINT (DFILE, "[%%a%d]", dec_insn.regs[i]);
	  if (need_comma)
	    {
	      if (
                  (insn->args[i+1] == 'a') || (insn->args[i+1] == 'd')
                ||
                  (insn->args[i+1] == 'A') || (insn->args[i+1] == 'D'))
	        need_comma = 1;
	      else
	        need_comma = 0;
	    }
	  break;

	case '<':
	  if (dec_insn.regs[i] == 10)
	    DPRINT (DFILE, "[+%%sp]");
	  else
	    DPRINT (DFILE, "[+%%a%d]", dec_insn.regs[i]);
	  need_comma = 0;
	  break;

	case '>':
	  if (dec_insn.regs[i] == 10)
	    DPRINT (DFILE, "[%%sp+]");
	  else
	    DPRINT (DFILE, "[%%a%d+]", dec_insn.regs[i]);
	  if (need_comma)
	    {
	      if ((insn->args[i+1] == 'a') || (insn->args[i+1] == 'd'))
	        need_comma = 1;
	      else
	        need_comma = 0;
	    }
	  break;

	case '*':
	  if (dec_insn.regs[i] == 10)
	    DPRINT (DFILE, "[%%sp+c]");
	  else
	    DPRINT (DFILE, "[%%a%d+c]", dec_insn.regs[i]);
	  need_comma = 0;
	  break;

	case '#':
	  if (dec_insn.regs[i] == 10)
	    DPRINT (DFILE, "[%%sp+r]");
	  else
	    DPRINT (DFILE, "[%%a%d+r]", dec_insn.regs[i]);
	  break;

	case '?':
	  if (dec_insn.regs[i] == 10)
	    DPRINT (DFILE, "[%%sp+i]");
	  else
	    DPRINT (DFILE, "[%%a%d+i]", dec_insn.regs[i]);
	  break;

	case 'S':
	  DPRINT (DFILE, "[%%a15]");
	  need_comma = 0;
	  break;
	}

      if (need_comma)
        DPRINT (DFILE, ",");
    }

#undef DPRINT
#undef DFILE
}

/* Decode the (LEN32 ? 32 : 16)-bit instruction located at MEMADDR.
   INSN already contains its bytes in the correct order, and INFO
   contains (among others) pointers to functions for printing the
   decoded insn.  Return the number of actually decoded bytes.  */

int
decode_tricore_insn (bfd_vma memaddr, unsigned long insn, int len32, struct disassemble_info *info)
{
  int idx = insn & 0x3f;
  struct insnlist *pinsn;
  unsigned long mask;
  tricore_fmt fmt;

  /* Try to find the instruction matching the given opcode.  */
  for (pinsn = insns[idx]; pinsn != NULL; pinsn = pinsn->next)
    {
      if ((pinsn->code->len32 != len32)
          || (insn & pinsn->code->lose))
        continue;

      fmt = pinsn->code->format;
      mask = tricore_opmask[fmt];
      if ((insn & mask) != pinsn->code->opcode)
        continue;

      /* A valid instruction was found.  Go print it. */
      dec_insn.code = pinsn->code;
      dec_insn.opcode = insn;
      decode[fmt] ();
      print_decoded_insn (memaddr, info);
      return len32 ? 4 : 2;
    }

  /* Oops -- this isn't a valid TriCore insn!  Since we know that
     MEMADDR is an even address (otherwise it already would have
     been handled by print_insn_tricore below) and that TriCore
     insns can only start at even addresses, we just print the
     lower 16 bits of INSN as a .hword pseudo-opcode and return 2,
     no matter what LEN32 says.  */
  (*info->fprintf_func) (info->stream, ".hword 0x%04lx", (insn & 0xffff));

  return 2;
}

/* Decode the PCP instruction located at MEMADDR.  Its first two bytes
   are already stored in BUFFER.  INFO contains (among others) pointers
   to functions for printing the decoded insn.  Return the number of
   actually decoded bytes (2 or 4).  */

int
decode_pcp_insn (bfd_vma memaddr, bfd_byte buffer[4], struct disassemble_info *info)
{
  unsigned long insn = 0, insn2 = 0, val;
  int idx, fail, rb, ra;
  struct pcplist *pinsn;
  pcp_opcode_t *pop = (pcp_opcode_t *) NULL;
  static const char *pcp_ccodes[] =
  {
    "uc", "z", "nz", "v", "c/ult", "ugt", "slt", "sgt",    /* CONDCA  */
    "n", "nn", "nv", "nc/uge", "sge", "sle", "cnz", "cnn"  /* CONDCB  */
  };
#define DPRINT (*info->fprintf_func)
#define DFILE info->stream

  /* Try to find the PCP instruction matching the given opcode.  */
  insn = bfd_getl16 (buffer);
  idx = (insn >> 11) & 0x1f;
  for (pinsn = pcpinsns[idx]; pinsn != NULL; pinsn = pinsn->next)
    {
      if (((insn & pinsn->code->opcode) != pinsn->code->opcode)
          || (insn & pinsn->code->lose))
        continue;

      /* A valid instruction was found.  */
      pop = pinsn->code;
      if (pop->len32)
        {
	  /* This is a 32-bit insn; try to read 2 more bytes.  */
          fail = (*info->read_memory_func) (memaddr + 2, &buffer[2], 2, info);
          if (fail)
            {
              DPRINT (DFILE, ".hword 0x%04lx", insn);
	      return 2;
	    }
	  insn2 = bfd_getl16 (buffer + 2);
	}

      break;
    }

  if (pop == NULL)
    {
      /* No valid instruction was found; print it as a 16-bit word.  */
      DPRINT (DFILE, ".hword 0x%04lx", (insn & 0xffff));

      return 2;
    }

  /* Print the instruction.  */
  DPRINT (DFILE, "%s  ", pop->name);
  switch (pop->fmt_group)
    {
    case 0:
      for (idx = 0; idx < pop->nr_operands; ++idx)
        {
	  switch (pop->args[idx])
	    {
	    case 'd':
	      val = (insn >> 9) & 0x3;
	      if (val == 0)
	        DPRINT (DFILE, "dst");
	      else if (val == 1)
	        DPRINT (DFILE, "dst+");
	      else if (val == 2)
	        DPRINT (DFILE, "dst-");
	      else
	        DPRINT (DFILE, "dst *ILLEGAL*");
	      break;

	    case 's':
	      val = (insn >> 7) & 0x3;
	      if (val == 0)
	        DPRINT (DFILE, "src");
	      else if (val == 1)
	        DPRINT (DFILE, "src+");
	      else if (val == 2)
	        DPRINT (DFILE, "src-");
	      else
	        DPRINT (DFILE, "src *ILLEGAL*");
	      break;

	    case 'c':
	      val = (insn >> 5) & 0x3;
	      DPRINT (DFILE, "cnc=%ld", val);
	      break;

	    case 'n':
	      if (!strcmp (pop->name, "copy"))
		val = ((insn >> 2) & 0x7) + 1;
	      else
	        {
		  val = (insn >> 2) & 0x3;
		  if (val == 0)
		    val = 8;
		  else if (val == 3)
		    val = 4;
		}
	      DPRINT (DFILE, "cnt0=%ld", val);
	      break;

	    case 'f':
	      val = 8 << (insn & 0x3);
	      DPRINT (DFILE, "size=%ld", val);
	      break;

	    case 'a':
	    case 'b':
	      val = insn & 0xf;
	      DPRINT (DFILE, "cc_%s", pcp_ccodes[val]);
	      break;

	    case 'g':
	      val = (insn >> 10) & 0x1;
	      DPRINT (DFILE, "st=%ld", val);
	      break;

	    case 'i':
	      val = (insn >> 9) & 0x1;
	      DPRINT (DFILE, "int=%ld", val);
	      break;

	    case 'j':
	      val = (insn >> 8) & 0x1;
	      DPRINT (DFILE, "ep=%ld", val);
	      break;

	    case 'h':
	      val = (insn >> 7) & 0x1;
	      DPRINT (DFILE, "ec=%ld", val);
	      break;

	    default:
	      DPRINT (DFILE, "***UNKNOWN OPERAND `%c'***", pop->args[idx]);
	      break;
	    }
          if (idx < (pop->nr_operands - 1))
	    DPRINT (DFILE, ", ");
        }
      break;

    case 1:
      rb = (insn >> 6) & 0x7;
      ra = (insn >> 3) & 0x7;
      val = 8 << (insn & 0x3);
      DPRINT (DFILE, "r%d, [r%d], size=%ld", rb, ra, val);
      break;

    case 2:
      ra = (insn >> 6) & 0x7;
      val = insn & 0x3f;
      DPRINT (DFILE, "r%d, [%ld]", ra, val);
      break;

    case 3:
      rb = (insn >> 6) & 0x7;
      ra = (insn >> 3) & 0x7;
      val = insn & 0x7;
      if (!strcmp (pop->name, "ld.p") || !strcmp (pop->name, "st.p"))
        DPRINT (DFILE, "cc_%s, r%d, [r%d]", pcp_ccodes[val], rb, ra);
      else
        DPRINT (DFILE, "cc_%s, r%d, r%d", pcp_ccodes[val], rb, ra);
      break;

    case 4:
      ra = (insn >> 6) & 0x7;
      val = insn & 0x3f;
      if (!strcmp (pop->name, "chkb"))
        DPRINT (DFILE, "r%d, %ld, %s", ra, val & 0x1f,
		(val & 0x20) ? "set" : "clr");
      else if (!strcmp (pop->name, "ldl.dptr"))
        {
          if (ra == 7)
            {
              DPRINT(DFILE, "r%d, 0x%04lx, %ld",ra, insn2 & 0xf00, (insn2 >> 5) & 3);
            }
          else
            DPRINT (DFILE, "r%d, 0x....%04lx", ra, insn2);
        }
      else if (!strcmp (pop->name, "ldl.il"))
        DPRINT (DFILE, "r%d, 0x....%04lx", ra, insn2);
      else if (!strcmp (pop->name, "ldl.iu"))
        DPRINT (DFILE, "r%d, 0x%04lx....", ra, insn2);
      else
        DPRINT (DFILE, "r%d, %ld", ra, val);
      break;

    case 5:
      ra = (insn >> 6) & 0x7;
      val = 8 << (((insn >> 5) & 0x1) | ((insn >> 8) & 0x2));
      if ((!strcmp (pop->name, "set.f") || !strcmp (pop->name, "clr.f"))
          && ((insn & 0x1f) >= val))
        DPRINT (DFILE, "[r%d], %ld ***ILLEGAL VALUE***, size=%ld", ra,
		insn & 0x1f, val);
      else
        DPRINT (DFILE, "[r%d], %ld, size=%ld", ra, insn & 0x1f, val);
      break;

    case 6:
      rb = (insn >> 6) & 0x7;
      ra = (insn >> 3) & 0x7;
      if ((rb == 0) || (ra == 0) || (rb == 7) || (ra == 7) || (rb == ra))
        DPRINT (DFILE, "r%d, r%d ***ILLEGAL REGISTER USE***", rb, ra);
      else
        DPRINT (DFILE, "r%d, r%d", rb, ra);
      break;

    case 7:
      for (idx = 0; idx < pop->nr_operands; ++idx)
        {
	  switch (pop->args[idx])
	    {
	    case 'r':
	    case 'R':
	      DPRINT (DFILE, "[r%ld]", (insn >> 3) & 0x7);
	      break;

	    case 'm':
	      DPRINT (DFILE, "dac=%ld", (insn >> 3) & 0x1);
	      break;

	    case 'a':
	    case 'b':
	      DPRINT (DFILE, "cc_%s", pcp_ccodes[(insn >> 6) & 0xf]);
	      break;

	    case 'o':
	      DPRINT (DFILE, "rta=%ld", (insn >> 2) & 0x1);
	      break;

	    case 'p':
	      DPRINT (DFILE, "eda=%ld", (insn >> 1) & 0x1);
	      break;

	    case 'q':
	      DPRINT (DFILE, "sdb=%ld", insn & 1);
	      break;

	    case 'e':
	      if (!strcmp (pop->name, "jl"))
	        {
		  val = insn & 0x3ff;
		  if (val & 0x200)
		    val |= ~0x3ff;
	          (*info->print_address_func) (memaddr + 2 + (val << 1), info);
		}
	      else if (!strcmp (pop->name, "jc"))
	        {
		  val = insn & 0x3f;
		  if (val & 0x20)
		    val |= ~0x3f;
	          (*info->print_address_func) (memaddr + 2 + (val << 1), info);
		}
	      else if (!strcmp (pop->name, "jc.a"))
	        /* FIXME: address should be PCODE_BASE + (insn2 << 1).  */
	        (*info->print_address_func)
		 ((memaddr & 0xffff0000) + (insn2 << 1), info);
	      else
	        DPRINT (DFILE, "***ILLEGAL expr FOR %s***", pop->name);
	      break;

	    default:
	      DPRINT (DFILE, "***UNKNOWN OPERAND `%c'***", pop->args[idx]);
	      break;
	    }
          if (idx < (pop->nr_operands - 1))
	    DPRINT (DFILE, ", ");
	}
      break;

    default:
      DPRINT (DFILE, "***ILLEGAL FORMAT GROUP %d***", pop->fmt_group);
      break;
    }

  return pop->len32 ? 4 : 2;
#undef DPRINT
#undef DFILE
}

unsigned long tricore_elf32_convert_eflags(unsigned long eflags);

/* convert old eflags to EABI conforming eflags */
unsigned long
tricore_elf32_convert_eflags(unsigned long eflags)
{
  unsigned long new_flags = 0;
  int i;

  if (eflags & 0xffff0000)
    new_flags = eflags;
  else
    for (i = 0; i < 16; i++)
      {
        if (eflags & (1 << i))
          new_flags |= 1 << (31-i);
      }
  return new_flags;
}

void tricore_init_arch_vars (unsigned long mach);

void
tricore_init_arch_vars (unsigned long mach)
{
  switch (mach & EF_EABI_TRICORE_CORE_MASK)
    {
    case EF_EABI_TRICORE_V1_1:
      tricore_mask_abs =  0x0c0000ff;
      tricore_mask_absb = 0x0c0000ff;
      tricore_mask_b =    0x000000ff;
      tricore_mask_bit =  0x006000ff;
      tricore_mask_bo =   0x0fc000ff;
      tricore_mask_bol =  0x000000ff;
      tricore_mask_brc =  0x800000ff;
      tricore_mask_brn =  0x8000007f;
      tricore_mask_brr =  0x800000ff;
      tricore_mask_rc =   0x0fe000ff;
      tricore_mask_rcpw = 0x006000ff;
      tricore_mask_rcr =  0x00e000ff;
      tricore_mask_rcrr = 0x00e000ff;
      tricore_mask_rcrw = 0x00e000ff;
      tricore_mask_rlc =  0x000000ff;
      tricore_mask_rr =   0x0ff000ff;
      tricore_mask_rrpw = 0x006000ff;
      tricore_mask_rrr =  0x00f000ff;
      tricore_mask_rrr1 = 0x00fc00ff;
      tricore_mask_rrr2 = 0x00ff00ff;
      tricore_mask_rrrr = 0x00e000ff;
      tricore_mask_rrrw = 0x00e000ff;
      tricore_mask_sys =  0x07c000ff;
      tricore_mask_sb =       0x00ff;
      tricore_mask_sbc =      0x00ff;
      tricore_mask_sbr =      0x00ff;
      tricore_mask_sbrn =     0x007f;
      tricore_mask_sc =       0x00ff;
      tricore_mask_slr =      0x00ff;
      tricore_mask_slro =     0x00ff;
      tricore_mask_sr =       0xf0ff;
      tricore_mask_src =      0x00ff;
      tricore_mask_sro =      0x00ff;
      tricore_mask_srr =      0x00ff;
      tricore_mask_srrs =     0x003f;
      tricore_mask_ssr =      0x00ff;
      tricore_mask_ssro =     0x00ff;
      break;

    case EF_EABI_TRICORE_V1_2:
    case EF_EABI_TRICORE_V1_3:
    case EF_EABI_TRICORE_V1_3_1:
    case EF_EABI_TRICORE_V1_6:
    case EF_EABI_TRICORE_V1_6_1:
    case EF_EABI_TRICORE_V1_6_2:
      tricore_mask_abs =  0x0c0000ff;
      tricore_mask_absb = 0x0c0000ff;
      tricore_mask_b =    0x000000ff;
      tricore_mask_bit =  0x006000ff;
      tricore_mask_bo =   0x0fc000ff;
      tricore_mask_bol =  0x000000ff;
      tricore_mask_brc =  0x800000ff;
      tricore_mask_brn =  0x8000007f;
      tricore_mask_brr =  0x800000ff;
      tricore_mask_rc =   0x0fe000ff;
      tricore_mask_rcpw = 0x006000ff;
      tricore_mask_rcr =  0x00e000ff;
      tricore_mask_rcrr = 0x00e000ff;
      tricore_mask_rcrw = 0x00e000ff;
      tricore_mask_rlc =  0x000000ff;
      tricore_mask_rr =   0x0ff300ff;
      tricore_mask_rr1 =  0x0ffc00ff;
      tricore_mask_rr2 =  0x0fff00ff;
      tricore_mask_rrpw = 0x006000ff;
      tricore_mask_rrr =  0x00f300ff;
      tricore_mask_rrr1 = 0x00fc00ff;
      tricore_mask_rrr2 = 0x00ff00ff;
      tricore_mask_rrrr = 0x00e000ff;
      tricore_mask_rrrw = 0x00e000ff;
      tricore_mask_sys =  0x0fc000ff;
      tricore_mask_sb =       0x00ff;
      tricore_mask_sbc =      0x00ff;
      tricore_mask_sbr =      0x00ff;
      tricore_mask_sbrn =     0x00ff;
      tricore_mask_sc =       0x00ff;
      tricore_mask_slr =      0x00ff;
      tricore_mask_slro =     0x00ff;
      tricore_mask_sr =       0xf0ff;
      tricore_mask_src =      0x00ff;
      tricore_mask_sro =      0x00ff;
      tricore_mask_srr =      0x00ff;
      tricore_mask_srrs =     0x003f;
      tricore_mask_ssr =      0x00ff;
      tricore_mask_ssro =     0x00ff;
      break;
    }

  /* Now fill in tricore_opmask[].  */

  tricore_opmask[TRICORE_FMT_ABS] = tricore_mask_abs;
  tricore_opmask[TRICORE_FMT_ABSB] = tricore_mask_absb;
  tricore_opmask[TRICORE_FMT_B] = tricore_mask_b;
  tricore_opmask[TRICORE_FMT_BIT] = tricore_mask_bit;
  tricore_opmask[TRICORE_FMT_BO] = tricore_mask_bo;
  tricore_opmask[TRICORE_FMT_BOL] = tricore_mask_bol;
  tricore_opmask[TRICORE_FMT_BRC] = tricore_mask_brc;
  tricore_opmask[TRICORE_FMT_BRN] = tricore_mask_brn;
  tricore_opmask[TRICORE_FMT_BRR] = tricore_mask_brr;
  tricore_opmask[TRICORE_FMT_RC] = tricore_mask_rc;
  tricore_opmask[TRICORE_FMT_RCPW] = tricore_mask_rcpw;
  tricore_opmask[TRICORE_FMT_RCR] = tricore_mask_rcr;
  tricore_opmask[TRICORE_FMT_RCRR] = tricore_mask_rcrr;
  tricore_opmask[TRICORE_FMT_RCRW] = tricore_mask_rcrw;
  tricore_opmask[TRICORE_FMT_RLC] = tricore_mask_rlc;
  tricore_opmask[TRICORE_FMT_RR] = tricore_mask_rr;
  tricore_opmask[TRICORE_FMT_RR1] = tricore_mask_rr1;
  tricore_opmask[TRICORE_FMT_RR2] = tricore_mask_rr2;
  tricore_opmask[TRICORE_FMT_RRPW] = tricore_mask_rrpw;
  tricore_opmask[TRICORE_FMT_RRR] = tricore_mask_rrr;
  tricore_opmask[TRICORE_FMT_RRR1] = tricore_mask_rrr1;
  tricore_opmask[TRICORE_FMT_RRR2] = tricore_mask_rrr2;
  tricore_opmask[TRICORE_FMT_RRRR] = tricore_mask_rrrr;
  tricore_opmask[TRICORE_FMT_RRRW] = tricore_mask_rrrw;
  tricore_opmask[TRICORE_FMT_SYS] = tricore_mask_sys;
  tricore_opmask[TRICORE_FMT_SB] = tricore_mask_sb;
  tricore_opmask[TRICORE_FMT_SBC] = tricore_mask_sbc;
  tricore_opmask[TRICORE_FMT_SBR] = tricore_mask_sbr;
  tricore_opmask[TRICORE_FMT_SBRN] = tricore_mask_sbrn;
  tricore_opmask[TRICORE_FMT_SC] = tricore_mask_sc;
  tricore_opmask[TRICORE_FMT_SLR] = tricore_mask_slr;
  tricore_opmask[TRICORE_FMT_SLRO] = tricore_mask_slro;
  tricore_opmask[TRICORE_FMT_SR] = tricore_mask_sr;
  tricore_opmask[TRICORE_FMT_SRC] = tricore_mask_src;
  tricore_opmask[TRICORE_FMT_SRO] = tricore_mask_sro;
  tricore_opmask[TRICORE_FMT_SRR] = tricore_mask_srr;
  tricore_opmask[TRICORE_FMT_SRRS] = tricore_mask_srrs;
  tricore_opmask[TRICORE_FMT_SSR] = tricore_mask_ssr;
  tricore_opmask[TRICORE_FMT_SSRO] = tricore_mask_ssro;
}

/* Read, decode and print the byte(s) starting at MEMADDR.  Return -1
   if a read error occurs, or else the number of decoded bytes.  We
   do expect to find a valid TriCore instruction at MEMADDR, but we'll
   happily just print the byte(s) as ".byte"/".hword" pseudo-ops if
   this is not the case.  We only read as many bytes as necessary
   (or possible) to decode a single instruction or a pseudo-op, i.e.
   1, 2 or 4 bytes.  */

int
print_insn_tricore (bfd_vma memaddr, struct disassemble_info *info)
{
  bfd_byte buffer[4];
  int len32 = 0, failure;
  unsigned long insn = 0;
  unsigned long flags = 0;

  if (!initialized)
    {
	  flags = tricore_elf32_convert_eflags(info->flags);
      /* Set the current instruction set architecture.  */
      switch (flags & EF_EABI_TRICORE_CORE_MASK)
        {
          case EF_EABI_TRICORE_V1_1:
            current_isa = TRICORE_RIDER_A;
            (*info->fprintf_func) (info->stream, "Disassembler Tricore Rider-A\n");
            break;
          case EF_EABI_TRICORE_V1_2:
            current_isa = TRICORE_V1_2;
            (*info->fprintf_func) (info->stream, "Disassembler TC1.2 instruction set\n");
            break;
          case EF_EABI_TRICORE_V1_3:
            current_isa = TRICORE_V1_3;
            (*info->fprintf_func) (info->stream, "Disassembler TC1.3 instruction set\n");
            break;
          case EF_EABI_TRICORE_V1_3_1:
            current_isa = TRICORE_V1_3_1;
            (*info->fprintf_func) (info->stream, "Disassembler TC1.3.1 instruction set\n");
            break;
          case EF_EABI_TRICORE_V1_6:
            current_isa = TRICORE_V1_6;
            (*info->fprintf_func) (info->stream, "Disassembler TC1.6 instruction set\n");
            break;
          case EF_EABI_TRICORE_V1_6_1:
            current_isa = TRICORE_V1_6_1;
            (*info->fprintf_func) (info->stream, "Disassembler TC1.6.1 instruction set\n");
            break;
          case EF_EABI_TRICORE_V1_6_2:
            current_isa = TRICORE_V1_6_2;
            (*info->fprintf_func) (info->stream, "Disassembler TC1.6.2 instruction set\n");
            break;
          default:
            (*info->fprintf_func) (info->stream, "unknown tricore architecture using TC1.6.2 instruction set");
            current_isa = TRICORE_V1_6_2;
            break;
          }

      /* Initialize architecture-dependent variables.  */
      tricore_init_arch_vars (flags);

      /* Initialize the hash tables.  */
      init_hash_tables ();
      initialized = 1;
    }

  memset ((char *) buffer, 0, sizeof (buffer));
  failure = (*info->read_memory_func) (memaddr, buffer, 1, info);
  if (failure)
    {
      (*info->memory_error_func) (failure, memaddr, info);
      return -1;
    }

  /* Try to read the 2nd byte.  */
  failure = (*info->read_memory_func) (memaddr + 1, &buffer[1], 1, info);
  if (failure)
    {
      /* Maybe MEMADDR isn't even and we reached the end of a section.  */
      (*info->fprintf_func) (info->stream, ".byte 0x%02x", buffer[0]);
      return 1;
    }

  /* Handle TriCore sections.  */
  if (buffer[0] & 1)
    {
      /* Looks like this is a 32-bit insn; try to read 2 more bytes.  */
      failure = (*info->read_memory_func) (memaddr + 2, &buffer[2], 2, info);
      if (failure)
        {
          insn = bfd_getl16 (buffer);
          (*info->fprintf_func) (info->stream, ".hword 0x%04lx", insn);
	  return 2;
	}
      else
        len32 = 1;
    }

  if (len32)
  {
    insn = bfd_getl32 (buffer);
  (*info->fprintf_func) (info->stream, "%10.8lx    ",insn);
  }
  else
  {
    insn = bfd_getl16 (buffer);
  (*info->fprintf_func) (info->stream, "    %6.4lx    ",insn);
  }
  return decode_tricore_insn (memaddr, insn, len32, info);
}

/* End of tricore-dis.c.  */
