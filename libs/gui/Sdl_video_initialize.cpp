/*!
  \file
  \brief SDL_VIDEO の初期化

  \author Satofumi KAMIMURA

  $Id: Sdl_video_initialize.cpp 1904 2010-09-12 23:06:47Z satofumi $
*/

#include "Sdl_video_initialize.h"
#include "Sdl_initialize.h"
#include <SDL.h>


using namespace qrk;


struct Sdl_video_initialize::pImpl : private Sdl_initialize
{
    static bool initialized_;
};


bool Sdl_video_initialize::pImpl::initialized_ = false;


Sdl_video_initialize::Sdl_video_initialize(void) : pimpl(new pImpl)
{
    initialize();
}


Sdl_video_initialize::~Sdl_video_initialize(void)
{
    // exit() 時に SdlInit が SDL_Quit() を呼ぶので terminate() は呼び出さない
}


void Sdl_video_initialize::initialize(void)
{
    if (pimpl->initialized_) {
        return;
    }
    pimpl->initialized_ =
        (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) ? false : true;
}


void Sdl_video_initialize::terminate(void)
{
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    pimpl->initialized_ = false;
}
