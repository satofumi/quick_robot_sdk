/*!
  \file
  \brief 16進文字列の数値への変換

  \author Satofumi KAMIMURA

  $Id: htoi.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "htoi.h"


unsigned long htoi(const char *hex_data, int data_size)
{
    int i;
    long value = 0;

    for (i = 0; i < data_size; ++i) {
        char ch = hex_data[i];
        value <<= 4;

        if ((ch >= '0') && (ch <= '9')) {
            value += ch - '0';
        } else if ((ch >= 'a') && (ch <= 'f')) {
            value += (ch - 'a') + 10;
        } else if ((ch >= 'A') && (ch <= 'F')) {
            value += (ch - 'A') + 10;
        }
    }

    return value;
}
