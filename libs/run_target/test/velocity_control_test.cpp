/*!
  \example velocity_control_test.cpp velocity_control.c のテスト

  \author Satofumi KAMIMURA

  $Id$
*/

#include "velocity_control.c"
#include <cstring>
#include <iostream>

using namespace std;


namespace
{
    typedef enum {
        Standard_velocity_test,
        Stop_top_position_test,
    } test_type_t;


    void velocity_standard_velocity_test(void)
    {
        // 初期化
        velocity_t velocity;
        velocity_initialize(&velocity);

#if 1
        // 加速のテスト
        velocity.target_velocity = 300;
        velocity.current_velocity = 0;
        velocity.target_acceleration = 300;
#endif
#if 0
        // 減速のテスト
        velocity.target_velocity = -300;
        velocity.current_velocity = 0;
        velocity.target_acceleration = 300;
#endif
#if 0
        // 正の速度に減速できるかのテスト
        velocity.target_velocity = 300;
        velocity.current_velocity = 400 << VELOCITY_INTERNAL_SHIFT_WIDTH;
        velocity.target_acceleration = 300;
#endif

        enum { Print_times = 200, };
        for (size_t i = 0; i < Print_times; ++i) {
            cout << velocity_standard_velocity(&velocity) << ", ";
        }
        cout << endl;
    }


    void velocity_stop_to_position_test(void)
    {
        // !!!
    }
}


int main(int argc, char *argv[])
{
    test_type_t test_type = Standard_velocity_test;
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-p")) {
            test_type = Stop_top_position_test;
        }
    }

    switch (test_type) {
    case Standard_velocity_test:
        velocity_standard_velocity_test();
        break;

    case Stop_top_position_test:
        velocity_stop_to_position_test();
        break;
    }

    return 0;
}
