/*!
  \file
  \brief 並進速・回転速の制御

  \author Satofumi KAMIMURA

  $Id: body_control.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "body_control.h"
#include "wheel_velocity.h"
#include "controller_config.h"
#include "robot_parameter.h"


void body_set_velocity(wheel_t* wheels,
                       int translational_velocity, int rotational_velocity)
{
    int velocity[NUMBER_OF_WHEELS];
    int wheel_rotational_velocity = rotational_velocity * TREAD;
    int i;

    velocity[RIGHT_WHEEL] =
        (translational_velocity + wheel_rotational_velocity) >> 2;
    velocity[LEFT_WHEEL] =
        (translational_velocity - wheel_rotational_velocity) >> 2;

    for (i = 0; i < NUMBER_OF_WHEELS; ++i) {
        wheel_set_velocity(&wheels[i], velocity[i]);
    }
}
