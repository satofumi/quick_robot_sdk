/*!
  \file
  \brief 筐体の速度制御

  \author Satofumi KAMIMURA

  $Id: velocity_control.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "velocity_control.h"


void velocity_initialize(velocity_t *velocity)
{
    velocity->mode = VELOCITY_CONTROL_UNKNOWN;
    velocity->target_velocity = 0;
    velocity->current_velocity = 0;
    velocity->target_acceleration = 0;
}


long velocity_stop_to_position(velocity_t *velocity, long length)
{
    // !!! v^2 = 2al

    (void)velocity;
    (void)length;
    // !!!
    return -1;
}
