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


extern long odometry_current_mm(const odometry_t *odometry, int axis_index);


extern long odometry_direction_difference(const odometry_t *odometry,
                                          long target_direction);

#endif /* !QRK_ODOMETRY_CALCULATE_H */


/*!
  \page odometry_calculate_h_page 推定自己位置の計算

  \section odometry_calculate_h_abstarct 概要

  推定自己位置の計算は、各輪のエンコーダ変位から計算する。\n
  エンコーダ変位は車輪の移動距離を示す。両輪の同じ向きの移動を並進、向きの異なる移動を回転、と呼ぶ。

  \image html odometry_calculate_h_translational_rotational_image.jpg "並進と回転"

  オドメトリ計算は、

  -# 各輪の移動距離を計算する。
  -# 回転の変位を計算し、その積分値をロボットの向きとみなす。
  -# ロボットの向きに並進の変位だけ移動した位置をロボットの位置とみなす。

  という手順で計算する。


  \section odometry_calculate_h_each_wheel 各輪の移動距離

  各輪の移動距離を計算するには、エンコーダ１カウントあたりの移動距離が計算できればよい。\n
  エンコーダ１カウントあたりの距離は、固定小数点で表現し、切捨てによる誤差が小さくなるようにする。

  距離 [mm/count] = 車輪の円周 [mm] / (車輪１周のカウント数)


  \section odometry_calculate_h_rotational 回転の処理

  向きは [0, 65535] の値で表現する。0 のときに X 軸の方向を向いているとする。

  \image html odometry_calculate_h_direction_image.jpg "向きの表現"

  ロボットの向きが１周するときの左右輪の差の距離を計算しておき、回転の距離差がその値になったときに、向きが１周したとみなせるようにする。


  \section odometry_calculate_h_translational 並進の処理

  並進速度(左右輪の平均速度)だけ、現在の向きに移動したとして計算する。\n

  \verbatim
  X 方向の移動量 = 並進速度 x cos(向き);
  Y 方向の移動量 = 並進速度 x sin(向き); \endverbatim

  ロボットの位置を管理する変数は km, m, mm に分ける。

  - ロボットの車輪径で 1000 [mm] 進むだけのエンコーダのカウント数を計算しておき、そのカウント数を越えたかどうかで X-Y 座標系での m 位置を更新する。
  - mm 位置は、ロボットの車輪径で 1000 [mm] 進むだけのエンコーダのカウント数と現在のその軸方向へのカウント数から、計算する。
  \verbatim
  X 軸の位置 [mm] = 1000 * X 軸のカウント数 / 1 [m] ぶんのカウント数;
  Y 軸の位置 [mm] = 1000 * Y 軸のカウント数 / 1 [m] ぶんのカウント数; \endverbatim

  - km 位置は、m 位置が 1000 以上、または 0 より小さくなったときに更新する。
*/
