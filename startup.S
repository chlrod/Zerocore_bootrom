# start sequence of the bootloader
#
#

#define DRAM_BASE 0x80000000
#include "smp.h"

  .section .text.init
  .option norvc
  .globl _prog_start
_prog_start:
  nop
  nop
  nop
  li sp,0xc0010000
  smp_pause(s0,s1)
  call main
  smp_resume(s0,s1)
  csrr a0, mhartid
  li s1, DRAM_BASE
  jr s1

