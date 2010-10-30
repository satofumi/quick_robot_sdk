#ifndef QRK_EMERGENCY_IO_CONTROL_H
#define QRK_EMERGENCY_IO_CONTROL_H

/*!
  \file
  \brief 緊急停止 IO の制御

  \author Satofumi KAMIMURA

  $Id: emergency_io_control.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include <stdbool.h>


//! 初期化
extern void emergency_io_initialize(void);


//! 緊急停止すべきかを取得
extern bool emergency_io_is_emergency(void);


//! 強制的に緊急停止状態に遷移させる
extern void emergency_io_force_set_emergency(void);

#endif /* !QRK_EMERGENCY_IO_CONTROL_H */


/*!
  \page emergency_io_control_h_page 緊急停止 IO の制御

  緊急停止ボタンと再開ボタンの入力信号を扱う。

  \image html emergency_io_2_button.jpg 緊急停止ボタンと再開ボタンの場合の配線

  emergency_io_is_emergency() は、停止すべきかどうかの内部状態を持つ。\n

  停止すべき状態への遷移条件は

  - 緊急停止ボタンの入力信号が Low になったとき

  とし、再開してもよい状態への遷移条件は

  - 緊急停止ボタンの入力信号が High であり、かつ再開ボタンの信号が Low から High に遷移した場合

  とする。

  押下が保持される緊急停止ボタンのみの構成の場合は、緊急停止ボタンの信号を再開ボタン用の信号に接続すればよい。

  \image html emergency_io_1_button.jpg 緊急停止ボタンのみの場合の配線
*/
