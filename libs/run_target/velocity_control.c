/*!
  \file
  \brief 筐体の速度制御

  \author Satofumi KAMIMURA

  $Id: velocity_control.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "velocity_control.h"
#include "isqrt.h"
#include "robot_parameter.h"


void velocity_initialize(velocity_t *velocity)
{
    velocity->target_velocity = 0;
    velocity->current_velocity = 0;
    velocity->target_acceleration = 0;
}


long velocity_standard_velocity(velocity_t *velocity)
{
    long v = velocity->current_velocity;
    long target_velocity = velocity->target_velocity;
    const long shifted_target_velocity =
        target_velocity << VELOCITY_INTERNAL_SHIFT_WIDTH;
    const long acceleration =
        velocity->target_acceleration << CONTROL_CYCLE_MSEC_SHIFT;

    // 加速度を加味した速度を計算する
    if (v < shifted_target_velocity) {
        v += acceleration;
        if (v > shifted_target_velocity) {
            v = shifted_target_velocity;
        }

    } else if (v > shifted_target_velocity) {
        v -= acceleration;
        if (v < shifted_target_velocity) {
            v = shifted_target_velocity;
        }
    }

    velocity->current_velocity = v;
    return v >> 10;
}


long velocity_stop_to_position(velocity_t *velocity, long length)
{
    // v^2 = 2al
    long a = velocity->target_acceleration << 1;
    long v;
    const long target_velocity = velocity->target_velocity;
    long original_target_velocity;
    long return_velocity;

    if (length > 0) {
        v = isqrt(a * length);
    } else {
        v = -isqrt(a * -length);
    }

    // 目標速度よりも速くならないようにする
    if (target_velocity >= 0) {
        if (v > target_velocity) {
            v = target_velocity;
        }
    } else {
        if (v < target_velocity) {
            v = target_velocity;
        }
    }

    original_target_velocity = target_velocity;
    velocity->target_velocity = v;
    return_velocity = velocity_standard_velocity(velocity);
    velocity->target_velocity = original_target_velocity;

    return return_velocity;
}
