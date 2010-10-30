#ifndef QRK_CLOCK_INITIALIZE_H
#define QRK_CLOCK_INITIALIZE_H

/*!
  \file
  \brief クロックの初期化

  \author Satofumi KAMIMURA

  $Id: clock_initialize.h 1927 2010-09-26 23:09:26Z satofumi $
*/


//! 初期化
extern void clock_initialize(void);

#endif /* !QRK_CLOCK_INITIALIZE_H */


/*!
  \page clock_initialize_h_page クロックの初期化

  クロック設定を初期化する。\n
  実際のクロック数値については cpu_clock.h にて適切なマクロを定義して利用すること。
*/
