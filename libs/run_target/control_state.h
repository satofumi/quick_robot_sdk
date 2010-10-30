#ifndef QRK_CONTROL_STATE_H
#define QRK_CONTROL_STATE_H

/*!
  \file
  \brief 制御中の状態

  \author Satofumi KAMIMURA

  $Id: control_state.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "run_t.h"


extern void control_state(run_t *run);

#endif /* !QRK_CONTROL_STATE_H */


/*!
  \page control_state_h_page 制御中

  1 [msec] 毎に推定位置の更新と、経路追従のためのモータ制御のタスクを実行する。
*/
