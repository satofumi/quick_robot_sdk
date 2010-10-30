#ifndef QRK_RUN_COMMANDS_H
#define QRK_RUN_COMMANDS_H

/*!
  \file
  \brief 走行コマンドの処理

  \author Satofumi KAMIMURA

  $Id: run_commands.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "run_t.h"


extern void handle_WV_command(run_t *run, const char *line_buffer);
// !!!

#endif /* !QRK_RUN_COMMANDS_H */
