#ifndef QRK_PAUSE_STATE_H
#define QRK_PAUSE_STATE_H

/*!
  \file
  \brief 一時停止の状態

  \author Satofumi KAMIMURA

  $Id: pause_state.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "run_t.h"


extern void pause_state(run_t *run);

#endif /* !QRK_PAUSE_STATE_H */


/*!
  \page pause_state_h_page 一時停止

  外部からの緊急停止の指示を実現する。\n
  この状態では、両輪の速度制御をゼロにする。 ただし、この状態を抜けたときには、それ以前の走行状態に復帰する。

  一時停止の状態への遷移は "stop" 信号がアクティブなときに発生し、復帰は "start" 信号の立上りとする。

  \dot
  digraph pause_state {
    control_state -> pause_state [label = "stop"];
    pause_state -> control_state [label = "start"];

    control_state [label = "制御中"];
    pause_state [label = "一時停止"];

    { rank = same; control_state pause_state }
  \enddot
*/
