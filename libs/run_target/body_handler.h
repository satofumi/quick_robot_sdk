#ifndef QRK_BODY_HANDLER_H
#define QRK_BODY_HANDLER_H

/*!
  \file
  \brief 並進速・回転速の制御

  \author Satofumi KAMIMURA

  $Id: body_handler.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "wheel_t.h"


extern void body_set_velocity(wheel_t* wheels,
                              int translational_velocity,
                              int rotational_velocity);

#endif /* !QRK_BODY_HANDLER_H */


/*!
  \page body_handler_h_page 並進速・回転速の制御 (記述中)

  \todo テストで正当性を保証すること

  与えられた並進速・回転速を駆動輪の速度に変換する。

  右輪の速度[m/s] + 左輪の速度[m/s] = 並進速度[m/s] / 2 \n
  右輪の速度[m/s] - 左輪の速度[m/s] = (回転速度[rad/s] * トレッド[m])/ 2 \n

  なので、

  右輪の速度[m/s] = (並進速度[m/s] + (回転速度[rad/s] * トレッド[m]) / 4 \n
  左輪の速度[m/s] = (並進速度[m/s] - (回転速度[rad/s] * トレッド[m]) / 4 \n

  となる。
*/
