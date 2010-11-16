/*!
  \example encoder_print.c エンコーダ値の表示

  \author Satofumi KAMIMURA

  $Id: encoder_print.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "imask.h"
#include "clock_initialize.h"
#include "interrupt_priority.h"
#include "encoder_reader.h"
#include "sci_read_write.h"
#include "sci_utilities.h"
#include "motor_pwm.h"


static encoder_t encoder_[2];


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
    static int total_count_[2] = { 0, 0 };
    int i;

    for (i = 0; i < 2; ++i) {
        int count;

        encoder_update(&encoder_[i]);
        count = encoder_difference(&encoder_[i]);
        total_count_[i] += count;
        sci_putint(count);
        sci_puts("(");
        sci_putint(total_count_[i]);
        sci_puts("), ");
    }
    sci_puts("\r\n");
}


int main(void)
{
    enum {
        DUTY = 0,
    };

    imask_initialize();
    clock_initialize();
    sci_initialize(INTERRUPT_PRIORITY_COMMUNICATION, 38400);

    int i;
    for (i = 0; i < 2; ++i) {
        encoder_initialize(&encoder_[i], i);
        motor_pwm_initialize(i);
        motor_pwm_set_duty(i, MOTOR_PWM_CW, DUTY);
    }


    while (1) {
        wait();
        output();
    }
}
