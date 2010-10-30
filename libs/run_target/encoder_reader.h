#ifndef QRK_ENCODER_CONTROL_H
#define QRK_ENCODER_CONTROL_H

/*!
  \file
  \brief エンコーダ制御

  \author Satofumi KAMIMURA

  $Id: encoder_reader.h 1927 2010-09-26 23:09:26Z satofumi $
*/


#include "encoder_t.h"


//! 初期化
extern void encoder_initialize(encoder_t *encoder, int device_id);

//! エンコーダ値の更新
extern void encoder_update(encoder_t *encoder);

//! エンコーダ変位の取得
extern short encoder_difference(encoder_t *encoder);

#endif /* !QRK_ENCODER_CONTROL_H */


/*!
  \page encoder_control_h_page エンコーダ制御

  エンコーダの値を定期的に読み取り、前回に読み出した値との差を取ることでエンコーダの変位量を計算する。 \n
  エンコーダが 16 [bit] 幅の場合、エンコーダ変位量の差分は、以下のコードで計算できる。

  \code
  // unsigned short current_counter; // 今回読み出したのエンコーダ値
  // unsigned short previous_counter; // 前回読み出したエンコーダ値

  short diff = current_counter - previous_counter; // エンコーダ変位
  \endcode
  \n

  エンコーダの値を定期的に読み出すには、優先度を高めに設定した割り込みを用いること。
*/
