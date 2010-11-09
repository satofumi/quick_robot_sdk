/*!
  \file
  \brief motor_table_pwm.c 用のデータ出力プログラム

  \author Satofumi KAMIMURA

  $Id$
*/

#include "imask.h"
#include "clock_initialize.h"
#include "interrupt_priority.h"
#include "sci_read_write.h"
#include "sci_utilities.h"
#include "encoder_reader.h"
#include "motor_pwm.h"


static encoder_t encoder_;

enum {
    DEVICE_ID = 0,
};


static void wait(void)
{
    volatile int i;
    volatile int j;

    for (i = 0; i < 50000; ++i) {
        for (j = 0; j < 2; ++j) {
            ;
        }
    }
}


static void output(void)
{
    int count;

    encoder_update(&encoder_);
    count = encoder_difference(&encoder_);

    sci_putint(count);
    sci_puts("\r\n");
}


int main(void)
{
    enum {
        DUTY_MAX = 255,
    };
    int i;

    // 初期化
    imask_initialize();
    clock_initialize();
    sci_initialize(INTERRUPT_PRIORITY_COMMUNICATION, 38400);
    set_imask_exr(0);

    // PWM を変更しながら、エンコーダの値を出力する
    motor_pwm_initialize(DEVICE_ID);
    encoder_initialize(&encoder_, DEVICE_ID);
    for (i = 0; i < DUTY_MAX; ++i) {
        motor_pwm_set_duty(DEVICE_ID, MOTOR_PWM_CW, i);
        wait();
        output();
    }

    // 停止
    motor_pwm_set_duty(DEVICE_ID, MOTOR_PWM_CW, 0);
    while (1) {
        ;
    }
}
