#ifndef RING_BUFFER_H
#define RING_BUFFER_H

/*!
  \file
  \brief リングバッファ

  \author Satofumi KAMIMURA

  $Id: ring_buffer.h 1927 2010-09-26 23:09:26Z satofumi $
*/


//! リングバッファの管理情報
typedef struct
{
    char *buffer;                 //!< バッファへのポインタ
    int buffer_size;              //!< バッファサイズ
    int first;                    //!< バッファの先頭位置
    int last;                     //!< バッファの最終位置
} ring_buffer_t;


/*!
  \brief 初期化

  \param[in] ring リングバッファの構造体
  \param[in] buffer 割り当てるバッファ
  \param[in] shift_length バッファサイズの 2 の乗数
*/
extern void ring_initialize(ring_buffer_t *ring,
                            char *buffer, const int shift_length);


/*!
  \brief リングバッファのクリア

  \param[in] ring リングバッファの構造体
*/
extern void ring_clear(ring_buffer_t *ring);


/*!
  \brief 格納データ数を返す

  \param[in] ring リングバッファの構造体
*/
extern int ring_size(const ring_buffer_t *ring);


/*!
  \brief 最大の格納データ数を返す

  \param[in] ring リングバッファの構造体
*/
extern int ring_capacity(const ring_buffer_t *ring);


/*!
  \brief データの格納

  \param[in] ring リングバッファの構造体
  \param[in] data データ
  \param[in] size データサイズ

  \return 格納したデータ数
*/
extern int ring_write(ring_buffer_t *ring, const char *data, int size);


/*!
  \brief データの取り出し

  \param[in] ring リングバッファの構造体
  \param[out] buffer データ
  \param[in] size 最大のデータサイズ

  \return 取り出したデータ数
*/
extern int ring_read(ring_buffer_t *ring, char *buffer, int size);


#if 0
//! 内部ポインタから直に読み出しを行う
extern int ring_readPtr(ring_buffer_t *ring, char **ptr, int size);
#endif

#endif /* ! RING_BUFFER_H */
