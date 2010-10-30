#ifndef QRK_SCI_READ_WRITE_H
#define QRK_SCI_READ_WRITE_H

/*!
  \file
  \brief SCI 通信

  \author Satofumi KAMIMURA

  $Id: sci_read_write.h 1927 2010-09-26 23:09:26Z satofumi $
*/


//! 初期化
extern void sci_initialize(int priority, long baudrate);

extern int sci_write(const char *data, int size);


/*!
  \brief 受信

  !!! 割り込み版では、受信済みのデータを格納して、即座に戻る。データがなかった場合は 0 を返すようにする
*/
extern int sci_read(char *data, int max_data_size);

#endif /* !QRK_SCI_READ_WRITE_H */
