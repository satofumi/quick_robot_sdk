/*!
  \file
  \brief 通信モジュールの補助関数

  \author Satofumi KAMIMURA

  $Id: connection_utilities.c 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "connection_utilities.h"
#include "connection.h"
#include "std_string.h"


int connection_readline(char *data, int max_data_size)
{
    static char line_buffer_[CONNECTION_READLINE_BUFFER_SIZE];
    static int line_buffer_filled_ = 0;
    char ch;
    int n;

    while (1) {
        n = connection_read(&ch, 1);
        if (n <= 0) {
            return -1;
        }

        if (ch == '\n') {
            if (line_buffer_filled_ <= 0) {
                line_buffer_filled_ = 0;
                return 0;
            } else {
                int ret_value = line_buffer_filled_;
                memcpy(data, line_buffer_, line_buffer_filled_);
                data[line_buffer_filled_] = '\0';
                line_buffer_filled_ = 0;
                return ret_value;
            }
        }

        // 格納
        line_buffer_[line_buffer_filled_++] = ch;

        // 最大サイズまでデータを格納したら戻る
        if (line_buffer_filled_ >= max_data_size) {
            int ret_value = line_buffer_filled_;
            memcpy(data, line_buffer_, line_buffer_filled_);
            line_buffer_filled_ = 0;
            return ret_value;
        }
    }
}
