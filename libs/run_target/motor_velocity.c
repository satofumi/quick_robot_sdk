/*!
  \file
  \brief モータ回転の速度制御

  \author Satofumi KAMIMURA

  $Id: motor_velocity.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "motor_velocity.h"
#include "robot_parameter.h"
#include "motor_pwm.h"
#include "encoder_reader.h"

enum {
    DEFAULT_GAIN_P = 32,        /* 1/1 の重さ */
    DEFAULT_GAIN_I = 32,        /* 1/256 の重さ */
};


void motor_velocity_initialize(motor_t *motor, int device_id)
{
    motor_pwm_initialize(device_id);

    motor->device_id = device_id;
    motor->total_diff = 0;
    motor->gain_p = DEFAULT_GAIN_P;
    motor->gain_i = DEFAULT_GAIN_I;
}


void motor_velocity_control(motor_t *motor,
                            int target_count_velocity,
                            int actual_count_velocity)
{
    enum {
        ENCODER_MAX = 100,   // １回のエンコーダ変位の想定される最大値
        TOTAL_DIFF_MAX = 32767 - ENCODER_MAX, // I 項の積分の最大値
    };
    long diff;
    long total_diff = motor->total_diff;
    long output;
    motor_pwm_direction_t direction;

    // PI 制御
    diff = target_count_velocity - actual_count_velocity;
    output = (motor->gain_p * diff) + (motor->gain_i * (total_diff >> 8));
    total_diff += diff;

    if (total_diff > TOTAL_DIFF_MAX) {
        total_diff = TOTAL_DIFF_MAX;
    } else if (total_diff < -TOTAL_DIFF_MAX) {
        total_diff = -TOTAL_DIFF_MAX;
    }
    motor->total_diff = total_diff;

    if (output >= 0) {
        direction = MOTOR_PWM_CW;
    } else {
        output = -output;
        direction = MOTOR_PWM_CCW;
    }

    if (output > 256) {
        output = 255;
    } else if (output < 0) {
        output = 0;
    }

#if 0
    // !!! リミットを付加
    if (output > 153) {
        output = 153;
    }
#endif

    motor_pwm_set_duty(motor->device_id, direction, output);
}
