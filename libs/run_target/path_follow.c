/*!
  \file
  \brief 経路の制御

  \author Satofumi KAMIMURA

  $Id: path_follow.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "path_t.h"
#include "position_handler.h"


void path_follow_initialize(path_t *path)
{
    path->is_controlling = 0;
    path->mode = PATH_UNKNOWN;
    path->target_translational_velocity = 0;
    path->target_rotational_velocity = 0;
    // !!!
}


void path_follow_update(long *translational_velocity,
                        long *rotational_velocity, path_t *path)
{
    // 指定がない場合は、左右輪の速度がゼロになるように制御する
    *translational_velocity = 0;
    *rotational_velocity = 0;

    if (!path->is_controlling) {
        // 左右輪の速度がゼロになるように制御する
        // 速度がゼロのままこのモジュールを抜ける

    } else {
        switch (path->mode) {

        case PATH_FOLLOW_LINE:
            // 並進速度の制御
            // !!! 停止するあたりは、いずれ実装する
            *translational_velocity = path->target_translational_velocity;
            // !!!
            *rotational_velocity = -1;
            break;

        case PATH_FOLLOW_CIRCLE:
            // 回転速度の制御
            // !!! 停止するあたりは、いずれ実装する
            *translational_velocity = path->target_translational_velocity;

            // !!!
            *rotational_velocity = -1;
            break;

        case PATH_TURN_TO_DIRECTION:
            // 指定した方向を向く
            // !!!
            *rotational_velocity = -1;
            break;

        case PATH_UNKNOWN:
            break;
        }
    }
}
