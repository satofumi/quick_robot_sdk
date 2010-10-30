/*!
  \file
  \brief 車輪速の制御

  \author Satofumi KAMIMURA

  $Id: wheel_velocity.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "wheel_velocity.h"
#include "robot_parameter.h"
#include "encoder_reader.h"
#include "motor_velocity.h"
#include "motor_pwm.h"
#include <math.h>


void wheel_initialize(wheel_t *wheel, int device_id)
{
    encoder_initialize(&wheel->encoder, device_id);
    motor_velocity_initialize(&wheel->motor, device_id);

    wheel->target_velocity = 0;
    wheel->next_add_velocity = 0;
}


void wheel_set_velocity(wheel_t *wheel, int mm_per_sec)
{
    wheel->target_velocity = mm_per_sec;
}


static int mm2count_velocity(int mm)
{
    int count_per_msec =
        (((mm * ENCODER_RESOLUTION) >> (10 - CONTROL_CYCLE_MSEC_SHIFT))
         / (int)(2 * M_PI * WHEEL_RADIUS_MM));

    return count_per_msec;
}


static int count2mm_velocity(int count)
{
    int mm_per_sec =
        count * (int)(2 * M_PI *
                      (WHEEL_RADIUS_MM << (10 - CONTROL_CYCLE_MSEC_SHIFT)))
        / ENCODER_RESOLUTION;

    return mm_per_sec;
}


void wheel_velocity_control(wheel_t *wheel)
{
    int adjusted_mm_velocity =
        wheel->target_velocity + wheel->next_add_velocity;
    int count_velocity = mm2count_velocity(adjusted_mm_velocity);

    // 整数の切捨て誤差を、次回の制御で加算されるようにする
    wheel->next_add_velocity =
        adjusted_mm_velocity - count2mm_velocity(count_velocity);

    motor_velocity_control(&wheel->motor, count_velocity,
                           encoder_difference(&wheel->encoder));
}


void wheel_set_servo_free(const wheel_t *wheel)
{
    motor_pwm_set_servo_free(wheel->motor.device_id);
}
