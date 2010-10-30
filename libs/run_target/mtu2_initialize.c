/*!
  \file
  \brief MTU2 モジュールのスタンバイ解除

  \author Satofumi KAMIMURA

  $Id: mtu2_initialize.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "mtu2_initialize.h"
#include <stdbool.h>
#include <7125S.H>


void mtu2_initialize(void)
{
    static bool initialized = false;
    if (initialized) {
        return;
    }

    // スタンバイ解除
    STB.CR4.BYTE &= ~0x40;

    initialized = true;
}
