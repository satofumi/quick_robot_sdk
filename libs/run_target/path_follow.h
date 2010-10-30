#ifndef QRK_PATH_FOLLOWER_H
#define QRK_PATH_FOLLOWER_H

/*!
  \file
  \brief 経路の制御

  \author Satofumi KAMIMURA

  $Id: path_follow.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "path_t.h"


//! 初期化
extern void path_follow_initialize(path_t *path);


// 状態の更新
extern void path_follow_update(path_t *path);

#endif /* !QRK_PATH_FOLLOWER_H */
