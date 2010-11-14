/*!
  \file
  \brief 16 進 ASCII 文字列変換

  \author Satofumi KAMIMURA

  $Id$
*/

#include "itoh.h"


void itoh(char *dest, long value, size_t byte_size)
{
    size_t i;
    size_t n = byte_size * 2;

    for (i = 0; i < n; ++i) {
        unsigned char number = value & 0xf;

        dest[n - 1 - i] = number + ((number <= 9) ? '0' : ('a' - 10));
        value >>= 4;
    }
}
