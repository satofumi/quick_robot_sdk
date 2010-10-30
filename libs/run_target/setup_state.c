/*!
  \file
  \brief 初期化の状態

  \author Satofumi KAMIMURA

  $Id: setup_state.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "setup_state.h"
#include "imask.h"
#include "clock_initialize.h"
#include "timer_control.h"
#include "run_system.h"
#include "emergency_io_control.h"
#include "odometry_calculate.h"
#include "path_follow.h"
#include "wheel_velocity.h"
#include "protocol_handler.h"
#include "interrupt_priority.h"


void setup_state(run_t *run)
{
    int i;

    // システム
    imask_initialize();
    clock_initialize();
    timer_initialize(INTERRUPT_PRIORITY_TIMER);

    // 走行モジュール
    run_system_initialize(&run->run_system);
    emergency_io_initialize();
    odometry_initialize(&run->odometry);
    path_follow_initialize(&run->path);
    for (i = 0; i < NUMBER_OF_WHEELS; ++i) {
        wheel_initialize(&run->wheel[i], i);
    }

    // 通信
    protocol_initialize();

    set_imask_exr(INTERRUPT_PRIORITY_NO_MASK);
}
