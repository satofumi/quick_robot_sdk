/*!
  \example run_urg_wired_recorder.cpp 走行経路と URG データを記録するプログラム

  \author Satofumi KAMIMURA

  $Id$
*/

#include "Run_driver.h"
#include "Urg_driver.h"
#include "Usb_joystick.h"
#include "run_joystick_control.h"
#include "record_utilities.h"
#include "urg_record_utilities.h"
#include <iostream>
#include <fstream>

using namespace qrk;
using namespace std;


namespace
{
    int file_id_ = 0;


    bool open_devices(Run_driver& robot, Urg_driver& urg,
                      Usb_joystick& joystick)
    {
        // 移動ロボットと接続
        if (!robot.open("/dev/ttyUSB0")) {
            cout << "Run_driver::open(): " << robot.what() << endl;
            return false;
        }

        // Joystick と接続
        if (!joystick.open()) {
            cout << "Usb_joystick::open(): " << joystick.what() << endl;
            return false;
        }

        // URG と接続
        if (!urg.open("/dev/ttyACM0")) {
            cout << "Urg_driver::open(): " << urg.what() << endl;
            return false;
        }

        return true;
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


    void save_urg_data(Urg_driver& urg, const string& save_directory)
    {
        vector<long> data;
        urg.get_distance(data);
        if (data.empty()) {
            return;
        }

        // ファイルに CSV 形式で保存
        string file_name = create_save_file_name(save_directory);
        if (!save_csv_data(urg, data, file_name)) {
            // !!! エラーメッセージを出力すべき
            return;
        }
    }


    void print_robot_position(Run_driver& robot, ofstream& fout)
    {
        Position<long> position = robot.position();

        fout << position.x << " "
             << position.y << " "
             << position.angle.to_rad() << endl;
    }
}


int main(void)
{
    Run_driver robot;
    Urg_driver urg;
    Usb_joystick joystick;

    // デバイスとの接続
    if (!open_devices(robot, urg, joystick)) {
        return 1;
    }

    // データ保存フォルダの作成
    string save_directory = create_record_directory();

    // 位置の記録用ファイルの作成
    ofstream position_fout((save_directory + "/position.txt").c_str());
    if (!position_fout.is_open()) {
        // !!! エラーメッセージを表示すべき
        return 1;
    }

    // URG のデータ送信開始
    urg.start_measurement();

    bool quit = false;
    while (!quit) {
        // URG データの記録
        save_urg_data(urg, save_directory);

        // ジョイスティックによる操作
        quit = control_by_joystick(robot, joystick);

        // 現在位置を出力
        print_robot_position(robot, position_fout);
    }

    //robot.stop();

    return 0;
}
