#ifndef QRK_ITOH_H
#define QRK_ITOH_H

/*!
  \file
  \brief 16 進 ASCII 文字列変換

  \author Satofumi KAMIMURA

  $Id$
*/

#include <stddef.h>


extern void itoh(char *dest, long value, size_t byte_size);

#endif /* !QRK_ITOH_H */
