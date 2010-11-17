#ifndef QRK_ODOMETRY_T_H
#define QRK_ODOMETRY_T_H

/*!
  \file
  \brief 推定自己位置の管理

  \author Satofumi KAMIMURA

  $Id: odometry_t.h 1927 2010-09-26 23:09:26Z satofumi $
*/


enum {
    NUMBER_OF_AXIS = 2,
    X_AXIS = 0,
    Y_AXIS = 1,
};


//! 推定自己位置の管理
typedef struct
{
    // 向き情報
    long direction_count;
    unsigned short direction;

    // 位置情報
    long xy_count[NUMBER_OF_AXIS];
    long mm[NUMBER_OF_AXIS];
    long m[NUMBER_OF_AXIS];
    long km[NUMBER_OF_AXIS];

    // 速度情報
    long translational_velocity;
    long rotational_velocity;
} odometry_t;

#endif /* !QRK_ODOMETRY_T_H */
