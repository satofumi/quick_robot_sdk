#ifndef QRK_JOYSTICK_H
#define QRK_JOYSTICK_H

/*!
  \file
  \brief ジョイスティック

  \author Satofumi KAMIMURA

  $Id: Joystick.h 1907 2010-09-13 21:58:51Z satofumi $
*/

#include <cstddef>


namespace qrk
{
    //! ジョイスティック用インターフェース
    class Joystick
    {
    public:
        enum Id {
            Auto_selected = -1,
        };


        virtual ~Joystick(void)
        {
        }


        virtual void set_event(void* event)
        {
            static_cast<void>(event);
        }


        virtual size_t number_of_joysticks(void) = 0;


        virtual const char* what(void) const = 0;


        virtual bool open(int device_index = Auto_selected) = 0;
        virtual void close(void) = 0;

        virtual size_t number_of_axes(void) const = 0;
        virtual size_t number_of_buttons(void) const = 0;

        virtual int axis_value(size_t index) const = 0;
        virtual bool is_button_pressed(size_t index) const = 0;
    };
}

#endif /* !QRK_JOYSTICK_H */
