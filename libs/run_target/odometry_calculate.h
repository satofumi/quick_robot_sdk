#ifndef QRK_ODOMETRY_CALCULATE_H
#define QRK_ODOMETRY_CALCULATE_H

/*!
  \file
  \brief 推定自己位置の計算

  \author Satofumi KAMIMURA

  $Id: odometry_calculate.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "odometry_t.h"


//! 初期化
extern void odometry_initialize(odometry_t *odometry);


//! 推定位置を更新
extern void odometry_update(odometry_t *odometry,
                            int left_encoder_difference,
                            int right_encoder_difference);

#endif /* !QRK_ODOMETRY_CALCULATE_H */


/*!
  \page odometry_calculate_h_page 推定自己位置の計算 (記述中)

  !!!
*/
