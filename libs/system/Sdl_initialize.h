#ifndef QRK_SDL_INITIALIZE_H
#define QRK_SDL_INITIALIZE_H

/*!
  \file
  \brief SDL の初期化

  \author Satofumi KAMIMURA

  $Id: Sdl_initialize.h 1903 2010-09-12 22:28:16Z satofumi $
*/

#include <memory>


namespace qrk
{
    //! SDL システムの初期化クラス
    class Sdl_initialize
    {
    protected:
        Sdl_initialize(void);
        ~Sdl_initialize(void);

    private:
        Sdl_initialize(const Sdl_initialize& rhs);
        Sdl_initialize& operator = (const Sdl_initialize& rhs);

        struct pImpl;
        const std::auto_ptr<pImpl> pimpl;
    };
}

#endif /* !QRK_SDL_INITIALIZE_H */
