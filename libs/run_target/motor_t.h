#ifndef QRK_MOTOR_T_H
#define QRK_MOTOR_T_H

/*!
  \file
  \brief モータ制御の管理

  \author Satofumi KAMIMURA

  $Id: motor_t.h 1927 2010-09-26 23:09:26Z satofumi $
*/


//! モータ制御の管理
typedef struct
{
    long gain_p;
    long gain_i;
    int device_id;
    long total_diff;
} motor_t;

#endif /* !QRK_MOTOR_T_H */
