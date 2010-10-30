/*!
  \example sensor_parameter.c センサ情報の出力

  \author Satofumi KAMIMURA

  $Id: sensor_parameter.cpp 1937 2010-10-25 01:12:49Z satofumi $
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
        cout << "Urg_driver::open():"
             << information.device_or_ip_name() << ": " << urg.what() << endl;
        return 1;
    }

    // パラメータ情報の表示
    printf("Sensor product type: %s\n", urg.product_type());
    printf("Sensor firmware version: %s\n", urg.firmware_version());
    printf("Sensor serial ID: %s\n", urg.serial_id());
    printf("Sensor status: %s\n", urg.status());

    printf("step: [%d, %d]\n", urg.min_step(), urg.max_step());
    printf("distance: [%ld, %ld)\n", urg.min_distance(), urg.max_distance());

    printf("scan interval: %ld [usec]\n", urg.scan_usec());
    printf("sensor data size: %d\n", urg.max_data_size());

    urg.close();

#if defined(URG_MSC)
    getchar();
#endif
    return 0;
}
