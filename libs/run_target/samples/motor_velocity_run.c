/*!
  \example motor_velocity_out.c モータの速度制御サンプル

  \author Satofumi KAMIMURA

  $Id: motor_velocity_run.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "clock_initialize.h"
#include "imask.h"
#include "interrupt_priority.h"
#include "motor_velocity.h"
#include "timer_control.h"
#include "encoder_reader.h"
#include "robot_parameter.h"


static encoder_t encoder_[2];
static motor_t motor_[2];


enum {
    TARGET_COUNT = 1,
};


static void timer_handler(void)
{
    static int msec = 0;
    int current_count[2];
    int i;

    if (++msec >= CONTROL_CYCLE_MSEC) {
        msec = 0;
    } else {
        return;
    }

    for (i = 0; i < 2; ++i) {
        encoder_update(&encoder_[i]);
        current_count[i] = encoder_difference(&encoder_[i]);
    }
    motor_velocity_control(&motor_[0], +TARGET_COUNT, current_count[0]);
    motor_velocity_control(&motor_[1], -TARGET_COUNT, current_count[1]);
}


int main(void)
{
    int i;

    imask_initialize();
    clock_initialize();
    timer_initialize(INTERRUPT_PRIORITY_TIMER);
    set_imask_exr(0);

    for (i = 0; i < 2; ++i) {
        encoder_initialize(&encoder_[i], i);
        motor_velocity_initialize(&motor_[i], i);
    }

    timer_set_interval_function(timer_handler);
    timer_start();

    while (1) {
        ;
    }
}
