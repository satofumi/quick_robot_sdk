/*!
  \file
  \brief 割り込みマスクの制御

  \author Satofumi KAMIMURA

  $Id: imask.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "imask.h"


void imask_initialize(void)
{
    // 全割り込みをマスクする
    set_imask_exr(15);
}


void set_imask_exr(unsigned char level)
{
#if defined(HOST_COMPILE)
    (void)level;
#else
  unsigned short sr_register;

  level <<= 4;
  level &= 0x000000f0;

  asm("stc sr, %0":"=r"(sr_register):);

  sr_register &= ~0x000000f0;
  sr_register = sr_register | level;

  asm("ldc %0, sr"::"r"(sr_register));
#endif
}


unsigned char get_imask_exr(void)
{
#if defined(HOST_COMPILE)
    return 0;
#else
  unsigned long mask;

  asm("stc sr, %0": "=r"(mask):);
  mask &= 0x000000f0;
  mask >>= 4;

  return mask;
#endif
}
