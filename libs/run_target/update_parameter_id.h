#ifndef UPDATE_PARAMETER_ID_H
#define UPDATE_PARAMETER_ID_H

/*!
  \file
  \brief パラメータ更新用の ID 定義

  \author Satofumi KAMIMURA

  $Id$
*/


typedef enum {
    UNKNOWN_ID = 0,
    ENCODER_RESOLUTION_ID ,     // エンコーダ分解能
    MOTOR_P_GAIN_ID,            // モータ制御の P ゲイン
    MOTOR_I_GAIN_ID,            // モータ制御の I ゲイン
    WHEEL_RADIUS_ID,            // 車輪径 (左右で独立)
    BOTY_TREAD_ID,              // 筐体のトレッド
} parameter_id_t;

#endif /* !UPDATE_PARAMETER_ID_H */
