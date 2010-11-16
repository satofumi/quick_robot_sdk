#ifndef QRK_PATH_T_H
#define QRK_PATH_T_H

/*!
  \file
  \brief 経路の管理

  \author Satofumi KAMIMURA

  $Id: path_t.h 1927 2010-09-26 23:09:26Z satofumi $
*/


//! 経路モード
typedef enum {
    PATH_UNKNOWN,
    PATH_FOLLOW_LINE,           //!< 直線追従
    PATH_FOLLOW_CIRCLE,         //!< 円弧追従
    PATH_TURN_TO_DIRECTION,     //!< 指定した方向を向く
} path_mode_t;


//! 経路の管理
typedef struct
{
    unsigned char is_controlling; //!< 制御中かどうか

    long target_translational_velocity; //!< 並進の目標速度
    long target_rotational_velocity;    //!< 回転の目標速度

    path_mode_t mode;
} path_t;

#endif /* !QRK_PATH_T_H */
