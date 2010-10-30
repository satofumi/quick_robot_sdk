#ifndef QRK_CONNECTION_UTILITIES_H
#define QRK_CONNECTION_UTILITIES_H

/*!
  \file
  \brief 通信モジュールの補助関数

  \author Satofumi KAMIMURA

  $Id: connection_utilities.h 1927 2010-09-26 23:09:26Z satofumi $
*/


enum {
    CONNECTION_READLINE_BUFFER_SIZE = 128,
};


extern int connection_readline(char *data, int max_data_size);

#endif /* !QRK_CONNECTION_UTILITIES_H */
