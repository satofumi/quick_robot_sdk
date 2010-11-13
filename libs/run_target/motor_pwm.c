/*!
  \file
  \brief モータの PWM 制御

  \author Satofumi KAMIMURA

  $Id: motor_pwm.c 1927 2010-09-26 23:09:26Z satofumi $

  \page motor_pwm_c_page モータ制御の詳細

  実装は TA8429H と SH7125 に依存している。


  \section motor_pwm_c_circuit 配線

  配線は以下のようになっている。(SH7125 - TA8429H)

  - device 0
    - PE8/TIOC3A - IN1
    - PE10/TIOC3C - IN2

  - device 1
    - PE12/TIOC4A - IN1
    - PE14/TIOC4C - IN2


  \section motor_pwm_c_control 制御

  制御は TA8429H の "正転 <-> ブレーキ", "逆転 <-> ブレーキ" によって行う。

  "正転 <-> 逆転" と "正転/逆転 <-> ブレーキ" を切替える際には OFF-TIME を挿入してください、とあるが duty 比が高くなければ 100 [usec] 間隔ができるため考慮しない。ただし、PWM の制御周期はなるべく長くなるようにする。

  この実装では、TA8429H の IN1, IN2 の両方に PWM 出力できる端子を接続している。\n
  - 正転させるときは、IN2 を Hi 固定にして IN1 の PWM 出力の duty を調整する。
  - 逆転させるときは、IN1 を Hi 固定にして IN2 の PWM 出力の duty を調整する。

  この接続の場合、PWM 出力が Lo のときに回転するので、duty の比率が 1.0 のときに回転、0.0 のときに停止させようとした場合、TA8429H に与える PWM の duty は、回転させるときに 0.0 を、停止させるときに 1.0 を指定することになる。
*/

#include "motor_pwm.h"
#include "mtu2_initialize.h"
#include <7125S.H>


typedef enum {
    LO = 0,
    HI = 1,
} io_state_t;


enum {
    MAX_DUTY = 255,
};


static void set_pe8(io_state_t state)
{
    PFC.PECRL3.WORD &= ~0x0007;
    PFC.PEIORL.WORD |= 0x0100;
    if (state == HI) {
        PE.DRL.WORD |= 0x0100;
    } else {
        PE.DRL.WORD &= ~0x0100;
    }
}


void set_pe10(io_state_t state)
{
    PFC.PECRL3.WORD &= ~0x0700;
    PFC.PEIORL.WORD |= 0x0400;
    if (state == HI) {
        PE.DRL.WORD |= 0x0400;
    } else {
        PE.DRL.WORD &= ~0x0400;
    }
}


static void set_pe8_pwm(unsigned char duty)
{
    PFC.PECRL3.WORD |= 0x0001;
    MTU23.TGRB = duty;
}


static void set_pe10_pwm(unsigned char duty)
{
    PFC.PECRL3.WORD |= 0x0100;
    MTU23.TGRD = duty;
}


static void set_pe12(io_state_t state)
{
    PFC.PECRL4.WORD &= ~0x0007;
    PFC.PEIORL.WORD |= 0x1000;
    if (state == HI) {
        PE.DRL.WORD |= 0x1000;
    } else {
        PE.DRL.WORD &= ~0x1000;
    }
}


static void set_pe14(io_state_t state)
{
    PFC.PECRL4.WORD &= ~0x0700;
    PFC.PEIORL.WORD |= 0x4000;
    if (state == HI) {
        PE.DRL.WORD |= 0x4000;
    } else {
        PE.DRL.WORD &= ~0x4000;
    }
}


static void set_pe12_pwm(unsigned char duty)
{
    PFC.PECRL4.WORD |= 0x0001;
    MTU24.TGRB = duty;
}


static void set_pe14_pwm(unsigned char duty)
{
    PFC.PECRL4.WORD |= 0x0100;
    MTU24.TGRD = duty;
}


static void set_cw(int device_id, unsigned char duty)
{
    if (device_id == 0) {
        set_pe8(HI);
        set_pe10_pwm(MAX_DUTY - duty);

    } else if (device_id == 1) {
        set_pe12(HI);
        set_pe14_pwm(MAX_DUTY - duty);
    }
}


static void set_ccw(int device_id, unsigned char duty)
{
    if (device_id == 0) {
        set_pe10(HI);
        set_pe8_pwm(MAX_DUTY - duty);

    } else if (device_id == 1) {
        set_pe14(HI);
        set_pe12_pwm(MAX_DUTY - duty);
    }
}


void motor_pwm_initialize(int device_id)
{
    mtu2_initialize();

    if (device_id == 0) {
        // PE8/TIOC3A, PI10/TIOC3C 側

        // TCNT の停止
        MTU2.TSTR.BYTE &= ~0x40;

        // 周期を TGRA に設定
        MTU23.TCR.BYTE = 0x25;
        MTU23.TGRA = 0x00ff;

        // コンペアマッチ出力が TGRA と同じになるよう TGRC も設定する
        MTU23.TGRC = 0x00ff;

        // duty 出力端子の初期化
        MTU23.TIOR.BYTE.H = 0x16;     // TGRB, TGRA
        MTU23.TIOR.BYTE.L = 0x16;     // TGRD, TGRC

        MTU23.TCNT = 0;

        // PWM モード 1
        MTU23.TMDR.BYTE = 0x02;

        // TIOC3C(PE10), TIOC3A(PE8) 出力設定
        PFC.PEIORL.WORD |= 0x0500;

        // TCNT のスタート
        MTU2.TSTR.BYTE |= 0x40;

    } else if (device_id == 1) {
        // PE12/TIOC4A, PI14/TIOC4C 側

        // TCNT の停止
        MTU2.TSTR.BYTE &= ~0x80;

        // 出力設定
        MTU2.TOER.BYTE |= 0x12;

        // 周期を TGRA に設定
        MTU24.TCR.BYTE = 0x25;
        MTU24.TGRA = 0x00ff;

        // コンペアマッチ出力が TGRA と同じになるよう TGRC も設定する
        MTU24.TGRC = 0x00ff;

        // duty 出力端子の初期化
        MTU24.TIOR.BYTE.H = 0x16;     // TGRB, TGRA
        MTU24.TIOR.BYTE.L = 0x16;     // TGRD, TGRC

        MTU24.TCNT = 0;

        // PWM モード 1
        MTU24.TMDR.BYTE = 0x02;

        // TIOC4C(PE14), TIOC4A(PE12) 出力設定
        PFC.PEIORL.WORD |= 0x5000;

        // TCNT のスタート
        MTU2.TSTR.BYTE |= 0x80;
    }

    // 初期状態では、"正転 <-> ブレーキ" に設定し、duty 比をゼロにする
    set_cw(device_id, 0);
}


void motor_pwm_set_duty(int device_id,
                        motor_pwm_direction_t direction, unsigned char duty)
{
    if (direction == MOTOR_PWM_CW) {
        set_cw(device_id, duty);
    } else if (direction == MOTOR_PWM_CCW) {
        set_ccw(device_id, duty);
    }
}


void motor_pwm_set_servo_free(int device_id)
{
    // TA8429H では実現できない
    (void)device_id;
}
