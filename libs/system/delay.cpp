/*!
  \file
  \brief 待機

  \author Satofumi KAMIMURA

  $Id: delay.cpp 1937 2010-10-25 01:12:49Z satofumi $
*/

#include "delay.h"
#include <SDL.h>


void qrk::delay(long msec)
{
    SDL_Delay(msec);
}
