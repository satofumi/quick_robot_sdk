#ifndef QRK_VELOCITY_T_H
#define QRK_VELOCITY_T_H

/*!
  \file
  \brief 速度計算の管理

  \author Satofumi KAMIMURA

  $Id$
*/


typedef enum {
    VELOCITY_CONTROL_UNKNOWN,
    VELOCITY_CONTROL_POSITION,  //!< 位置制御
    VELOCITY_CONTROL_VELOCITY,  //!< 等速制御
} velocity_mode_t;


typedef struct
{
    velocity_mode_t mode;

    long target_velocity;
    long current_velocity;      // 1 << 10 の重さ
    long target_acceleration;
} velocity_t;

#endif /* !QRK_VELOCITY_T_H */
