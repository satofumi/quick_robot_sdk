#ifndef QRK_C_RUN_T_H
#define QRK_C_RUN_T_H

/*!
  \file
  \brief 走行制御の管理

  \author Satofumi KAMIMURA

  $Id: run_driver_t.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "urg_connection.h"


enum {
    RUN_DRIVER_T_BUFFER_SIZE = 128,
};


//! 走行制御の管理
typedef struct
{
    char error_message[RUN_DRIVER_T_BUFFER_SIZE];
    urg_connection_t connection;
    int is_opened;
    int timeout;
} run_driver_t;

#endif /* !QRK_C_RUN_T_H */
