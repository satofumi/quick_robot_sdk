/*!
  \file
  \brief ジョイスティックによる走行コントローラの制御

  \author satofumi KAMIMURA

  $Id$
*/

#include "run_joystick_control.h"
#include "Run_driver.h"
#include "Usb_joystick.h"
#include <SDL.h>

using namespace qrk;


namespace
{
    enum Velocity {
        Normal_velocity = 300,  // [mm/sec]
        Slow_velocity = 100,    // [mm/sec]
        Rotate_velocity = 300,  // [mm/sec]
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
            return +Rotate_velocity;

        } else if (x_axis_value > +Threahold_value) {
            return -Rotate_velocity;
        }
        return 0;
    }


    void set_robot_velocity(Run_driver& robot_moving,
                            long straight_velocity, long rotate_velocity)
    {
        long left_wheel_velocity = straight_velocity + (rotate_velocity / 2);
        long right_wheel_velocity = straight_velocity - (rotate_velocity / 2);

        robot_moving.set_wheel_velocity(0, -left_wheel_velocity);
        robot_moving.set_wheel_velocity(1, +right_wheel_velocity);
    }
}


bool control_by_joystick(Run_driver& robot_moving, Usb_joystick& joystick)
{
    bool is_normal = true;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        joystick.set_event(&event);
        if (event.type == SDL_QUIT) {
            is_normal = false;
            break;
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
        is_normal = false;
    }

    // 並進速度、回転速度の計算
    long straight_velocity =
        create_straight_velocity(is_L1_pressed, is_L2_pressed);
    long rotate_velocity = create_rotate_velocity(x_axis_value);

    // 各輪の速度を計算して指示
    set_robot_velocity(robot_moving,
                       straight_velocity, rotate_velocity);

    return is_normal;
}
