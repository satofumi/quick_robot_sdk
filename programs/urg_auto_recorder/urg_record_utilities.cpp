/*!
  \file
  \brief URG 用の ログ記録の補助関数

  \author Satofumi KAMIMURA

  $Id$

  \todo ライブラリ用のソースコードとして管理する。
*/

#include "urg_record_utilities.h"
#include "Urg_driver.h"
#include <fstream>

using namespace qrk;
using namespace std;


bool save_csv_data(const qrk::Urg_driver& urg,
                   std::vector<long>& data,
                   const std::string& file_name)
{
    ofstream fout(file_name.c_str());
    if (!fout.is_open()) {
        return false;
    }

    size_t n = data.size();
    for (size_t i = 0; i < n; ++i) {
        fout << i << ", "
             << data[i] << ","
             << urg.index2rad(i)
             << endl;
    }

    return true;
}
