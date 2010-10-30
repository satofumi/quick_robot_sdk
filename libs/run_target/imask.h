#ifndef QRK_IMASK_H
#define QRK_IMASK_H

/*!
  \file
  \brief 割り込みマスクの制御

  \author Satofumi KAMIMURA

  $Id: imask.h 1927 2010-09-26 23:09:26Z satofumi $
*/


/*!
  \brief 初期化

  割り込み設定を初期化する。\n
  初期状態では、割り込みマスクの設定を最大に設定し、割り込みが発生しないようにする。
*/
extern void imask_initialize(void);

#if defined(HOST_COMPILE)
extern void set_imask_exr(unsigned char level);
extern unsigned char get_imask_exr(void);
#endif

// !!!

#endif /* !QRK_IMASK_H */
