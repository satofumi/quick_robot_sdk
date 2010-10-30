/*!
  \example timer_1sec.c タイマーのテスト

  \author Satofumi KAMIMURA

  $Id: timer_1sec.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "clock_initialize.h"
#include "imask.h"
#include "sci_read_write.h"
#include "timer_control.h"
#include "interrupt_priority.h"
#include "itoa.h"
#include "std_string.h"


static void timer_handler(void)
{
    static int msec_counter = 0;
    static int sec_counter = 0;

    if (++msec_counter >= 1000) {
        char number_text;

        msec_counter = 0;
        ++sec_counter;
        if (sec_counter >= 10) {
            return;
        }

        number_text = '0' + sec_counter;
        sci_write(&number_text, 1);
        sci_write("\r\n", 2);
    }
}


int main(void)
{
    imask_initialize();
    clock_initialize();
    sci_initialize(INTERRUPT_PRIORITY_COMMUNICATION, 38400);
    timer_initialize(INTERRUPT_PRIORITY_TIMER);
    set_imask_exr(0);

    timer_set_interval_function(timer_handler);
    timer_start();

    sci_write("0\r\n", 3);

    while (1) {
        ;
    }
}
