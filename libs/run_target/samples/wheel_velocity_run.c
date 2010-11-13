/*!
  \example wheel_velocity_run.c 車輪速の制御

  \author Satofumi KAMIMURA

  $Id: wheel_velocity_run.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "imask.h"
#include "clock_initialize.h"
#include "interrupt_priority.h"
#include "wheel_velocity.h"
#include "encoder_reader.h"
#include "timer_control.h"
#include "robot_parameter.h"


static wheel_t wheel_[2];


static void timer_handler(void)
{
    static int msec = 0;
    int i;

    if (++msec >= CONTROL_CYCLE_MSEC) {
        msec = 0;
    } else {
        return;
    }

    for (i = 0; i < 2; ++i) {
        encoder_update(&wheel_[i].encoder);
    }

    // 車輪の速度制御
    for (i = 0; i < 2; ++i) {
        wheel_velocity_control(&wheel_[i]);
    }
}


int main(void)
{
    enum {
        VELOCITY_MM_PER_SEC = 300,
    };
    int i;

    imask_initialize();
    clock_initialize();
    timer_initialize(INTERRUPT_PRIORITY_TIMER);
    set_imask_exr(0);

    for (i = 0; i < 2; ++i) {
        wheel_initialize(&wheel_[i], i);
    }
    wheel_set_velocity(&wheel_[0], VELOCITY_MM_PER_SEC);
    wheel_set_velocity(&wheel_[1], -VELOCITY_MM_PER_SEC);

    timer_set_interval_function(timer_handler);
    timer_start();

    while (1) {
        ;
    }
}
