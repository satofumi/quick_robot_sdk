/*!
  \file
  \brief ログ記録の補助関数

  \author Satofumi KAMIMURA

  $Id$
*/

#include "record_utilities.h"
#include <sys/stat.h>

using namespace std;


string create_record_directory(void)
{
    enum { Buffer_size = 80 };
    char buffer[Buffer_size];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(buffer, Buffer_size, "%F_%H_%M_%S", tm);

    mkdir(buffer, 0755);

    return buffer;
}
