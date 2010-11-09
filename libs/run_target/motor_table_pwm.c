/*!
  \file
  \brief 補正テーブルを用いたモータの PWM 制御

  \author Satofumi KAMIMURA

  $Id: motor_pwm.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "motor_table_pwm.h"


void motor_table_pwm_initialize(int device_id)
{
    // テーブルの初期化
    // !!!

    motor_pwm_initialize(device_id);
}

void motor_table_pwm_set_duty(int device_id,
                              motor_pwm_direction_t direction,
                              unsigned char duty)
{
    (void)device_id;
    (void)direction;
    (void)duty;

    motor_pwm_set_duty(device_id, direction, duty);

    // !!!

    // !!! テーブルの値を介した値を PWM の duty 比として使うようにする
}
