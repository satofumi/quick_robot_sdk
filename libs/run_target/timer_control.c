/*!
  \file
  \brief タイマー・モジュール

  \author Satofumi KAMIMURA

  $Id: timer_control.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "timer_control.h"
#include "cpu_clock.h"
#include <7125S.H>
#include <stddef.h>


typedef void (*function_t)(void);


static function_t interval_function_ = NULL;
static long msec_counter_ = 0;


static void set_interval_usec(long usec)
{
    CMT0.CMCOR = (usec * P_MHz) >> (10 + 3);
}


void timer_initialize(unsigned char priority)
{
    // スタンバイ解除
    STB.CR4.BYTE &= ~0x20;

    // タイマーの停止
    CMT.CMSTR.WORD &= ~0x0001;

    // 割り込み優先度の登録
    INTC.IPRJ.WORD &= ~0xf000;
    INTC.IPRJ.WORD |= (unsigned short)(priority) << 12;

    // 割り込み設定、クロック分周の設定
    CMT0.CMCSR.WORD &= ~0x0080;
    CMT0.CMCSR.WORD |= 0x0040;

    set_interval_usec(1000);

    msec_counter_ = 0;
}


void timer_set_interval_function(void (*function)(void))
{
    interval_function_ = function;
}


void timer_start(void)
{
    CMT0.CMCNT = 0;
    CMT.CMSTR.WORD |= 0x0001;
}


//! 動作の停止
void timer_stop(void)
{
    CMT.CMSTR.WORD &= ~0x0001;
}


long timer_msec_counter(void)
{
    return msec_counter_;
}


#pragma interrupt
void cmi0(void)
{
    ++msec_counter_;

    if (interval_function_) {
        interval_function_();
    }

    CMT0.CMCSR.WORD &= ~0x0080;
}
