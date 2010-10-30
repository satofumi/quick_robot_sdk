/*!
  \file
  \brief 緊急停止 IO の制御

  \author Satofumi KAMIMURA

  $Id: emergency_io_control.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "emergency_io_control.h"


typedef enum {
    IO_LOW,
    IO_HIGH,
} io_state_t;


static bool is_emergency_ = false;
static io_state_t previous_stop_io_state_ = IO_LOW;
static io_state_t previous_start_io_state_ = IO_LOW;


static io_state_t stop_io_state(void)
{
    // !!!
    return IO_HIGH;
}


static io_state_t start_io_state(void)
{
    // !!!
    return IO_HIGH;
}


void emergency_io_initialize(void)
{
    // IO 設定の初期化
    // !!!

    // 現在の信号を読み出す
    previous_stop_io_state_ = stop_io_state();
    previous_start_io_state_ = start_io_state();
}


bool emergency_io_is_emergency(void)
{
    io_state_t current_stop_io_state = stop_io_state();
    io_state_t current_start_io_state = start_io_state();

    if (current_stop_io_state == IO_LOW) {
        // 緊急停止ボタンが押されている場合は、停止させる
        is_emergency_ = true;

    } else if ((previous_start_io_state_ == IO_LOW) &&
               (current_start_io_state == IO_HIGH)) {
        // 再開ボタンの押下で、再開を許可する
        is_emergency_ = false;
    }

    previous_stop_io_state_ = current_stop_io_state;
    previous_start_io_state_ = current_start_io_state;

    return is_emergency_;
}


void emergency_io_force_set_emergency(void)
{
    is_emergency_ = true;
}
