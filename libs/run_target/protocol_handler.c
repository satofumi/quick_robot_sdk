/*!
  \file
  \brief 通信プロトコルの処理

  \author Satofumi KAMIMURA

  $Id: protocol_handler.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "protocol_handler.h"
#include "connection.h"
#include "connection_utilities.h"
#include "run_commands.h"
#include "std_string.h"


typedef enum {
    Unknown_Command,
    OP_Command,
    // !!!
    SA_Command,
    ST_Command,
    // !!!
    WV_Command,                 //!< 車輪速の制御
} command_type_t;


typedef struct
{
    command_type_t type;
    const char *tag;
    char tag_size;
    char packet_size;
} command_packet_t;


static command_packet_t command_packets_[] = {
    // !!!
    { OP_Command, "OP", 2, 2, },
    // !!!
    { SA_Command, "SA", 2, 2, },
    { ST_Command, "ST", 2, 2, },
    // !!!
    { WV_Command, "WV", 2, 7, },
};


void protocol_initialize(void)
{
    connection_initialize();

    // !!!
}


command_type_t parse_received_command(const char *line_buffer, int line_size)
{
    int packets_size = sizeof(command_packets_) / sizeof(command_packets_[0]);
    int i;

    for (i = 0; i < packets_size; ++i) {
        const command_packet_t *p = &command_packets_[i];
        if (line_size != p->packet_size) {
            continue;
        }

        if (strncmp(p->tag, line_buffer, p->tag_size)) {
            continue;
        }

        // コマンドのタグが一致
        return p->type;
    }
    return Unknown_Command;
}


void protocol_update(run_t *run)
{
    char line_buffer[CONNECTION_READLINE_BUFFER_SIZE];
    int line_size;
    command_type_t command_type;

    line_size =
        connection_readline(line_buffer, CONNECTION_READLINE_BUFFER_SIZE);
    command_type = parse_received_command(line_buffer, line_size);

    // コマンドのパース処理
    switch (command_type) {

    case OP_Command:
        handle_OP_command(run);
        break;

    case SA_Command:
        handle_SA_command(run);
        break;

    case ST_Command:
        handle_ST_command(run);
        break;

    case WV_Command:
        handle_WV_command(run, line_buffer);
        break;

    case Unknown_Command:
        // !!! エラー応答を返す
        break;
    }
}
