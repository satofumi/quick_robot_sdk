/*!
  \example sci_write.c シリアル出力

  \author Satofumi KAMIMURA

  $Id: sci_write.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "clock_initialize.h"
#include "imask.h"
#include "sci_read_write.h"
#include "sci_utilities.h"
#include "interrupt_priority.h"


int main(void)
{
    const char message[] = "hello.\r\n";

    imask_initialize();
    clock_initialize();
    sci_initialize(INTERRUPT_PRIORITY_COMMUNICATION, 38400);
    set_imask_exr(0);

    sci_write(message, sizeof(message) - 1);
    sci_puts("start\r\n");

    while (1) {
        ;
    }
}
