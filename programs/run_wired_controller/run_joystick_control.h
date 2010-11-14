#ifndef QRK_RUN_JOYSTICK_CONTROL_H
#define QRK_RUN_JOYSTICK_CONTROL_H

/*!
  \file
  \brief ジョイスティックによる走行コントローラの制御

  \author satofumi KAMIMURA

  $Id$

  \page run_joystick_control_h_page 操作方法

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

namespace qrk
{
    class Run_driver;
    class Usb_joystick;
}

extern bool control_by_joystick(qrk::Run_driver& robot_moving,
                                qrk::Usb_joystick& joystick);

#endif /* !QRK_RUN_JOYSTICK_CONTROL_H */
