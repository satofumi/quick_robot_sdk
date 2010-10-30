#ifndef QRK_SDL_VIDEO_INITIALIZE_H
#define QRK_SDL_VIDEO_INITIALIZE_H

/*!
  \file
  \brief SDL_VIDEO の初期化

  \author Satofumi KAMIMURA

  $Id: Sdl_video_initialize.h 1904 2010-09-12 23:06:47Z satofumi $
*/

#include <memory>


namespace qrk
{
    //! SDL_VIDEO システムの初期化クラス
    class Sdl_video_initialize
    {
    public:
        Sdl_video_initialize(void);
        ~Sdl_video_initialize(void);


        //! システムの初期化
        void initialize(void);


        //! システムの終了
        void terminate(void);


    private:
        Sdl_video_initialize(const Sdl_video_initialize& rhs);
        Sdl_video_initialize& operator = (const Sdl_video_initialize& rhs);

        struct pImpl;
        const std::auto_ptr<pImpl> pimpl;
    };
}

#endif /* !QRK_SDL_VIDEO_INITIALIZE_H */
