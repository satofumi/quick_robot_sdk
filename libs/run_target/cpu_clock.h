#ifndef QRK_CPU_CLOCK_H
#define QRK_CPU_CLOCK_H

/*!
  \file
  \brief クロックの値

  \author Satofumi KAMIMURA

  $Id: cpu_clock.h 1927 2010-09-26 23:09:26Z satofumi $
*/


// !!! 25.0 が CPU クロックの 12.5 から生成されるようにする
enum {
  P_MHz = (long)(25.0 * 1024.0), // 動作周波数 [MHz] << 10
};

#endif /* !QRK_CPU_CLOCK_H */
