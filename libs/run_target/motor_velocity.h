#ifndef QRK_MOTOR_VELOCITY_H
#define QRK_MOTOR_VELOCITY_H

/*!
  \file
  \brief モータ回転の速度制御

  \author Satofumi KAMIMURA

  $Id: motor_velocity.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "motor_t.h"


//! 初期化
extern void motor_velocity_initialize(motor_t *motor, int device_id);


//! モータ制御
extern void motor_velocity_control(motor_t *motor,
                                   int target_count_velocity,
                                   int actual_count_velocity);

#endif /* !QRK_MOTOR_VELOCITY_H */


/*!
  \page motor_velocity_h_page モータ回転の制御

  指定された速度でモータが回転するようにする。\n
  このモジュールでは、エンコーダ単位系での速度を受け取り、その速度になるように制御を行う。


  \section motor_velocity_h_pi PI 制御による速度制御

  モータ速度の制御は PI 制御にて行う。\n
  逆起電力の補償の処理は、必要ならば実装してもよい。

  \code
  // PI 制御について
  // target_count: 時間あたりの目標カウント速度
  // actual_count: 時間あたりの実機のカウント速度

  diff = target_count - actual_count;
  output = (GAIN_P * diff) + GAIN_I * (total_diff);
  total_diff += diff; \endcode
*/
