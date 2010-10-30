#ifndef QRK_MOTOR_PWM_H
#define QRK_MOTOR_PWM_H

/*!
  \file
  \brief モータの PWM 制御

  \author Satofumi KAMIMURA

  $Id: motor_pwm.h 1927 2010-09-26 23:09:26Z satofumi $
*/

typedef enum {
    MOTOR_PWM_CW,
    MOTOR_PWM_CCW,
} motor_pwm_direction_t;


//! 初期化
extern void motor_pwm_initialize(int device_id);


//! モータの PWM 出力値を設定
// !!! 256 分解能であることを書く
extern void motor_pwm_set_duty(int device_id,
                               motor_pwm_direction_t direction,
                               unsigned char duty);


/*!
  \brief サーボ・フリーに設定

  サーボをかけるときは motor_pwm_set_duty() 関数の duty をゼロに指定して呼び出すこと。
*/
extern void motor_pwm_set_servo_free(int device_id);

#endif /* !QRK_MOTOR_PWM_H */


/*!
  \page motor_pwm_h_page モータ制御

  モータドライバに対して "回転 <-> 停止" を duty を指定した PWM 信号を与えることで制御する。
*/
