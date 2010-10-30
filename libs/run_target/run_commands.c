/*!
  \file
  \brief 走行コマンドの処理

  \author Satofumi KAMIMURA

  $Id: run_commands.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "run_commands.h"
#include "htoi.h"
#include "wheel_velocity.h"
#include "connection.h"


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
