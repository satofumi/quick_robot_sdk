/*!
  \file
  \brief 入出力の補助関数

  \author Satofumi KAMIMURA

  $Id: sci_utilities.c 1927 2010-09-26 23:09:26Z satofumi $

  \todo putint() を atoi() を使った実装に変更する
*/

#include "sci_utilities.h"
#include "sci_read_write.h"


int sci_puts(const char *data)
{
    const char *p;
    for (p = data; *p != '\0'; ++p) {
        ;
    }
    return sci_write(data, p - data);
}


int sci_putint(long value)
{
    char buffer[] = { '\0', '\0', '\0', '\0',
                      '\0', '\0', '\0', '\0',
                      '\0', '\0', '\0', '\0', '\0' };
    int sign = -1;
    int index = 11;
    long calc_value = value;

    if (calc_value >= 0) {
        // 負の値の方が、表現できる数値が１大きいため、負の数で計算する
        calc_value = -calc_value;
        sign = +1;
    }

    do {
        buffer[index--] = '0' - (calc_value % 10);
        calc_value /= 10;
    } while (calc_value != 0);

    if (sign < 0) {
        buffer[index--] = '-';
    }
    ++index;

    return sci_puts(&buffer[index]);
}
