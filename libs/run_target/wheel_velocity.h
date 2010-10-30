#ifndef QRK_WHEEL_VELOCITY_H
#define QRK_WHEEL_VELOCITY_H

/*!
  \file
  \brief 車輪速の制御

  \author Satofumi KAMIMURA

  $Id: wheel_velocity.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "wheel_t.h"


//! 初期化
extern void wheel_initialize(wheel_t *wheel, int device_id);


//! 回転速度を指定
extern void wheel_set_velocity(wheel_t *wheel, int mm_per_sec);


extern void wheel_velocity_control(wheel_t *wheel);


//! サーボフリーに設定
extern void wheel_set_servo_free(const wheel_t *wheel);

#endif /* !QRK_WHEEL_VELOCITY_H */


/*!
  \page wheel_velocity_h_page 車輪速の制御 (記述中)

  !!!
*/
