/*!
  \file
  \brief 推定自己位置の計算

  \author Satofumi KAMIMURA

  $Id: odometry_calculate.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "odometry_calculate.h"
#include "robot_parameter.h"
#include "controller_config.h"
#include "isin_icos.h"
#include <math.h>


void odometry_initialize(odometry_t *odometry)
{
    int i;

    odometry->direction_count = 0;
    odometry->direction = 0;

    for (i = 0; i < NUMBER_OF_AXIS; ++i) {
        odometry->xy_count[i] = 0;
        odometry->mm[i] = 0;
        odometry->km[i] = 0;
    }
    odometry->straight_velocity = 0;
}


void odometry_update(odometry_t *odometry,
                     int right_encoder_difference,
                     int left_encoder_difference)
{
    enum {
        MM_SHIFT_WIDTH = 10,
        MM_PER_COUNT = (int)(2 * M_PI * (WHEEL_RADIUS_MM *
                                         (1 << MM_SHIFT_WIDTH))
                             / ENCODER_RESOLUTION),
        M_PER_COUNT = (int)(2 * M_PI * (WHEEL_RADIUS_MM * 1000.0)
                            / ENCODER_RESOLUTION),
        DIRECTION_COUNT_MAX = (int)(2 * M_PI * TREAD * (1 << MM_SHIFT_WIDTH)),
    };

    long wheel_mm[NUMBER_OF_WHEELS];
    long direction_count;
    unsigned short direction;
    long straight_velocity;
    int i;

    // 各輪の移動距離の計算
    wheel_mm[RIGHT_WHEEL] = MM_PER_COUNT * right_encoder_difference;
    wheel_mm[LEFT_WHEEL] = MM_PER_COUNT * left_encoder_difference;

    // 向きの更新
    direction_count = odometry->direction_count;
    direction_count += wheel_mm[RIGHT_WHEEL] - wheel_mm[LEFT_WHEEL];
    if (direction_count < 0) {
        direction_count += DIRECTION_COUNT_MAX;
    } else if (direction_count > DIRECTION_COUNT_MAX) {
        direction_count -= DIRECTION_COUNT_MAX;
    }
    direction =
        (direction_count << (ODOMETFY_DIRECTION_BIT_WIDTH - MM_SHIFT_WIDTH))
        / (DIRECTION_COUNT_MAX >> MM_SHIFT_WIDTH);
    odometry->direction_count = direction_count;
    odometry->direction = direction;

    // 並進速度
    straight_velocity = (wheel_mm[RIGHT_WHEEL] + wheel_mm[LEFT_WHEEL]);
    odometry->straight_velocity = straight_velocity;

    // 位置の更新
    // 並進速度の計算で 2 で割らなかったぶんを、ここで割る
    odometry->xy_count[X_AXIS] +=
        (straight_velocity * icos(direction)) >> (MM_SHIFT_WIDTH + 1);
    odometry->xy_count[Y_AXIS] +=
        (straight_velocity * isin(direction)) >> (MM_SHIFT_WIDTH + 1);

    const long compare_value = (M_PER_COUNT * 2) << ISINCOS_SHIFT_WIDTH;
    for (i = 0; i < NUMBER_OF_AXIS; ++i) {
        long count = odometry->xy_count[i];
        if (count >= compare_value) {
            count -= compare_value;
            ++odometry->m[i];

        } else if (count < 0) {
            count += compare_value;
            --odometry->m[i];
        }
        odometry->mm[i] = count * 1000 / compare_value;

        if (odometry->m[i] >= 1000) {
            odometry->m[i] -= 1000;
            ++odometry->km[i];

        } else if (odometry->m[i] < 0) {
            odometry->m[i] += 1000;
            --odometry->km[i];
        }
        odometry->xy_count[i] = count;
    }
}
