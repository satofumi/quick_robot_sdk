#ifndef QRK_RUN_SYSTEM_H
#define QRK_RUN_SYSTEM_H

/*!
  \file
  \brief 走行制御のシステム管理

  \author Satofumi KAMIMURA

  $Id: run_system.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "run_system_t.h"


extern void run_system_initialize(run_system_t *run_system);
extern void run_system_increment_timestamp(run_system_t *run_system);

#endif /* !QRK_RUN_SYSTEM_H */
