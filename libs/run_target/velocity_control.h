#ifndef QRK_VELOCITY_CONTROL_H
#define QRK_VELOCITY_CONTROL_H

/*!
  \file
  \brief 筐体の速度制御

  \author Satofumi KAMIMURA

  $Id: velocity_control.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "velocity_t.h"


//! 初期化
extern void velocity_initialize(velocity_t *velocity);


// 等加速度で一定速度まで加速するための速度の計算
extern long velocity_standard_velocity(velocity_t *velocity);


//! 指定距離だけ移動して停止するための速度の計算
extern long velocity_stop_to_position(velocity_t *velocity, long length);

#endif /* !QRK_VELOCITY_CONTROL_H */


/*!
  \page velocity_control_h_page 筐体の速度制御 (記述中)

  !!!
*/
