/*!
  \example motor_table_pwm_test.cpp 変換テーブル値の出力テスト

  \author Satofumi KAMIMURA

  $Id$
*/

#include "motor_pwm.h"
#include "motor_table_pwm.h"
#include <cstdio>

void motor_pwm_initialize(int device_id)
{
    // 何もしない
    static_cast<void>(device_id);
}


void motor_pwm_set_duty(int device_id,
                        motor_pwm_direction_t direction,
                        unsigned char duty)
{
    printf("%d\n", duty);
}


int main(void)
{
    const int device_id = 0;

    for (int i = 0; i <= 0xff; ++i) {
        printf("%d ", i);
        motor_table_pwm_set_duty(device_id, MOTOR_PWM_CW, i);
    }
}
