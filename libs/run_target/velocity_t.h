#ifndef QRK_VELOCITY_T_H
#define QRK_VELOCITY_T_H

/*!
  \file
  \brief 速度計算の管理

  \author Satofumi KAMIMURA

  $Id$
*/

enum {
    VELOCITY_INTERNAL_SHIFT_WIDTH = 10,
};

typedef struct
{
    long target_velocity;
    long current_velocity;      // 1 << 10 の重さ
    long target_acceleration;
} velocity_t;

#endif /* !QRK_VELOCITY_T_H */
