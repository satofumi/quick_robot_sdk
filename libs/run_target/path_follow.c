/*!
  \file
  \brief 経路の制御

  \author Satofumi KAMIMURA

  $Id: path_follow.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "path_follow.h"
#include "velocity_control.h"
#include "robot_parameter.h"
#include "isqrt.h"
#include "odometry_calculate.h"
#include "isin_icos.h"


void path_follow_initialize(path_t *path)
{
    path->is_controlling = 0;
    path->mode = PATH_UNKNOWN;

    path->default_translational_velocity = DEFAULT_TRANSLATIONAL_VELOCITY;
    path->default_rotational_velocity = DEFAULT_ROTATIONAL_VELOCITY;
    path->translational_control.target_acceleration =
        DEFAULT_TRANSLATIONAL_ACCELERATION;
    path->rotational_control.target_acceleration =
        DEFAULT_ROTATIONAL_ACCELERATION;

    velocity_initialize(&path->translational_control);
    velocity_initialize(&path->rotational_control);

    // !!! マクロにする
    // !!! 任意の距離を指定できるようにすべき
    path->follow_radius_shift_width = 10;

    path->point_x = 0;
    path->point_y = 0;
    path->point_direction = 0;

    path->line_a = 0;
    path->line_b = 0;
    path->line_c = 0;

    path->stop_length = 0;
    path->start_direction = 0;
    path->stop_direction = 0;
}


static long follow_line_rotational_velocity(path_t *path,
                                            const odometry_t* odometry)
{
    enum {
        VERTICLE_DIRECTION = 0xffff >> 2,
    };
    long x = odometry_current_mm(odometry, X_AXIS);
    long y = odometry_current_mm(odometry, Y_AXIS);
    long d;
    long abs_d;
    long target_direction;
    long direction_diff;
    const int shift_width_diff =
        path->follow_radius_shift_width - ISINCOS_SHIFT_WIDTH;

    // 追従直線との距離計算
#if 0
    d = ((path->line_a * x) + (path->line_b * y) + path->line_c) /
        path->line_sqrt_a_square_plus_b_square;
#else
    (void)x;
    (void)y;
    d = 0;
#endif
    abs_d = (d < 0) ? -d : d;

    // 直線に追従する方向の導出
    if (abs_d > (1 << path->follow_radius_shift_width)) {
        // 追従直線との距離が遠い場合、追従直線に向かう垂直な方向を向かせる
        target_direction = (d > 0) ? -VERTICLE_DIRECTION : +VERTICLE_DIRECTION;

    } else {
        // 追従直線に漸近するような方向を向かせる
        target_direction = (shift_width_diff >= 0)
            ? d << shift_width_diff : d >> -shift_width_diff;
    }

    direction_diff = odometry_direction_difference(odometry, target_direction);

    // 指定された方向を向くための速度の導出
    return velocity_stop_to_position(&path->rotational_control, direction_diff);
}


void path_follow_update(long *translational_velocity,
                        long *rotational_velocity, path_t *path,
                        const odometry_t *odometry)
{
    if (!path->is_controlling) {
        // 左右輪の速度がゼロになるように制御する
        *translational_velocity = 0;
        *rotational_velocity = 0;

    } else {
        long left_length;
        long x_diff;
        long y_diff;
        long direction_diff;

        switch (path->mode) {

        case PATH_FOLLOW_LINE:
            // 並進速度の制御
            x_diff = path->point_x - odometry_current_mm(odometry, X_AXIS);
            y_diff = path->point_y - odometry_current_mm(odometry, Y_AXIS);
            left_length = isqrt((x_diff * x_diff) + (y_diff * y_diff));
            *translational_velocity =
                velocity_stop_to_position(&path->translational_control,
                                          left_length);
            *rotational_velocity =
                follow_line_rotational_velocity(path, odometry);
            break;

        case PATH_FOLLOW_CIRCLE:
            // 回転速度の制御
            // !!! いずれ実装する
            // !!! どう停止するか、などは、いずれ考える
            *translational_velocity = 0;
            *rotational_velocity = 0;
            break;

        case PATH_TURN_TO_DIRECTION:
            *translational_velocity = 0;

            // 指定した方向を向く
            direction_diff =
                odometry_direction_difference(odometry, path->point_direction);
            *rotational_velocity =
                velocity_stop_to_position(&path->rotational_control,
                                          direction_diff);
            break;

        case PATH_UNKNOWN:
            *translational_velocity = 0;
            *rotational_velocity = 0;
            break;
        }
    }
}
