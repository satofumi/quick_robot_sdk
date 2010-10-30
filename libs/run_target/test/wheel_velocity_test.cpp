/*!
  \example wheel_velocity.c のテスト

  \author Satofumi KAMIMURA

  $Id: wheel_velocity_test.cpp 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "wheel_velocity.c"
#include "robot_parameter.h"
#include <stdio.h>
#include <math.h>


void motor_velocity_initialize(motor_t *motor, int device_id)
{
    (void)motor;
    (void)device_id;
    // !!!
}


void motor_velocity_control(motor_t *motor,
                            int target_count_velocity,
                            int actual_count_velocity)
{
    (void)motor;
    (void)target_count_velocity;
    (void)actual_count_velocity;
    // !!!
}


void motor_pwm_set_servo_free(int device_id)
{
    (void)device_id;
    // !!!
}


void encoder_initialize(encoder_t *encoder, int device_id)
{
    (void)encoder;
    (void)device_id;
    // !!!
}


short encoder_difference(encoder_t *encoder)
{
    (void)encoder;
    // !!!
    return 0;
}


static void calculate_velocity(int mm_velocity)
{
    int count = mm2count_velocity(mm_velocity);
    int mm = mm_velocity - count2mm_velocity(count);

    printf("%d, %d, %d\n", mm_velocity, count, mm);
}


int main(void)
{
    enum {
        MM_VELOCITY_BASE = 150,
    };

    for (int i = 0; i < 10; ++i) {
        calculate_velocity(MM_VELOCITY_BASE * i);
    }

    return 0;
}
