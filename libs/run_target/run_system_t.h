#ifndef QRK_SYSTEM_T_H
#define QRK_SYSTEM_T_H

/*!
  \file
  \brief システム

  \author Satofumi KAMIMURA

  $Id: run_system_t.h 1927 2010-09-26 23:09:26Z satofumi $
*/


typedef enum {
    NORMAL_CONTROL,             //!< 通常動作
    DIRECT_WHEEL_CONTROL,       //!< 車輪速の直接制御
} control_mode_t;


typedef struct
{
    short msec;
    long sec;

    control_mode_t mode;
} run_system_t;

#endif /* !QRK_SYSTEM_T_H */
