/*!
  \file
  \brief 走行制御

  \author Satofumi KAMIMURA

  $Id: Run_driver.cpp 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "Run_driver.h"
extern "C" {
#include "c_run_driver.h"
}
#include "math_utilities.h"
#include <string>

using namespace qrk;
using namespace std;


struct Run_driver::pImpl
{
    string error_message_;
    run_driver_t run_;


    pImpl(void) : error_message_("no error.")
    {
    }
};


Run_driver::Run_driver(void) : pimpl(new pImpl)
{
}


Run_driver::~Run_driver(void)
{
}


const char* Run_driver::what(void) const
{
    return pimpl->error_message_.c_str();
}


bool Run_driver::open(const char *device)
{
    bool ret = (run_driver_open(&pimpl->run_, device) == 0) ? true : false;
    pimpl->error_message_ = run_driver_what(&pimpl->run_);
    return ret;
}


void Run_driver::close(void)
{
    run_driver_close(&pimpl->run_);
}


qrk::Position<long> Run_driver::position() const
{
    // !!!

    if (run_driver_is_open(&pimpl->run_) != 0) {
        // !!! エラー状態を更新する
        Position<long> dummy;
        return dummy;
    }

    long x_mm;
    long y_mm;
    unsigned short direction;
    int ret = run_position(&pimpl->run_, &x_mm, &y_mm, &direction);
    if (ret != 0) {
        Position<long> dummy;
        return dummy;
    }

    Position<long> position(x_mm, y_mm, rad(2.0 * M_PI * direction / 0xffff));
    return position;
}


bool Run_driver::set_path_line(const qrk::Position<long>& position,
                                   long stop_length)
{
    (void)position;
    (void)stop_length;
    // !!!
    return false;
}


bool Run_driver::set_path_circle(const qrk::Point<long>& center,
                                     long radius,
                                     Circle_rotation_direction direction,
                                     const Angle& stop_angle)
{
    (void)center;
    (void)radius;
    (void)direction;
    (void)stop_angle;
    // !!!
    return false;
}


long Run_driver::path_length_to_target(void) const
{
    // !!!
    return -1;
}


bool Run_driver::stop_module(void)
{
    // !!!
    return false;
}


bool Run_driver::resume_module(void)
{
    // !!!
    return false;
}


bool Run_driver::set_wheel_velocity(int wheel_id, short mm_per_sec)
{
    if (run_driver_is_open(&pimpl->run_) != 0) {
        // !!! エラー状態を更新する
        return false;
    }

    int ret = run_set_wheel_velocity(&pimpl->run_, wheel_id, mm_per_sec);
    return (ret == 0) ? true : false;
}
