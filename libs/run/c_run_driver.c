/*!
  \file
  \brief 走行制御

  \author Satofumi KAMIMURA

  $Id: c_run_driver.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "c_run_driver.h"
#include <stdio.h>


enum {
    BAUDRATE = 38400,
    DEFAULT_TIMEOUT = 1000,

    FALSE = 0,
    TRUE = 1,
};


static void initialize_run_driver_t(run_driver_t *run)
{
    sprintf(run->error_message, "no error.");
    run->is_opened = FALSE;
    run->timeout = DEFAULT_TIMEOUT;
}


int run_driver_open(run_driver_t *run, const char *device)
{
    int ret;

    initialize_run_driver_t(run);

    ret = connection_open(&run->connection, URG_SERIAL, device, BAUDRATE);
    if (ret < 0) {
        // !!! エラーメッセージの更新
        (void)run->error_message;

    } else {
        run->is_opened = TRUE;
    }

    return run_driver_is_open(run);
}


int run_driver_is_open(run_driver_t *run)
{
    return (run->is_opened == TRUE) ? 0 : -1;
}


void run_driver_close(run_driver_t *run)
{
    connection_close(&run->connection);
}


const char *run_driver_what(const run_driver_t *run)
{
    return run->error_message;
}


void run_stop_module(void)
{
    // !!!
}


void run_resume_module(void)
{
    // !!!
}


int run_driver_set_wheel_velocity(run_driver_t *run,
                                  int wheel_id, short mm_per_sec)
{
    int n;

    // !!! wheel_id と mm_per_sec の範囲判定を行うべき

    if (run_driver_is_open(run) != 0) {
        // !!! エラーメッセージの更新
        return -1;
    }

    // コマンドを送信
    enum {
        BUFFER_SIZE = 9,
        SEND_SIZE = 8,
        RECEIVE_SIZE = 4,
    };
    char buffer[BUFFER_SIZE] = "WVivvvv\n";
    snprintf(buffer, BUFFER_SIZE, "WV%d%04x\n", wheel_id, (unsigned short)mm_per_sec);

    buffer[SEND_SIZE - 1] = '\n';

    n = connection_write(&run->connection, buffer, SEND_SIZE);
    if (n != BUFFER_SIZE) {
        // !!! エラーメッセージの更新
        return -1;
    }

    // 応答を受信
    n = connection_read(&run->connection, buffer, RECEIVE_SIZE, run->timeout);
    if (n != RECEIVE_SIZE) {
        // !!! エラーメッセージの更新
        return -1;
    }

    return 0;
}
