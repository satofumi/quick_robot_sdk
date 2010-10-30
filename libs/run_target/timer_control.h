#ifndef QRK_TIMER_CONTROL_H
#define QRK_TIMER_CONTROL_H

/*!
  \file
  \brief タイマー・モジュール

  \author Satofumi KAMIMURA

  $Id: timer_control.h 1927 2010-09-26 23:09:26Z satofumi $
*/


//! 初期化
extern void timer_initialize(unsigned char priority);


//! 定期的に実行する関数の登録
extern void timer_set_interval_function(void (*function)(void));


//! 動作の開始
extern void timer_start(void);


//! 動作の停止
extern void timer_stop(void);


/*!
  \brief カウント値を返す

  最初に timer_start() を呼び出してからの msec 単位のカウント値を返す。 ただし timer_stop() を呼び出してから timer_start() を呼び出すまでの時間はカウントされない。
*/
extern long timer_msec_counter(void);


//! 割り込みベクタ用の関数
extern void timer_interrupt(void);

#endif /* !QRK_TIMER_CONTROL_H */


/*!
  \page timer_control_h_page タイマー

  1 [msec] 毎に割り込みを発生させ、登録されている関数を実行する。

  - 割り込みの優先度は interrupt_priority.h にて #INTERRUPT_PRIORITY_TIMER で定義される
*/
