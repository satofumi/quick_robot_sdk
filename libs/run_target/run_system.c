/*!
  \file
  \brief 走行制御のシステム管理

  \author Satofumi KAMIMURA

  $Id: run_system.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "run_system.h"


void run_system_initialize(run_system_t *run_system)
{
    run_system->msec = 0;
    run_system->sec = 0;
    run_system->mode = NORMAL_CONTROL;
}
