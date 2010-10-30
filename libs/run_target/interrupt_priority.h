#ifndef QRK_INTERRUPT_PRIORITY_H
#define QRK_INTERRUPT_PRIORITY_H

/*!
  \file
  \brief 割り込み優先度の定義

  \author Satofumi KAMIMURA

  $Id: interrupt_priority.h 1927 2010-09-26 23:09:26Z satofumi $
*/


//! 割り込み優先度
enum {
    INTERRUPT_PRIORITY_ALL_MASK = 15,     //!< 全てをマスク
    // !!!
    INTERRUPT_PRIORITY_COMMUNICATION = 6, //!< 通信
    INTERRUPT_PRIORITY_TIMER = 4,        //!< タイマー
    // !!!
    INTERRUPT_PRIORITY_NO_MASK = 0, //!< マスクなし
};

#endif /* !QRK_INTERRUPT_PRIORITY_H */
