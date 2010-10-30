#ifndef QRK_PATH_T_H
#define QRK_PATH_T_H

/*!
  \file
  \brief 経路の管理

  \author Satofumi KAMIMURA

  $Id: path_t.h 1927 2010-09-26 23:09:26Z satofumi $
*/


//! 経路モード
typedef enum {
    PATH_FOLLOW_LINE,           //!< 直線追従
    PATH_FOLLOW_CIRCLE,         //!< 円弧追従
} path_mode_t;


//! 経路の管理
typedef struct
{
    path_mode_t path_mode;
} path_t;

#endif /* !QRK_PATH_T_H */
