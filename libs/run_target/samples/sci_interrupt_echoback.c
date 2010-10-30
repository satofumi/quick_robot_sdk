/*!
  \example sci_echoback.c シリアル出力

  \author Satofumi KAMIMURA

  $Id: sci_interrupt_echoback.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "clock_initialize.h"
#include "imask.h"
#include "sci_interrupt_read_write.h"
#include "interrupt_priority.h"


int main(void)
{
    const char first_message[] = "echoback test.\r\n";

    imask_initialize();
    clock_initialize();
    sci_initialize(INTERRUPT_PRIORITY_COMMUNICATION, 38400);
    set_imask_exr(0);

    sci_write(first_message, sizeof(first_message) - 1);

    while (1) {
        char ch;
        int n;

        // 受信した内容を送信する
        n = sci_read(&ch, 1);
        if (n > 0) {
            sci_write(&ch, 1);
        }
    }
}
