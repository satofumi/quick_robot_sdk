/*!
  \file
  \brief 走行コントローラ

  \author Satofumi KAMIMURA

  $Id: run_drive.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "setup_state.h"
#include "control_state.h"


// スタックに積まないために static 宣言する
static run_t run_;


int main(void)
{
    setup_state(&run_);
    control_state(&run_);

    return 0;
}
