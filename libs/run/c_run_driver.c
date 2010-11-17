/*!
  \file
  \brief 走行制御

  \author Satofumi KAMIMURA

  $Id: c_run_driver.c 1927 2010-09-26 23:09:26Z satofumi $

  \todo 数値をマクロにする。
*/

#include "c_run_driver.h"
#include "htoi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined FALSE
#define FALSE 0
#endif

#if !defined TRUE
#define TRUE 1
#endif


enum {
    BAUDRATE = 38400,
    DEFAULT_TIMEOUT = 1000,
};


static void initialize_run_driver_t(run_driver_t *run)
{
    sprintf(run->error_message, "no error.");
    run->is_opened = FALSE;
    run->timeout = DEFAULT_TIMEOUT;
}


static int handle_no_args_command(const char *command, run_driver_t *run)
{
    enum {
        READ_SIZE = 4,
        BUFFER_SIZE = READ_SIZE + 1,
    };
    char buffer[BUFFER_SIZE];
    int send_size = strlen(command);
    int n;

    // コマンドを送信
    n = connection_write(&run->connection, command, send_size);
    if (n != send_size) {
        // !!! エラーメッセージの更新
        return -1;
    }

    n = connection_read(&run->connection, buffer, READ_SIZE, run->timeout);
    if (n != READ_SIZE) {
        // !!! エラーメッセージの更新
        return -1;
    }

    if (buffer[2] != '0') {
        return -1;
    }

    return 0;
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


int run_position(run_driver_t *run,
                 long *x_mm, long *y_mm, unsigned short *direction)
{
    enum {
        BUFFER_SIZE = 26,
        SEND_SIZE = 3,
        READ_SIZE = 25,
        DATA_FIRST = 4,
    };
    char buffer[BUFFER_SIZE] = "OP0\nxxxxxxxxyyyyyyyydddd\n";
    int n;

    if (run_driver_is_open(run) != 0) {
        // !!! エラーメッセージの更新
        return -1;
    }

    // コマンドを送信
    n = connection_write(&run->connection, "OP\n", SEND_SIZE);
    if (n != SEND_SIZE) {
        // !!! エラーメッセージの更新
        return -1;
    }

    n = connection_read(&run->connection, buffer, READ_SIZE, run->timeout);
    if (n != READ_SIZE) {
        // !!! エラーメッセージの更新
        return -1;
    }

    // 受信結果をデコード
    char decode_buffer[9];
    memcpy(decode_buffer, &buffer[DATA_FIRST], 8);
    decode_buffer[8] = '\0';
    *x_mm = htoi(decode_buffer, 8);

    memcpy(decode_buffer, &buffer[DATA_FIRST + 8], 8);
    *y_mm = htoi(decode_buffer, 8);

    memcpy(decode_buffer, &buffer[DATA_FIRST + 8 + 8], 4);
    decode_buffer[4] = '\0';
    *direction = strtol(decode_buffer, NULL, 16);

    return 0;
}


int run_set_path_line(long x_mm, long y_mm, unsigned short direction,
                      long stop_length)
{
    (void)x_mm;
    (void)y_mm;
    (void)direction;
    (void)stop_length;
    // !!!

    return -1;
}


int run_set_stop_direction(run_driver_t *run, unsigned short direction)
{
    enum {
        SEND_SIZE = 7,
        READ_SIZE = 4,
        BUFFER_SIZE = READ_SIZE + 1,
    };
    char command[] = "TDxxxx\n";
    char buffer[BUFFER_SIZE];
    int n;

    snprintf(command, strlen(command) + 1, "TD%04x\n", direction);

    n = connection_write(&run->connection, command, SEND_SIZE);
    if (n != SEND_SIZE) {
        // !!!
        return -1;
    }

    n = connection_read(&run->connection, buffer, READ_SIZE, run->timeout);
    if (n != READ_SIZE) {
        // !!!
        return -1;
    }

    return 0;
}


int run_start(run_driver_t *run)
{
    const char command[] = "SA\n";
    return handle_no_args_command(command, run);
}


int run_stop(run_driver_t *run)
{
    const char command[] = "ST\n";
    return handle_no_args_command(command, run);
}


void run_stop_module(void)
{
    // !!!
}


void run_resume_module(void)
{
    // !!!
}


int run_set_wheel_velocity(run_driver_t *run, int wheel_id, short mm_per_sec)
{
    enum {
        SEND_SIZE = 8,
        BUFFER_SIZE = SEND_SIZE + 1,
        READ_SIZE = 4,
    };
    char buffer[BUFFER_SIZE] = "WVivvvv\n";
    int n;

    // !!! wheel_id と mm_per_sec の範囲判定を行うべき

    if (run_driver_is_open(run) != 0) {
        // !!! エラーメッセージの更新
        return -1;
    }

    // コマンドを送信
    snprintf(buffer, BUFFER_SIZE, "WV%d%04x\n", wheel_id,
             (unsigned short)mm_per_sec);

    n = connection_write(&run->connection, buffer, SEND_SIZE);
    if (n != SEND_SIZE) {
        // !!! エラーメッセージの更新
        return -1;
    }

    // 応答を受信
    n = connection_read(&run->connection, buffer, READ_SIZE, run->timeout);
    if (n != READ_SIZE) {
        // !!! エラーメッセージの更新
        return -1;
    }

    return 0;
}
