/*
  \brief 整数型の平方根関数

  http://www.infoeddy.ne.jp/~tensyo/prog/ALGO.HTM#STEPMT より

  \ahthor Satofumi KAMIMURA (maintenance)
  $Id: isqrt.c 286 2008-10-20 09:40:22Z satofumi $
*/

#include "isqrt.h"


/*!
  整数型の平方根を計算する

  \param x [i] 正の整数
  \retval int 平方根の負でない値

  \attention 多少の誤差あり
*/
unsigned long isqrt(unsigned long i)
{
    int sft = 0;
    unsigned short y, y0, y1, sum;

    if (i < 2) {
        return i;
    }
    while (0 < (signed long)i) { /* MSB=1 になるまで左シフト */
        i <<= 1L;
        sft++;
    }
    y1 = (unsigned short)(i >> 16L);
    y0 = (~y1) & 0xffff;
    y = (y0 * 0x8000) >> 16;
    sum = y;
    y = (y * y0) >> 16;
    y = (y * 0x4000) >> 16;	/* シフトで代用可 */
    sum += y;
    y = (y * y0) >> 16;
    y = (y * 0x8000) >> 16;	/* シフトで代用可 */
    sum += y;
    y = (y * y0) >> 16;
    y = (y * 40960) >> 16;
    sum += y;			/* 40960 = 5*2^13  */
    y = (y * y0) >> 16;
    y = (y * 45875) >> 16;
    sum += y;
    y = ~sum;
    y +=  ((signed short)((i -(unsigned long)y *
                           (unsigned long)y) >> 16L)) >> 1;
    if (sft & 1) {
        sft >>= 1;
        y = (unsigned short)((0x8000L +
                              (unsigned long)(y >> sft) * 46341L) >> 16L);
    }else {
        sft >>= 1;
        y = y >> sft;
    }
    return y;
}
