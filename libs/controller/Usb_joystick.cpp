/*!
  \file
  \brief USB コントローラ

  \author Satofumi KAMIMURA

  $Id: Usb_joystick.cpp 1907 2010-09-13 21:58:51Z satofumi $
*/

#include "Usb_joystick.h"
#include "Sdl_video_initialize.h"
#include <SDL.h>
#include <vector>
#include <string>

using namespace qrk;
using namespace std;


namespace
{
    class Usb_joystick_initialize : private Sdl_video_initialize
    {
    private:
        static bool initialized_;


    protected:
        Usb_joystick_initialize(void)
        {
            if (initialized_) {
                return;
            }
            if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0) {
                // !!! エラーメッセージの表示
                return;
            }
            atexit(quit_joystick);
            SDL_JoystickEventState(SDL_ENABLE);

            initialized_ = true;
        }


        static void quit_joystick(void)
        {
            SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
        }
    };


    bool Usb_joystick_initialize::initialized_ = false;


    class Joystick_group
    {
    public:

        class Joystick_event
        {
        public:
            SDL_Joystick* pointer_;
            int own_device_index_;
            vector<short> axis_value_;
            vector<bool> is_button_pressed_;


            Joystick_event(void) : pointer_(NULL), own_device_index_(-1)
            {
            }
        };


        vector<Joystick_event> events_;


        static Joystick_group* singleton(void)
        {
            static Joystick_group singleton_object;
            return &singleton_object;
        }
    };
}


struct Usb_joystick::pImpl : private Usb_joystick_initialize
{
    string error_message_;
    Joystick_group* joysticks_;
    size_t own_device_index_;
    size_t number_of_axes_;
    size_t number_of_buttons_;


    pImpl(void)
        : error_message_("no error."),
          joysticks_(Joystick_group::singleton()),
          own_device_index_(joysticks_->events_.size()),
          number_of_axes_(0), number_of_buttons_(0)
    {
        joysticks_->events_.resize(own_device_index_ + 1);
    }


    bool open(int device_index)
    {
        if (SDL_JoystickOpened(device_index)) {
            error_message_ = "already connected.";
            return false;
        }

        SDL_Joystick* p = SDL_JoystickOpen(device_index);
        if (p == NULL) {
            error_message_ = SDL_GetError();
            return false;
        }
        joysticks_->events_[own_device_index_].pointer_ = p;
        joysticks_->events_[own_device_index_].own_device_index_ = device_index;

        number_of_axes_ = SDL_JoystickNumAxes(p);
        for (size_t i = 0; i < number_of_axes_; ++i) {
            joysticks_->events_[own_device_index_].axis_value_.push_back(0);
        }

        number_of_buttons_ = SDL_JoystickNumButtons(p);
        for (size_t i = 0; i < number_of_buttons_; ++i) {
            joysticks_->events_[own_device_index_].
                is_button_pressed_.push_back(false);
        }
        return true;
    }


    bool is_opend(void) const
    {
        if ((joysticks_->events_.size() <= own_device_index_) ||
            (joysticks_->events_[own_device_index_].pointer_ == NULL)) {
            return false;
        } else {
            return true;
        }
    }


    void axis_event_handler(SDL_JoyAxisEvent& event)
    {
        joysticks_->events_[event.which].axis_value_[event.axis] = event.value;
    }


    void button_event_handler(SDL_JoyButtonEvent& event)
    {
        joysticks_->events_[event.which].is_button_pressed_[event.button] =
            (event.state == SDL_PRESSED) ? true : false;
    }
};


Usb_joystick::Usb_joystick(void) : pimpl(new pImpl)
{
}


Usb_joystick::~Usb_joystick(void)
{
    if (pimpl->is_opend()) {
        close();
    }
}


void Usb_joystick::set_event(void* event)
{
    if (!pimpl->is_opend()) {
        return;
    }

    SDL_Event* sdl_event = static_cast<SDL_Event*>(event);
    switch (sdl_event->type) {

    case SDL_JOYAXISMOTION:
        pimpl->axis_event_handler(sdl_event->jaxis);
        break;

#if 0
    case SDL_JOYBALLMOTION:
        pimpl->ball_event_handler(event.jball);
        break;

    case SDL_JOYHATMOTION:
        pimpl->hat_event_handler(event.jhat);
        break;
#endif

    case SDL_JOYBUTTONDOWN:
    case SDL_JOYBUTTONUP:
        pimpl->button_event_handler(sdl_event->jbutton);
        break;
    }
}


const char* Usb_joystick::what(void) const
{
    return pimpl->error_message_.c_str();
}


size_t Usb_joystick::number_of_joysticks(void)
{
    return SDL_NumJoysticks();
}


bool Usb_joystick::open(int device_id)
{
    if (device_id >= 0) {
        return pimpl->open(device_id);

    } else {
        size_t n = number_of_joysticks();
        if (n <= 0) {
            return pimpl->open(0);
        }
        for (size_t i = 0; i < n; ++i) {
            bool ret = pimpl->open(i);
            if (ret) {
                return ret;
            }
        }
    }
    return false;
}


void Usb_joystick::close(void)
{
    if (!pimpl->is_opend()) {
        return;
    }

    SDL_JoystickClose(pimpl->joysticks_->
                      events_[pimpl->own_device_index_].pointer_);
}


size_t Usb_joystick::number_of_axes(void) const
{
    return pimpl->number_of_axes_;
}


size_t Usb_joystick::number_of_buttons(void) const
{
    return pimpl->number_of_buttons_;
}


int Usb_joystick::axis_value(size_t index) const
{
    if (!pimpl->is_opend()) {
        return 0;
    }

    return pimpl->joysticks_->
        events_[pimpl->own_device_index_].axis_value_[index];
}


bool Usb_joystick::is_button_pressed(size_t index) const
{
    if (!pimpl->is_opend()) {
        return false;
    }

    return pimpl->joysticks_->
        events_[pimpl->own_device_index_].is_button_pressed_[index];
}
