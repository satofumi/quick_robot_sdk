/*!
  \example evaluate_timestamp.cpp タイムスタンプの評価

  \author Satofumi KAMIMURA

  $Id$
*/

#include "Urg_driver.h"
#include "Connection_information.h"
#include "ticks.h"
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

    // タイムスタンプの同期
    urg.set_sensor_time_stamp(ticks());

    // 受信データを取りつつ、タイムスタンプ値を表示し続ける
    enum { Times = 100 * 60 * 5 };

    urg.start_measurement(Urg_driver::Distance, Times);
    for (int i = 0; i < Times; ++i) {
        long time_stamp;
        vector<long> data;
        urg.get_distance(data, &time_stamp);

        cout << ticks() << " " << time_stamp << endl;
    }
}
