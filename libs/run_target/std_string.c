/*!
  \file
  \brief <string.h> で提供している関数

  \author Satofumi KAMIMURA

  $Id: std_string.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "std_string.h"


size_t strlen(const char *s)
{
    const char *p;

    for (p = s; *p != '\0'; ++p) {
        ;
    }
    return p - s;
}


void *memcpy(void *dest, const void *src, size_t n)
{
    char *p = (char *)dest;
    const char *q = (const char *)src;
    const char *q_last = q + n;

    while (q < q_last) {
        *p++ = *q++;
    }

    return dest;
}


int strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    for (i = 0; i < n; ++i) {
        if (*s1 != *s2) {
            return *s1 - *s2;
        }
        ++s1;
        ++s2;
    }
    return 0;
}
