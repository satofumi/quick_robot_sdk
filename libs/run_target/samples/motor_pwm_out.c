/*!
  \example motor_pwm_out.c モータの PWM 出力サンプル

  \author Satofumi KAMIMURA

  $Id: motor_pwm_out.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "clock_initialize.h"
#include "motor_pwm.h"


int main(void)
{
    enum {
        DUTY = 255 * 30 / 100,
    };
    int i;

    clock_initialize();

    for (i = 0; i < 2; ++i) {
        motor_pwm_initialize(i);
    }
    motor_pwm_set_duty(0, MOTOR_PWM_CW, DUTY);
    motor_pwm_set_duty(1, MOTOR_PWM_CW, DUTY);

#if 0
    for (i = 0; i < 2; ++i) {
        motor_pwm_set_duty(i, MOTOR_PWM_CCW, 254);
        motor_pwm_set_duty(i, MOTOR_PWM_CCW, 0);
    }
#endif

    while (1) {
        ;
    }
}
