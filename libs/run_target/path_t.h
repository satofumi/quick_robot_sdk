#ifndef QRK_PATH_T_H
#define QRK_PATH_T_H

/*!
  \file
  \brief 経路の管理

  \author Satofumi KAMIMURA

  $Id: path_t.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "velocity_t.h"


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
    path_mode_t mode;

    long default_translational_velocity; //!< 並進の目標速度のデフォルト値
    long default_rotational_velocity; //!< 回転の目標速度のデフォルト値

    velocity_t translational_control;
    velocity_t rotational_control;

    long follow_radius_shift_width;

    long point_x;
    long point_y;
    long point_direction;

    long line_a;
    long line_b;
    long line_c;
    long line_sqrt_a_square_plus_b_square;

    long stop_length;
    unsigned short start_direction;
    unsigned short stop_direction;
} path_t;

#endif /* !QRK_PATH_T_H */
