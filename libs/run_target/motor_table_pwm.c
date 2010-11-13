/*!
  \file
  \brief 補正テーブルを用いたモータの PWM 制御

  \author Satofumi KAMIMURA

  $Id: motor_pwm.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "motor_table_pwm.h"


enum {
    INDEX_SHIFT_WIDTH = 5,
    INDEX_WIDTH = 1 << INDEX_SHIFT_WIDTH,
};


// 最後の要素は番兵
// テーブル値は 255 まで 32 毎の値を格納しており、
// 実際の値は 2 分探索で計算する
static unsigned char convert_table[] = {
    0, 50, 80, 110,
    145, 170, 190, 210,
    230,
};


void motor_table_pwm_initialize(int device_id)
{
    motor_pwm_initialize(device_id);
}

void motor_table_pwm_set_duty(int device_id,
                              motor_pwm_direction_t direction,
                              unsigned char duty)
{
    unsigned char actual_duty;

    if (duty <= 1) {
        actual_duty = 0;
    } else {
        // ２分探索で、目的の duty に相当する値を計算する
        int low_index = duty >> INDEX_SHIFT_WIDTH;
        unsigned char low = convert_table[low_index];
        unsigned char high = convert_table[low_index + 1];

        int low_duty = duty & ~(INDEX_WIDTH - 1);
        int high_duty = duty + INDEX_WIDTH;
        while (1) {
            int middle_duty = (low_duty + high_duty) >> 1;
            unsigned char middle = (low + high) >> 1;
            if (duty == middle_duty) {
                actual_duty = middle;
                break;

            } else if (duty > middle_duty) {
                low_duty = middle_duty;
                low = middle;
            } else {
                high_duty = middle_duty;
                high = middle;
            }
        }
    }
    motor_pwm_set_duty(device_id, direction, actual_duty);
}
