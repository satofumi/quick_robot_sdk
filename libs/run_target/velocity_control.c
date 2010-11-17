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
    long a = velocity->target_acceleration;
    long abs_a = (a > 0) ? a : -a;
    long abs_v = isqrt(abs_a * length << 1);
    long v;

    if (a > 0) {
        v = abs_v;
    } else {
        v = -abs_v;
    }

    // 目標速度よりも速くならないようにする
    if (velocity->target_velocity >= 0) {
        if (v > velocity->target_velocity) {
            v = velocity->target_velocity;
        }
    } else {
        if (v < velocity->target_velocity) {
            v = velocity->target_velocity;
        }
    }

    velocity->target_velocity = v;
    return velocity_standard_velocity(velocity);
}
