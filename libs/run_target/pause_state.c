/*!
  \file
  \brief 一時停止の状態

  \author Satofumi KAMIMURA

  $Id: pause_state.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "pause_state.h"
#include "emergency_io_control.h"
#include "wheel_velocity.h"


void pause_state(run_t *run)
{
    int i;

    while (true) {
        if (!emergency_io_is_emergency()) {
            return;
        }

        // 車輪の速度をゼロになるように制御する
        for (i = 0; i < NUMBER_OF_WHEELS; ++i) {
            wheel_set_velocity(&run->wheel[i], 0);
        }
    }
}
