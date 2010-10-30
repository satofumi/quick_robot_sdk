/*!
  \example calculate_xy.c X-Y 座標系での位置を計算する

  センサ前方が X 軸の方向とみなした直行座標上で、距離データを位置を出力する。

  \author Satofumi KAMIMURA

  $Id: calculate_xy.cpp 1930 2010-09-30 03:26:52Z satofumi $
*/

#include "Urg_driver.h"
#include "Connection_information.h"
#include "math_utilities.h"
#include <iostream>

using namespace qrk;
using namespace std;


int main(int argc, char *argv[])
{
    Connection_information information(argc, argv);

    // 接続
    Urg_driver urg;
    if (!urg.open(information.device_or_ip_name(),
                  information.baudrate_or_port_number(),
                  information.connection_type())) {
        cout << "Urg_driver::open(): "
             << information.device_or_ip_name() << ": " << urg.what() << endl;
        return 1;
    }

    // データ取得
    if (!urg.start_measurement(Urg_driver::Distance, 1)) {
        cout << "Urg_driver::start_measurement(): " << urg.what() << endl;
        return 1;
    }

    vector<long> length_data;
    if (!urg.get_distance(length_data)) {
        cout << "Urg_driver::get_distance(): " << urg.what() << endl;
        return 1;
    }

    // 座標系の値を出力
    long min_distance = urg.min_distance();
    long max_distance = urg.max_distance();
    size_t n = length_data.size();
    for (size_t i = 0; i < n; ++i) {
        long distance = length_data[i];
        if ((distance < min_distance) || (distance > max_distance)) {
            continue;
        }

        double radian = urg.index2rad(i);
        long x = static_cast<long>(distance * cos(radian));
        long y = static_cast<long>(distance * sin(radian));

        cout << x << ", " << y << endl;
    }
    cout << endl;

#if defined(URG_MSC)
    getchar();
#endif
    return 0;
}
