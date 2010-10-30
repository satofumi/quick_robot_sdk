#ifndef QRK_WHEEL_T_H
#define QRK_WHEEL_T_H

/*!
  \file
  \brief 車輪速の管理

  \author Satofumi KAMIMURA

  $Id: wheel_t.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "encoder_t.h"
#include "motor_t.h"


//! 車輪速の管理
typedef struct
{
    encoder_t encoder;
    motor_t motor;

    int target_velocity;        //!< [mm/msec]
    int next_add_velocity;      //!< [mm/msec]
} wheel_t;

#endif /* !QRK_WHEEL_T_H */
