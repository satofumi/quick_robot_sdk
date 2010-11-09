#ifndef QRK_MOTOR_TABLE_PWM_H
#define QRK_MOTOR_TABLE_PWM_H

/*!
  \file
  \brief 補正テーブルを用いたモータの PWM 制御

  \author Satofumi KAMIMURA

  $Id: motor_pwm.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "motor_pwm.h"


//! 初期化
extern void motor_table_pwm_initialize(int device_id);


//! モータの PWM 出力値を設定
// !!! 256 分解能であることを書く
extern void motor_table_pwm_set_duty(int device_id,
                                     motor_pwm_direction_t direction,
                                     unsigned char duty);


#endif /* !QRK_MOTOR_TABLE_PWM_H */


/*!
  \page motor_table_pwm_h_page 補正テーブルを用いた PWM 制御

  モータと制御回路によっては、PWM の duty 比とモータの回転速度の関係は線形ではない。そこで、指定した値とモータの回転速度との関係が線形になるように、duty 比の出力を調整するためのモジュールを作成する。

  - 目的
    - 指定した値の増加とモータ回転速の増加が線形になるようにする。

  - 実現方法
    - PWM の duty 比は 0 から 255 の数値で指定するものとする。
    - テーブルで、指定した値に対応する duty 比の出力を保持する。

  - 実験、評価
    - テーブル作成のためのデータ取得を行う。
      - モータに負化をかけない状態で実験する。
      - PWM の duty 比を変更しながら、実際のモータ回転速を記録する。
        - duty 比を 1 増加させるごとに、1 [msec] 以上だけ待機させ、回転速が安定するのを待ち、回転速を記録する。

  - 実際の実装方法
    - 逆起電力は考慮しない。
    - テーブルの要素数は 32 とし、途中の値は両端の値を用いて計算する。
      - ループと左シフトを用いて、２分法で値を計算する。
*/
