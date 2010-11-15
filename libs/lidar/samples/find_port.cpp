/*!
  \example find_port.c ポートの探索

  \author Satofumi KAMIMURA

  $Id: find_port.c,v 1146cf49af96 2010/10/29 21:18:57 Satofumi $
*/

#include "Urg_driver.h"
#include <iostream>

using namespace qrk;
using namespace std;


int main(void)
{
    vector<string> found_ports = Urg_driver::find_ports();

    size_t n = found_ports.size();
    if (n == 0) {
        cout << "could not found ports." << endl;
        return 1;
    }

    for (size_t i = 0; i < n; ++i) {
        cout << found_ports[i] << endl;
    }

    return 0;
}
