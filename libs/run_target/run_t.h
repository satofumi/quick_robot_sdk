#ifndef QRK_RUN_T_H
#define QRK_RUN_T_H

/*!
  \file
  \brief 走行状態の管理

  \author Satofumi KAMIMURA

  $Id: run_t.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "controller_config.h"
#include "run_system_t.h"
#include "odometry_t.h"
#include "path_t.h"
#include "wheel_t.h"


//! 走行状態の管理
typedef struct {
    run_system_t run_system;
    odometry_t odometry;
    path_t path;
    wheel_t wheel[NUMBER_OF_WHEELS];
} run_t;

#endif /* !QRK_RUN_T_H */
