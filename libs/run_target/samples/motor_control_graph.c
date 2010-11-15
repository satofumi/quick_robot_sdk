/*!
  \example motor_control_graph.c モータ制御時のグラフ作成プログラム

  \author Satofumi KAMIMURA

  $Id$
*/

#include "clock_initialize.h"
#include "imask.h"
#include "interrupt_priority.h"
#include "motor_velocity.h"
#include "timer_control.h"
#include "encoder_reader.h"
#include "robot_parameter.h"
#include "sci_read_write.h"
#include "sci_utilities.h"


static encoder_t encoder_;
static motor_t motor_;


enum {
    TARGET_COUNT = 3,
};


static void timer_handler(void)
{
    static int msec = 0;
    int current_count;

    if (++msec >= CONTROL_CYCLE_MSEC) {
        msec = 0;
    } else {
        return;
    }

    encoder_update(&encoder_);
    current_count = encoder_difference(&encoder_);

    motor_velocity_control(&motor_, +TARGET_COUNT, current_count);

    // エンコーダ値の出力
    sci_putint(current_count);
    sci_write(",", 1);
}


int main(void)
{
    imask_initialize();
    clock_initialize();
    timer_initialize(INTERRUPT_PRIORITY_TIMER);
    sci_initialize(INTERRUPT_PRIORITY_COMMUNICATION, 38400);
    set_imask_exr(0);

    encoder_initialize(&encoder_, 0);
    motor_velocity_initialize(&motor_, 0);

    timer_set_interval_function(timer_handler);
    timer_start();

    while (1) {
        ;
    }
}
