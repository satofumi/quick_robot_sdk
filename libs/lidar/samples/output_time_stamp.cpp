/*!
  \example output_time_stamp.cpp タイムスタンプの出力プログラム

  \author Satofumi KAMIMURA

  $Id$
*/

#include "Urg_driver.h"
#include "Connection_information.h"
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

    //urg.start_measurement(Urg_driver::Multiecho_intensity,
    urg.start_measurement(Urg_driver::Distance_intensity,
                          //urg.start_measurement(Urg_driver::Distance,
                          Urg_driver::Infinity_times);

    long pre_time_stamp = 0;
    //enum { Scan_times = 1200 };
    enum { Scan_times = 100 };
    for (int i = 0; i < Scan_times; ++i) {
        vector<long> data;
        vector<unsigned short> intensity;
        long time_stamp = 0;

        //if (!urg.get_multiecho_intensity(data, intensity, &time_stamp)) {
        if (!urg.get_distance_intensity(data, intensity, &time_stamp)) {
            //if (!urg.get_distance(data, &time_stamp)) {
            cout << "Urg_driver::get_distance_intensity(): " << urg.what() << endl;
            return 1;
        }

        // cout << time_stamp << endl;
        if (pre_time_stamp > 0) {
            long diff = time_stamp - pre_time_stamp;
            cout << diff << ", " << time_stamp << endl;
        }
        pre_time_stamp = time_stamp;
    }

    return 0;
}
