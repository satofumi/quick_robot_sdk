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
    //odometry->translational_velocity = 0;
}


void odometry_update(odometry_t *odometry,
                     int right_encoder_difference,
                     int left_encoder_difference)
{
    enum {
        COUNT_PER_M = (int)(1000.0 * ENCODER_RESOLUTION
                            / (2.0 * M_PI * WHEEL_RADIUS_MM)),
        DIRECTION_COUNT_MAX = (int)(1.0 * TREAD * ENCODER_RESOLUTION
                                    / WHEEL_RADIUS_MM),
    };

    long direction_count;
    unsigned short direction;
    long translational_count;
    int i;

    // 向きの更新
    direction_count = odometry->direction_count;
    direction_count += right_encoder_difference - left_encoder_difference;
    if (direction_count < 0) {
        direction_count += DIRECTION_COUNT_MAX;
    } else if (direction_count > DIRECTION_COUNT_MAX) {
        direction_count -= DIRECTION_COUNT_MAX;
    }
    direction = (direction_count << 16) / DIRECTION_COUNT_MAX;
    odometry->direction_count = direction_count;
    odometry->direction = direction;

    // 並進速度
    translational_count = right_encoder_difference + left_encoder_difference;

    // 位置の更新
    odometry->xy_count[X_AXIS] += (translational_count * icos(direction)) >> 1;
    odometry->xy_count[Y_AXIS] += (translational_count * isin(direction)) >> 1;

    const long m_count = COUNT_PER_M << ISINCOS_SHIFT_WIDTH;
    for (i = 0; i < NUMBER_OF_AXIS; ++i) {
        long count = odometry->xy_count[i];
        if (count >= m_count) {
            count -= m_count;
            ++odometry->m[i];

        } else if (count < 0) {
            count += m_count;
            --odometry->m[i];
        }
        odometry->mm[i] = 1000 * count / m_count;

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
