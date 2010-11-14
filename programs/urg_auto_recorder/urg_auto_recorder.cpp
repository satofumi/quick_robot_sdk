/*!
  \example urg_auto_recorder.cpp URG データの記録

  \author Satofumi KAMIMURA

  $Id: urg_auto_recorder.cpp 1926 2010-09-26 23:06:51Z satofumi $
*/

#include "Urg_driver.h"
#include "record_utilities.h"
#include "urg_record_utilities.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace qrk;
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


    string create_save_file_name(const string& save_directory)
    {
        // ファイル名の作成
        enum { Buffer_size = 80 };
        char buffer[Buffer_size];
        snprintf(buffer, Buffer_size, "data_%06d.csv", file_id_);
        ++file_id_;

        return save_directory + "/" + buffer;
    }


    void record_urg_data(Urg_driver& urg, int record_interval,
                         const string& save_directory)
    {
        // 計測の開始
        urg.start_measurement(Urg_driver::Distance,
                              Urg_driver::Infinity_times, record_interval);

        vector<long> data;
        while (true) {
            // URG からのデータ取得
            urg.get_distance(data);
            if (data.empty()) {
                break;
            }

            // ファイルに CSV 形式で保存
            string file_name = create_save_file_name(save_directory);
            if (!save_csv_data(urg, data, file_name)) {
                // !!! エラーメッセージを出力すべき
                break;
            }
            fprintf(stderr, ".");
        }
        cout << "Urg_drver::get_distance(): " << urg.what() << endl;
    }
}


int main(int argc, char *argv[])
{
    // URG センサと接続
    enum { URG_DEVICE_BAUDRATE = 115200 };
    const char *device = "/dev/ttyACM0";

    Urg_driver urg;
    if (!urg.open(device)) {
        cout << "Urg_driver::open(): " << device
             << ": " << urg.what() << endl;
        return 1;
    }

    // 記録するデータ間隔の読み出し
    int record_interval = parse_args(argc, argv);

    // 記録するディレクトリの作成
    string save_directory = create_record_directory();

    // 記録
    record_urg_data(urg, record_interval, save_directory);

    return 0;
}
