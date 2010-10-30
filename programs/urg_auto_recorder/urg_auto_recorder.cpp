/*!
  \example urg_auto_recorder.cpp URG データの記録

  \author Satofumi KAMIMURA

  $Id: urg_auto_recorder.cpp 1926 2010-09-26 23:06:51Z satofumi $
*/

extern "C" {
#include "urg_sensor.h"
#include "urg_utils.h"
}
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>


using namespace std;


namespace
{
    int file_id_ = 0;


    int parse_args(int argc, char *argv[])
    {
        if (argc >= 2) {
            return atoi(argv[1]);
        } else {
            return 0;
        }
    }


    string crate_record_directory()
    {
        enum { Buffer_size = 80 };
        char buffer[Buffer_size];
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        strftime(buffer, Buffer_size, "%F_%H_%M_%S", tm);

        mkdir(buffer, 0755);

        return buffer;
    }


    string create_save_file_name(const string& save_directory)
    {
        // ファイル名の作成
        enum { Buffer_size = 80 };
        char buffer[Buffer_size];
        snprintf(buffer, Buffer_size, "data_%06d.csv", file_id_);
        ++file_id_;

        return save_directory + "/" + buffer;
    }


    bool save_csv_data(const urg_t& urg,
                       long data[], int data_size, const string& file_name)
    {
        ofstream fout(file_name.c_str());//, ios::out);
        if (!fout.is_open()) {
            return false;
        }

        for (int i = 0; i < data_size; ++i) {
            fout << i << ","
                 << data[i] << ","
                 << urg_index2rad(&urg, i) << endl;
        }

        return true;
    }


    void record_urg_data(urg_t& urg, int record_interval,
                         const string& save_directory)
    {
        // 計測の開始
        urg_start_measurement(&urg, URG_DISTANCE,
                              URG_SCAN_INFINITY, record_interval);

        long* data = new long[urg_max_data_size(&urg)];
        while (true) {
            // URG からのデータ取得
            int data_size = urg_get_distance(&urg, data, NULL);
            if (data_size <= 0) {
                break;
            }

            // ファイルに CSV 形式で保存
            string file_name = create_save_file_name(save_directory);
            if (!save_csv_data(urg, data, data_size, file_name)) {
                fprintf(stderr, "b\n");
                break;
            }
            fprintf(stderr, ".");
        }
        cout << "urg_get_distance: " << urg_error(&urg) << endl;

        delete data;
    }
}


int main(int argc, char *argv[])
{
    // URG センサと接続
    enum { URG_DEVICE_BAUDRATE = 115200 };
    const char *device = "/dev/ttyACM0";

    urg_t urg;
    if (urg_open(&urg, URG_SERIAL, device, URG_DEVICE_BAUDRATE) < 0) {
        cout << "urg_open: " << device << ": " << urg_error(&urg) << endl;
        return 1;
    }

    // 記録するデータ間隔の読み出し
    int record_interval = parse_args(argc, argv);

    // 記録するディレクトリの作成
    string save_directory = crate_record_directory();

    // 記録
    record_urg_data(urg, record_interval, save_directory);

    return 0;
}
