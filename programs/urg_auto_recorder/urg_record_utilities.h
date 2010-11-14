#ifndef QRK_URG_RECORD_UTILITIES_H
#define QRK_URG_RECORD_UTILITIES_H

/*!
  \file
  \brief URG 用の ログ記録の補助関数

  \author Satofumi KAMIMURA

  $Id$

  \todo ライブラリ用のソースコードとして管理する。
*/

#include <vector>
#include <string>

namespace qrk
{
    class Urg_driver;
}


extern bool save_csv_data(const qrk::Urg_driver& urg,
                          std::vector<long>& data,
                          const std::string& file_name);

#endif /* !QRK_RECORD_UTILITIES_H */
