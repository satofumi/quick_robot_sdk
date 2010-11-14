/*!
  \example run_wired_controller.cpp 有線でのロボット操作

  \author Satofumi KAMIMURA

  $Id: run_wired_controller.cpp 1926 2010-09-26 23:06:51Z satofumi $
*/

#include "Usb_joystick.h"
#include "Run_driver.h"
#include "run_joystick_control.h"
#include <SDL.h>
#include <iostream>

using namespace qrk;
using namespace std;


namespace
{
    bool open_devices(Run_driver& robot_moving, Usb_joystick& joystick)
    {
        // 移動ロボットと接続
        if (!robot_moving.open("/dev/ttyUSB0")) {
            cout << "Run_driver::open(): " << robot_moving.what() << endl;
            return false;
        }

        // Joystick と接続
        if (!joystick.open()) {
            cout << "Usb_joystick::open(): " << joystick.what() << endl;
            return false;
        }

        return true;
    }


    void print_robot_position(Run_driver& robot_moving)
    {
        Position<long> position = robot_moving.position();

        cout << position.x << " " << position.y << " " << position.to_deg()
             << endl;
    }
}


int main(void)
{
    Run_driver robot_moving;
    Usb_joystick joystick;

    // デバイスとの接続
    if (!open_devices(robot_moving, joystick)) {
        return 1;
    }

    // ジョイスティックによる操作
    while (control_by_joystick(robot_moving, joystick)) {
        // 現在位置を出力
        print_robot_position(robot_moving);

        SDL_Delay(100);
    }

    return 0;
}
