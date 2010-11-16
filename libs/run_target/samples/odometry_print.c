/*!
  \example odometry_print.c オドメトリ位置の出力

  \author Satofumi KAMIMURA

  $Id$
*/

#include "interrupt_priority.h"
#include "sci_read_write.h"
#include "sci_utilities.h"
#include "imask.h"
#include "clock_initialize.h"
#include "timer_control.h"
#include "odometry_calculate.h"
#include "encoder_reader.h"
#include "controller_config.h"
#include "motor_pwm.h"


static odometry_t odometry_;
static encoder_t encoder_[2];


static void timer_handler(void)
{
    enum {
        CONTROL_CYCLE_MSEC_SHIFT = 3,
        CONTROL_CYCLE_MSEC = 1 << CONTROL_CYCLE_MSEC_SHIFT, //!< 制御周期 [msec]
    };
    static int msec_counter = 0;
    static int cycle_msec = 0;
    long left_encoder_count;
    long right_encoder_count;
    int i;

    // CONTROL_CYCLE_MSEC 毎に処理を行う
    ++msec_counter;
    ++cycle_msec;
    if (cycle_msec >= CONTROL_CYCLE_MSEC) {
        cycle_msec = 0;
    } else {
        return;
    }

    // 位置の更新
    for (i = 0; i < 2; ++i) {
        encoder_update(&encoder_[i]);
    }
    right_encoder_count = encoder_difference(&encoder_[RIGHT_WHEEL]);
    left_encoder_count = encoder_difference(&encoder_[LEFT_WHEEL]);
    odometry_update(&odometry_, right_encoder_count, -left_encoder_count);

    if (msec_counter >= 1000) {
        msec_counter = 0;

#if 0
        sci_putint(right_encoder_count);
        sci_puts(" ");
        sci_putint(left_encoder_count);
#endif
#if 1
        sci_puts("(");
        sci_putint(odometry_.km[X_AXIS]);
        sci_puts(" ");
        sci_putint(odometry_.m[X_AXIS]);
        sci_puts(" ");
        sci_putint(odometry_.mm[X_AXIS]);
        sci_puts(",");
        sci_putint(odometry_.km[Y_AXIS]);
        sci_puts(" ");
        sci_putint(odometry_.m[Y_AXIS]);
        sci_puts(" ");
        sci_putint(odometry_.mm[Y_AXIS]);
        sci_puts("),");
#endif
#if 1
        //sci_putint(odometry_.direction_count);
        //sci_puts(" ");
        sci_putint(odometry_.direction);
        sci_puts(",");
#endif
#if 0
        sci_putint(odometry_.xy_count[X_AXIS]);
        sci_puts(" ");
        sci_putint(odometry_.xy_count[Y_AXIS]);
        sci_puts(",");
#endif
        sci_puts("\r\n");
    }
}


int main(void)
{
    int i;

    imask_initialize();
    clock_initialize();
    sci_initialize(INTERRUPT_PRIORITY_COMMUNICATION, 38400);
    timer_initialize(INTERRUPT_PRIORITY_TIMER);
    for (i = 0; i < 2; ++i) {
        motor_pwm_initialize(i);
        encoder_initialize(&encoder_[i], i);
    }
    odometry_initialize(&odometry_);
    set_imask_exr(0);

    timer_set_interval_function(timer_handler);
    timer_start();

    //motor_pwm_set_duty(0, MOTOR_PWM_CCW, 50);
    //motor_pwm_set_duty(1, MOTOR_PWM_CW, 50);

    while (1) {
        ;
    }
}
