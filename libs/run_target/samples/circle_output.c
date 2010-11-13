/*!
  \file
  \example circle_output.c 用のデータ出力プログラム

  \author Satofumi KAMIMURA

  $Id$
*/

#include "imask.h"
#include "clock_initialize.h"
#include "interrupt_priority.h"
#include "sci_read_write.h"
#include "sci_utilities.h"
#include "isin_icos.h"


static void output(int x, int y)
{
    sci_putint(x);
    sci_puts(",");
    sci_putint(y);
    sci_puts("\r\n");
}


int main(void)
{
    enum { RADIUS = 1000 };
    int i;

    // 初期化
    imask_initialize();
    clock_initialize();
    sci_initialize(INTERRUPT_PRIORITY_COMMUNICATION, 38400);
    set_imask_exr(0);

    // isin(), icos() を使って円の x, y 座標を計算する
    for (i = 0; i < 0xffff; i += 0x10) {
        long x = (RADIUS * icos(i)) >> ISINCOS_SHIFT_WIDTH;
        long y = (RADIUS * isin(i)) >> ISINCOS_SHIFT_WIDTH;
        output(x, y);
    }

    // 停止
    while (1) {
        ;
    }
}
