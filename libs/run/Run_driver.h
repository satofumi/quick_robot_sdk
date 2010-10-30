#ifndef QRK_RUN_DRIVER_H
#define QRK_RUN_DRIVER_H

/*!
  \file
  \brief 走行制御

  \author Satofumi KAMIMURA

  $Id: Run_driver.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "Position.h"
#include "Point.h"
#include <memory>


namespace qrk
{
    //! 走行制御
    class Run_driver
    {
    public:
        typedef enum {
            CCW,                //!< 反時計回り
            CW,                 //!< 時計回り
        } Circle_rotation_direction;


        Run_driver(void);
        ~Run_driver(void);


        //! 直前のエラーの内容を返す
        const char* what(void) const;


        /*!
          \brief 接続を行う

          \param[in] device 接続デバイス名
          \retval true 正常
          \retval false エラー

          Example
          \code
          Run_driver run;
          if (!run.open("COM3")) {
              cout << "Run_driver::open(): " << run.what() << endl;
              return -1;
          }
          \endcode

          \see close()
        */
        bool open(const char *device);


        //! 接続を閉じる
        void close(void);


        //! 推定位置の取得
        qrk::Position<long> position() const;


        // position() で返される推定位置をずらす
        // !!!


        /*!
          \brief 直線追従コマンド

          !!! 図で説明する
        */
        bool set_path_line(const qrk::Position<long>& position,
                           long stop_length);


        /*!
          \brief 円弧追従コマンド

          !!! 図で説明する
        */
        bool set_path_circle(const qrk::Point<long>& center, long radius,
                             Circle_rotation_direction direction,
                             const Angle& stop_angle);


        /*!
          \brief 目標までの距離を取得

          !!! 図で説明する
        */
        long path_length_to_target(void) const;


        // 移動の開始
        // !!!


        // 移動の停止
        // !!!


        // 並進速度の速度、加速度を指定
        // !!!


        // 回転速度の速度、加速度を指定
        // !!!


        //! 走行モジュールを "緊急停止" させる
        bool stop_module(void);


        //! 走行モジュールの通常動作を再開する
        bool resume_module(void);


        // 車輪の速度を指示
        // !!! id の順番を定義する
        // !!! 0: 左
        // !!! 1: 右
        // !!! 戻り値を返すべきかを検討する
        bool set_wheel_velocity(int wheel_id, short mm_per_sec);


    private:
        Run_driver(const Run_driver& rhs);
        Run_driver& operator = (const Run_driver& rhs);

        struct pImpl;
        std::auto_ptr<pImpl> pimpl;
    };
}

#endif /* !QRK_RUN_DRIVER_H */


/*!
  \page run_driver_h_command_page 走行コマンドについて (記述中)

  !!! コマンド構成について記述する
*/
