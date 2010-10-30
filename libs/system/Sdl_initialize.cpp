/*!
  \file
  \brief SDL の初期化

  \author Satofumi KAMIMURA

  $Id: Sdl_initialize.cpp 1903 2010-09-12 22:28:16Z satofumi $
*/

#include "Sdl_initialize.h"
#include <SDL.h>

using namespace qrk;


struct Sdl_initialize::pImpl
{
    static bool initialized_;
};


bool Sdl_initialize::pImpl::initialized_ = false;


Sdl_initialize::Sdl_initialize(void) : pimpl(new pImpl)
{
    if (pimpl->initialized_) {
        return;
    }

    if (SDL_Init(0) < 0) {
        // !!! エラー表示
        return;
    }

#if 0
    // OpenGL を利用した場合、終了時に警告がでるためコメントアウト
    atexit(SDL_Quit);
#endif

    pimpl->initialized_ = true;
}


Sdl_initialize::~Sdl_initialize(void)
{
}
