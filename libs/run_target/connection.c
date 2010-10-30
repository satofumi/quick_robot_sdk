/*!
  \file
  \brief 通信モジュール

  \author Satofumi KAMIMURA

  $Id: connection.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "connection.h"
#include "sci_read_write.h"
#include "interrupt_priority.h"

enum {
    SCI_BAUDRATE = 38400,
};


void connection_initialize(void)
{
    sci_initialize(INTERRUPT_PRIORITY_COMMUNICATION, SCI_BAUDRATE);
}


int connection_write(const char *data, int data_size)
{
    return sci_write(data, data_size);
}


void connection_write_flush(void)
{
    // !!! 未実装
}


int connection_read(char *data, int max_data_size)
{
    return sci_read(data, max_data_size);
}
