#ifndef QRK_USB_JOYSTICK_H
#define QRK_USB_JOYSTICK_H

/*!
  \file
  \brief USB コントローラ

  \author Satofumi KAMIMURA

  $Id: Usb_joystick.h 1907 2010-09-13 21:58:51Z satofumi $
*/

#include "Joystick.h"
#include <memory>


namespace qrk
{
    class Usb_joystick : public Joystick
    {
    public:
        Usb_joystick(void);
        ~Usb_joystick(void);

        void set_event(void* event);

        size_t number_of_joysticks(void);
        const char* what(void) const;
        bool open(int device_index = Auto_selected);
        void close(void);

        size_t number_of_axes(void) const;
        size_t number_of_buttons(void) const;

        int axis_value(size_t index) const;
        bool is_button_pressed(size_t index) const;

    private:
        Usb_joystick(const Usb_joystick& rhs);
        Usb_joystick& operator = (const Usb_joystick& rhs);

        struct pImpl;
        std::auto_ptr<pImpl> pimpl;
    };
}

#endif /* !QRK_USB_JOYSTICK_H */
