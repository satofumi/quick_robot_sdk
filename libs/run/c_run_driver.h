#ifndef QRK_C_RUN_DRIVER_H
#define QRK_C_RUN_DRIVER_H

/*!
  \file
  \brief 走行制御

  \author Satofumi KAMIMURA

  $Id: c_run_driver.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "run_driver_t.h"


extern int run_driver_open(run_driver_t *run, const char *device);
extern int run_driver_is_open(run_driver_t *run);
extern void run_driver_close(run_driver_t *run);
extern const char *run_driver_what(const run_driver_t *run);

//qrk::Position<long> position() const;

//bool set_path_line(const qrk::Position<long>& position,
//long stop_length);

//bool set_path_circle(const qrk::Point<long>& center, long radius,
//Circle_rotation_direction direction,
//const Angle& stop_angle);

//long path_length_to_target(void) const;

// !!!

extern void run_stop_module(void);
extern void run_resume_module(void);
extern int run_driver_set_wheel_velocity(run_driver_t *run,
                                         int wheel_id, short mm_per_sec);

#endif /* !QRK_C_RUN_DRIVER_H */
