/*!
  \file
  \brief SCI 通信 (割り込み版)

  \author Satofumi KAMIMURA

  $Id: sci_interrupt_read_write.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "sci_read_write.h"
#include "imask.h"
#include "cpu_clock.h"
#include "ring_buffer.h"
#include <7125S.H>


enum {
    BUFFER_SIZE_SHIFT = 8,
    BUFFER_SIZE = 1 << BUFFER_SIZE_SHIFT,
};


static unsigned char interrupt_priority_ = 0;
static ring_buffer_t read_ring_;
static ring_buffer_t write_ring_;
static char read_buffer_[BUFFER_SIZE];
static char write_buffer_[BUFFER_SIZE];


void sci_initialize(int priority, long baudrate)
{
    interrupt_priority_ = priority;

    // スタンバイ解除
    STB.CR3.BYTE = 0xef;

    // 通信と割り込みを禁止し、内部クロックで動作させる
    SCI1.SCSCR.BYTE = 0x00;

    // 8bit, no parity, 1 stop bit
    SCI1.SCSMR.BYTE = 0x00;
    SCI1.SCSDCR.BYTE = 0xf2;

    // set baudrate
    SCI1.SCBRR = (int)((P_MHz / 1024.0) * 2 * 1000000 / 64 / baudrate) - 1;

    // 1 bit のウェイト
    // !!! 1 bit のウェイト数を適切に設定すること
    enum { OneBitWait = 1000 };
    volatile int i;
    for (i = 0; i < OneBitWait; ++i) {
        ;
    }

    // TXD1(PA4)
    PFC.PACRL2.WORD &= ~0x0007;
    PFC.PACRL2.WORD |= 0x0001;

    // RXD1(PA3)
    PFC.PACRL1.WORD &= ~0x7000;
    PFC.PACRL1.WORD |= 0x1000;

    // リングバッファの初期化
    ring_initialize(&read_ring_, read_buffer_, BUFFER_SIZE_SHIFT);
    ring_initialize(&write_ring_, write_buffer_, BUFFER_SIZE_SHIFT);

    // 割り込みの初期化
    //INTC.IPRL.BIT._SCI1 = priority;
    INTC.IPRL.WORD &= ~0x0f00;
    INTC.IPRL.WORD |= priority << 8;
    SCI1.SCSCR.BYTE |= 0x40;
    // !!! 以下の割り込みを許可する必要があるかは、要検討
    // !!! SCSCR の TIE, TEIE, MPIE で割り込みを許可

    // 通信を許可
    SCI1.SCSCR.BYTE |= 0x30;
}


int sci_write(const char *data, int size)
{
    unsigned char current_level = get_imask_exr();
    int n;

    // 送信データの格納
    set_imask_exr(interrupt_priority_);
    n = ring_write(&write_ring_, data, size);

    if (n > 0) {
        // 送信割り込みの許可
        SCI1.SCSCR.BYTE |= 0x80;
    }
    set_imask_exr(current_level);

    return n;
}


int sci_read(char *data, int max_data_size)
{
    int current_level = get_imask_exr();
    int read_size;

    set_imask_exr(interrupt_priority_);
    read_size = ring_read(&read_ring_, data, max_data_size);
    set_imask_exr(current_level);

    return read_size;
}


#pragma interrupt
void eri1(void)
{
    SCI1.SCSSR.BYTE &= ~0x38;
}


#pragma interrupt
void rxi1(void)
{
    char ch = SCI1.SCRDR;
    ring_write(&read_ring_, &ch, 1);
    SCI1.SCSSR.BYTE &= ~0x40;
}


#pragma interrupt
void txi1(void)
{
    char ch;

    if (ring_read(&write_ring_, &ch, 1) <= 0) {
        SCI1.SCSCR.BYTE &= ~0x80;     // 送信終了。以後の送信割り込みを禁止
    } else {
        SCI1.SCTDR = ch;
        SCI1.SCSSR.BYTE &= ~0x80;
    }
}


#pragma interrupt
void tei1(void)
{
}
