/*!
  \file
  \brief 制御中の状態

  \author Satofumi KAMIMURA

  $Id: control_state.c 1927 2010-09-26 23:09:26Z satofumi $

  \todo モータ回転と取り付けの関係を調整できるようにする。
*/

#include "control_state.h"
#include "imask.h"
#include "interrupt_priority.h"
#include "robot_parameter.h"
#include "pause_state.h"
#include "emergency_io_control.h"
#include "timer_control.h"
#include "protocol_handler.h"
#include "run_system.h"
#include "encoder_reader.h"
#include "odometry_calculate.h"
#include "path_follow.h"
#include "body_control.h"
#include "wheel_velocity.h"
#include <stddef.h>


static run_t *run_ = NULL;


static void control_task(void)
{
    static int msec = 0;
    int left_encoder_count;
    int right_encoder_count;
    int i;
    long translational_velocity;
    long rotational_velocity;
    unsigned char current_interrupt_priority = get_imask_exr();

    // タイムスタンプの更新
    run_system_increment_timestamp(&run_->run_system);

    // CONTROL_CYCLE_MSEC 毎に処理を行う
    if (++msec >= CONTROL_CYCLE_MSEC) {
        msec = 0;
    } else {
        return;
    }

    // エンコーダ値の更新
    set_imask_exr(INTERRUPT_PRIORITY_ALL_MASK);
    for (i = 0; i < NUMBER_OF_WHEELS; ++i) {
        encoder_update(&run_->wheel[i].encoder);
    }
    set_imask_exr(current_interrupt_priority);

    // 推定自己位置の更新
    left_encoder_count = encoder_difference(&run_->wheel[LEFT_WHEEL].encoder);
    right_encoder_count = encoder_difference(&run_->wheel[RIGHT_WHEEL].encoder);
    odometry_update(&run_->odometry, +right_encoder_count, -left_encoder_count);

    // 走行経路の指示
    switch (run_->run_system.mode) {
    case NORMAL_CONTROL:
        path_follow_update(&translational_velocity,
                           &rotational_velocity, &run_->path, &run_->odometry);
        body_set_velocity(run_->wheel,
                          translational_velocity, rotational_velocity);
        break;

    case DIRECT_WHEEL_CONTROL:
        // 何も変更しない
        break;
    }

    // 設定された車輪速になるように制御する
    for (i = 0; i < NUMBER_OF_WHEELS; ++i) {
        wheel_velocity_control(&run_->wheel[i]);
    }
}


void control_state(run_t *run)
{
    run_ = run;

    timer_set_interval_function(control_task);
    timer_start();

    while (true) {
#if 0
        // !!! 未配線のため、コメントアウト
        if (emergency_io_is_emergency()) {
            pause_state(run);
        }
#endif

        // 通信による状態の更新
        protocol_update(run);
    }
}
