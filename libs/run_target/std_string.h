#ifndef STD_STRING_H
#define STD_STRING_H

/*!
  \file
  \brief <string.h> で提供している関数

  \author Satofumi KAMIMURA

  $Id: std_string.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include <stddef.h>


extern size_t strlen(const char *s);
extern void *memcpy(void *dest, const void *src, size_t n);
extern int strncmp(const char *s1, const char *s2, size_t n);

#endif /* !STD_STRING_H */
