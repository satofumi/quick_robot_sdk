/*!
  \example usb_joysticck_view.cpp USB ジョイスティックの入力表示

  \author Satofumi KAMIMURA

  $Id: usb_joystick_view.cpp 1907 2010-09-13 21:58:51Z satofumi $
*/

#include "Usb_joystick.h"
#include <SDL.h>
#include <iostream>

using namespace qrk;
using namespace std;


int main(void)
{
    Usb_joystick joystick;

    if (!joystick.open()) {
        cout << joystick.what() << endl;
        return 1;
    }

    size_t number_of_axes = joystick.number_of_axes();
    size_t number_of_buttons = joystick.number_of_buttons();

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            joystick.set_event(&event);
            if (event.type == SDL_QUIT) {
                return 0;
            }
        }

        for (size_t i = 0; i < number_of_axes; ++i) {
            int value = joystick.axis_value(i);
            cout << value << ", ";
        }
        cout << " ";

        for (size_t i = 0; i < number_of_buttons; ++i) {
            bool is_pressed = joystick.is_button_pressed(i);
            cout << ((is_pressed) ? '*' : '_') << " ";
        }
        cout << endl;

        enum { Wait_msec = 100 };
        SDL_Delay(Wait_msec);
    }
}
