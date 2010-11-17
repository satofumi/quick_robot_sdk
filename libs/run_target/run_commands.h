#ifndef QRK_RUN_COMMANDS_H
#define QRK_RUN_COMMANDS_H

/*!
  \file
  \brief 走行コマンドの処理

  \author Satofumi KAMIMURA

  $Id: run_commands.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "run_t.h"


//! Odometry Position
extern void handle_OP_command(const run_t *run);


// !!!


//! Turn to Direction
extern void handle_TD_command(run_t *run, unsigned short target_direction);


//! StArt
extern void handle_SA_command(run_t *run);


//! STop
extern void handle_ST_command(run_t *run);


//! Set Parameter
extern void handle_SP_command(run_t *run, const char *line_buffer);


//! Wheel Velocity
extern void handle_WV_command(run_t *run, const char *line_buffer);

#endif /* !QRK_RUN_COMMANDS_H */
