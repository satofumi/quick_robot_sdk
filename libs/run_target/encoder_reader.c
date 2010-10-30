/*!
  \file
  \brief エンコーダ制御

  \author Satofumi KAMIMURA

  $Id: encoder_reader.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "encoder_reader.h"
#include "mtu2_initialize.h"
#include <7125S.H>


static void encoder_initialize_device(int device_id)
{
    if (device_id == 0) {
        MTU2.TSTR.BYTE &= ~0x02;
        MTU21.TMDR.BYTE = 0x04;

        // TCOKB(PA7), TCLKA(PA6)
        PFC.PACRL2.WORD &= ~0xff00;
        PFC.PACRL2.WORD |= 0x1100;

        MTU2.TSTR.BYTE |= 0x02;

    } else if (device_id == 1) {
        MTU2.TSTR.BYTE &= ~0x04;
        MTU22.TMDR.BYTE = 0x04;

        // TCLKD(PA9), TCLKC(PA8)
        PFC.PACRL3.WORD &= ~0x00ff;
        PFC.PACRL3.WORD |= 0x0011;

        MTU2.TSTR.BYTE |= 0x04;
    }
}


static short encoder_count(int device_id)
{
    if (device_id == 0) {
        return MTU21.TCNT;

    } else if (device_id == 1) {
        return MTU22.TCNT;

    } else {
        return -1;
    }
}


void encoder_initialize(encoder_t *encoder, int device_id)
{
    mtu2_initialize();
    encoder_initialize_device(device_id);

    encoder->device_id = device_id;
    encoder->previous_count = encoder_count(device_id);
    encoder->difference = 0;
}


void encoder_update(encoder_t *encoder)
{
    short current_count = encoder_count(encoder->device_id);

    encoder->difference = current_count - encoder->previous_count;
    encoder->previous_count = current_count;
}


short encoder_difference(encoder_t *encoder)
{
    return encoder->difference;
}
