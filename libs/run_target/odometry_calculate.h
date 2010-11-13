#ifndef QRK_ODOMETRY_CALCULATE_H
#define QRK_ODOMETRY_CALCULATE_H

/*!
  \file
  \brief 推定自己位置の計算

  \author Satofumi KAMIMURA

  $Id: odometry_calculate.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "odometry_t.h"


enum {
    ODOMETFY_DIRECTION_BIT_WIDTH = 16,
};


//! 初期化
extern void odometry_initialize(odometry_t *odometry);


//! 推定位置を更新
extern void odometry_update(odometry_t *odometry,
                            int right_encoder_difference,
                            int left_encoder_difference);

#endif /* !QRK_ODOMETRY_CALCULATE_H */


/*!
  \page odometry_calculate_h_page 推定自己位置の計算 (記述中)

  \section odometry_calculate_h_abstarct 概要

  推定自己位置の計算は、各輪のエンコーダ変位から計算する。\n
  エンコーダ変位は車輪の移動距離を示す。両輪の同じ向きの移動を並進、向きの異なる移動を回転、と呼ぶ。

  \image html odometry_calculate_h_straight_rotate_image.jpg "並進と回転"

  オドメトリ計算は、

  -# 各輪の移動距離を計算する。
  -# 回転の変位を計算し、その積分値をロボットの向きとみなす。
  -# ロボットの向きに並進の変位だけ移動した位置をロボットの位置とみなす。

  という手順で計算する。


  \section odometry_calculate_h_each_wheel 各輪の移動距離

  各輪の移動距離を計算するには、エンコーダ１カウントあたりの移動距離が計算できればよい。\n
  エンコーダ１カウントあたりの距離は、固定小数点で表現し、切捨てによる誤差が小さくなるようにする。

  距離 [mm/count] = 車輪の円周 [mm] / (車輪１周のカウント数)


  \section odometry_calculate_h_rotate 回転の処理

  向きは [0, 65535] の値で表現する。0 のときに X 軸の方向を向いているとする。

  \image html odometry_calculate_h_direction_image.jpg "向きの表現"

  ロボットの向きが１周するときの左右輪の差の距離を計算しておき、回転の距離差がその値になったときに、向きが１周したとみなせるようにする。

  \section odometry_calculate_h_straight 並進の処理

  !!!
*/
