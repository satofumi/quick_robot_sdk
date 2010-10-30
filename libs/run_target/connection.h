#ifndef QRK_COMMUNICATION_HANDLER_H
#define QRK_COMMUNICATION_HANDLER_H

/*!
  \file
  \brief 通信モジュール

  \author Satofumi KAMIMURA

  $Id: connection.h 1927 2010-09-26 23:09:26Z satofumi $
*/


//! 初期化
extern void connection_initialize(void);


// !!! write
extern int connection_write(const char *data, int data_size);


// !!! flush
extern void connection_write_flush(void);


// !!! read
extern int connection_read(char *data, int max_data_size);

#endif /* !QRK_COMMUNICATION_HANDLER_H */
