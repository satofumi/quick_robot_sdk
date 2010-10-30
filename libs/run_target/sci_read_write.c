/*!
  \file
  \brief SCI 通信

  \author Satofumi KAMIMURA

  $Id: sci_read_write.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "sci_read_write.h"
#include "cpu_clock.h"
#include <7125S.H>


void sci_initialize(int priority, long baudrate)
{
    (void)priority;

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

    // !!! SCSCR の RIE, TIE, TEIE, MPIE で割り込みを許可

    // 通信を許可
    // !!! 割り込みを使ったバージョンでは、割り込みを許可するようにする
    SCI1.SCSCR.BYTE |= 0x30;
}


int sci_write(const char *data, int size)
{
    int i;

    for (i = 0; i < size; ++i) {
        // SCSSR の TDRE を確認しながらデータを格納、送信する
        while (! (SCI1.SCSSR.BYTE & 0x80)) {
            ;
        }
        SCI1.SCTDR = data[i];
        SCI1.SCSSR.BYTE &= ~0x80;
    }

    return size;
}


int sci_read(char *data, int max_data_size)
{
    int i;
    for (i = 0; i < max_data_size; ++i) {
        while (1) {
            // SCSSR の ORER, PER, FER を読み出す
            if (SCI1.SCSSR.BYTE & 0x38) {
                // PER, FER, ORER のエラーフラグをクリア
                SCI1.SCSSR.BYTE &= ~0x38;

            } else if (SCI1.SCSSR.BYTE & 0x40) {
                // 受信データの読み出し
                data[i] = SCI1.SCRDR;
                SCI1.SCSSR.BYTE &= ~0x40;

                // 次の場所に受信データを格納する
                break;
            }
        }
    }

    return max_data_size;
}
