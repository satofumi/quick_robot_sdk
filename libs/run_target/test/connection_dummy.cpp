/*!
  \example connection_dummy.cpp connection.c のダミー実装

  \author Satofumi KAMIMURA

  $Id: connection_dummy.cpp 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "connection.h"
#include <deque>
#include <string>
#include <cstring>

using namespace std;


namespace
{
    deque<char> pc_sent_command_;
    deque<char> sensor_sent_data_;
    string sensor_sent_buffer_;
}


void send_command(const char *command)
{
    size_t n = strlen(command);
    for (size_t i = 0; i < n; ++i) {
        pc_sent_command_.push_back(command[i]);
    }
}


std::string receive_response_line(void)
{
    // 改行を送信したら、そこまでを１行の終端として処理する
    size_t n = sensor_sent_data_.size();
    string line;
    for (size_t i = 0; i < n; ++i) {
        char front_ch = sensor_sent_data_.front();
        line.push_back(front_ch);
        sensor_sent_data_.pop_front();

        if (front_ch == '\n') {
            break;
        }
    }
    return line;
}


void connection_initialize(void)
{
    pc_sent_command_.clear();
    sensor_sent_data_.clear();
}


int connection_write(const char *data, int data_size)
{
    for (int i = 0; i < data_size; ++i) {
        sensor_sent_buffer_.push_back(data[i]);
    }

    size_t n = sensor_sent_buffer_.size();
    for (size_t i = 0; i < n; ++i) {
        sensor_sent_data_.push_back(sensor_sent_buffer_[i]);
    }
    sensor_sent_buffer_.clear();

    return data_size;
}


void connection_write_flush(void)
{
    size_t n = sensor_sent_buffer_.size();
    for (size_t i = 0; i < n; ++i) {
        sensor_sent_data_.push_back(sensor_sent_buffer_[i]);
    }
    sensor_sent_buffer_.clear();
}


int connection_read(char *data, int max_data_size)
{
    size_t read_size =
        min(static_cast<size_t>(max_data_size), pc_sent_command_.size());

    for (size_t i = 0; i < read_size; ++i) {
        char ch = pc_sent_command_.front();
        data[i] = ch;

        pc_sent_command_.pop_front();
    }

    return read_size;
}
