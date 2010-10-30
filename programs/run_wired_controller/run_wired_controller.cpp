/*!
  \example run_wired_controller.cpp 有線でのロボット操作

  \author Satofumi KAMIMURA

  $Id: run_wired_controller.cpp 1926 2010-09-26 23:06:51Z satofumi $

  \page run_wired_controller_cpp_page 操作方法

  - 前進について
    - L1, L2 ボタンのどちらかを押すと前進する
    - L1, L2 の両方を押すと、少し遅めの速度で前進する
    - L1, L2 の両方とも押されていないときは、ロボットは停止する

  - 旋回について
    - 十字キーの左を押すと左に旋回する
    - 十字キーの右を押すと右に旋回する

  - プログラムの終了について
    - R1, R2 を全部押すと、プログラムは終了する
*/

#include "Usb_joystick.h"
#include "Run_driver.h"
#include <SDL.h>
#include <iostream>

using namespace qrk;
using namespace std;


namespace
{
    enum Velocity {
        Normal_velocity = 500,  // [mm/sec]
        Slow_velocity = 100,    // [mm/sec]
        Rotate_velocity = 250,   // [mm/sec]
    };

    enum Buttons {
        L1_Button = 6,
        L2_Button = 7,
        R1_Button = 8,
        R2_Button = 9,
    };

    enum Axis {
        X_Axis = 0,
    };


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


    long create_straight_velocity(bool is_L1_pressed, bool is_L2_pressed)
    {
        if (is_L1_pressed && is_L2_pressed) {
            // 微速前進
            return Slow_velocity;

        } else if (is_L1_pressed || is_L2_pressed) {
            // 前進
            return Normal_velocity;
        }
        return 0;
    }


    long create_rotate_velocity(int x_axis_value)
    {
        enum { Threahold_value = 16384 };
        if (x_axis_value < -Threahold_value) {
            return -Rotate_velocity;

        } else if (x_axis_value > +Threahold_value) {
            return +Rotate_velocity;
        }
        return 0;
    }


    void set_robot_velocity(Run_driver& robot_moving,
                            long straight_velocity, long rotate_velocity)
    {
        long left_wheel_velocity = straight_velocity + (rotate_velocity / 2);
        long right_wheel_velocity = straight_velocity - (rotate_velocity / 2);

        robot_moving.set_wheel_velocity(0, left_wheel_velocity);
        robot_moving.set_wheel_velocity(1, -right_wheel_velocity);
    }


    void control_by_joystick(Run_driver& robot_moving, Usb_joystick& joystick)
    {
        bool quit = false;
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                joystick.set_event(&event);
                if (event.type == SDL_QUIT) {
                    return;
                }
            }

            // 操作情報の取得
            bool is_L1_pressed = joystick.is_button_pressed(L1_Button);
            bool is_L2_pressed = joystick.is_button_pressed(L2_Button);
            bool is_R1_pressed = joystick.is_button_pressed(R1_Button);
            bool is_R2_pressed = joystick.is_button_pressed(R2_Button);
            int x_axis_value = joystick.axis_value(X_Axis);

            if (is_R1_pressed && is_R2_pressed) {
                // 走行終了。戻る
                quit = true;
            }

            // 並進速度、回転速度の計算
            long straight_velocity =
                create_straight_velocity(is_L1_pressed, is_L2_pressed);
            long rotate_velocity = create_rotate_velocity(x_axis_value);

            // 各輪の速度を計算して指示
            set_robot_velocity(robot_moving,
                               straight_velocity, rotate_velocity);

            SDL_Delay(100);
        }
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
    control_by_joystick(robot_moving, joystick);

    return 0;
}
