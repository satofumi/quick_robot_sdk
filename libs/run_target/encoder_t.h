#ifndef QRK_ENCODER_T_H
#define QRK_ENCODER_T_H

/*!
  \file
  \brief エンコーダ管理

  \author Satofumi KAMIMURA

  $Id: encoder_t.h 1927 2010-09-26 23:09:26Z satofumi $
*/


//! エンコーダ管理
typedef struct
{
    int device_id;
    short previous_count;
    short difference;
} encoder_t;

#endif /* !QRK_ENCODER_T_H */
