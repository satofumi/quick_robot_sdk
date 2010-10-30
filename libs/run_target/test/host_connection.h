#ifndef QRK_HOST_CONNECTION_H
#define QRK_HOST_CONNECTION_H

/*!
  \file
  \brief ダミーセンサ用の PC 向け送受信関数

  実装は connection_dummy.cpp が提供する。

  \author Satofumi KAMIMURA

  $Id: host_connection.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include <string>


extern void send_command(const char *command);
extern std::string receive_response_line(void);

#endif /* !QRK_HOST_CONNECTION_H */
