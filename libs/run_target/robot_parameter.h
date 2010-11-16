#ifndef QRK_ROBOT_PARAMETER_H
#define QRK_ROBOT_PARAMETER_H

/*!
  \file
  \brief パラメータ

  \author Satofumi KAMIMURA

  $Id: robot_parameter.h 1927 2010-09-26 23:09:26Z satofumi $
*/


enum {
    CONTROL_CYCLE_MSEC_SHIFT = 3,
    CONTROL_CYCLE_MSEC = 1 << CONTROL_CYCLE_MSEC_SHIFT, //!< 制御周期 [msec]
};


#define ENCODER_RESOLUTION 400  //!< エンコーダ分解能 [1]
#define WHEEL_RADIUS_MM 47.932478   //!< 車輪の半径 [mm]
#define GEAR_RATIO 1.0          //!< ギヤ比 (モータ軸/車輪軸) [1]

// !!!
#define TREAD 280.22222         //!< トレッド [mm]

#endif /* !QRK_ROBOT_PARAMETER_H */
