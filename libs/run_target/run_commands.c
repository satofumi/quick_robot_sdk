/*!
  \file
  \brief 走行コマンドの処理

  \author Satofumi KAMIMURA

  $Id: run_commands.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "run_commands.h"
#include "htoi.h"
#include "itoh.h"
#include "wheel_velocity.h"
#include "connection.h"
#include "update_parameter_id.h"


void handle_OP_command(const run_t *run)
{
    enum {
        DATA_FIRST = 4,
    };
    char response[] = "OP0\nxxxxxxxxyyyyyyyydddd\n";
    char *p = &response[DATA_FIRST];
    const odometry_t *odometry = &run->odometry;
    int i;

    // 応答を返す
    for (i = 0; i < NUMBER_OF_AXIS; ++i) {
        long mm =
            1000 * ((1000 * odometry->km[i]) + odometry->m[i]) +
            odometry->mm[i];
        itoh(p, mm, 4);
        p += 8;
    }
    itoh(p, run->odometry.direction, 2);

    connection_write(response, 25);
}


void handle_SP_command(run_t *run, const char *line_buffer)
{
    (void)run;
    (void)line_buffer;
    // !!!

    // ID の読み出し
    // !!!

    // 設定の更新
    // !!!
}


void handle_WV_command(run_t *run, const char *line_buffer)
{
    int id;
    short velocity;
    char response[] = "WV0\n";

    // パラメータの読み出し
    id = htoi(&line_buffer[2], 1);
    velocity = htoi(&line_buffer[3], 4);

    // !!! パースに失敗したら、エラー応答を返すようにするべき

    if ((id == 0) || (id == 1)) {
        wheel_set_velocity(&run->wheel[id], velocity);
        run->run_system.mode = DIRECT_WHEEL_CONTROL;
    } else {
        // ID 範囲外のエラー
        response[2] = '2';
    }

    connection_write(response, 4);
}
