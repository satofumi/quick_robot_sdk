/*!
  \example direct_path_control.c 車輪速の制御による経路追従

  \author Satofumi KAMIMURA

  $Id$
*/

#include "Run_driver.h"
#include "Urg_driver.h"
#include "delay.h"
#include <iostream>

using namespace qrk;
using namespace std;


namespace
{
    typedef struct
    {
        int x;
        int y;
    } path_t;


    const path_t path_[] = {
        { 1922, 1211 },
	{ 1674, 1387 },
	{ 1506, 1149 },
	{ 1502, 1128 },
	{ 1149, 625 },
	{ 879, 784 },
	{ 879, 784 },
    };


    bool open_devices(Run_driver& run, Urg_driver& urg)
    {
        if (!run.open("/dev/ttyUSB0")) {
            cout << "Run_driver::open(): " << run.what() << endl;
            return false;
        }

#if 0
        if (!urg.open("/dev/ttyACM0")) {
            cout << "Urg_driver::open(): " << urg.what() << endl;
            return false;
        }
#endif

        return true;
    }


    void run_path(Run_driver& run, Urg_driver& urg)
    {
#if 0
        size_t path_size = sizeof(path_) / sizeof(path_[0]);
        for (size_t path_index = 0; path_index < path_size; ++path_size) {

            Position<long> target_line;
            while (true) {
                // 目標線を越えるまで直進する
                // !!! 位置を取得し、目標直線とのずれを計算し、

                // 障害物があったら回避ルーチンに入る
                // !!!

                // ロボットが通過できる方向にしばらく移動する
                // !!!
            }
        }
#endif

        enum { Velocity = 200, };
        run.set_wheel_velocity(0, -Velocity);
        run.set_wheel_velocity(1, +Velocity);

        while (true) {
            delay(100);
        }
    }
}


int main(void)
{
    Run_driver run;
    Urg_driver urg;

    // 接続
    if (!open_devices(run, urg)) {
        return 1;
    }

    run_path(run, urg);

    return 0;
}
