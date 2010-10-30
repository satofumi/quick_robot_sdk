#ifndef QRK_PROTOCOL_HANDLER_H
#define QRK_PROTOCOL_HANDLER_H

/*!
  \file
  \brief 通信プロトコルの処理

  \author Satofumi KAMIMURA

  $Id: protocol_handler.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "run_t.h"


//! 初期化
extern void protocol_initialize(void);


//! 通信への応答
extern void protocol_update(run_t *run);

#endif /* !QRK_PROTOCOL_HANDLER_H */


/*!
  \page protocol_handler_h_page 通信プロトコルの処理 (記述中)

  - モータ制御の P ゲイン, I ゲインを変更できるようにする。

  !!!
*/
