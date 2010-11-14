/*!
  \file
  \brief run_commands.c のテスト

  \author Satofumi KAMIMURA

  $Id: Run_commands_test.cpp 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "Run_commands_test.h"
#include "host_connection.h"
#include "connection_utilities.h"
#include "connection.h"
#include "protocol_handler.h"
#include <string>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(Run_commands_test);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(Run_commands_test, "Run_commands_test");


namespace {
    run_t run_;
}


void Run_commands_test::setUp(void)
{
    for (int i = 0; i < 2; ++i) {
        run_.wheel[i].target_velocity = 0;
    }
}


void wheel_set_velocity(wheel_t *wheel, int mm_per_sec)
{
    wheel->target_velocity = mm_per_sec;
}


void Run_commands_test::op_command_test(void)
{
    // テストに使う変数を初期化
    run_.odometry.direction = 2;
    for (int i = 0; i < 2; ++i) {
        run_.odometry.km[i] = 0;
        run_.odometry.m[i] = 0;
        run_.odometry.mm[i] = 1;
    }

    connection_initialize();

    // 応答が返されるかのテスト
    send_command("OP\n");
    protocol_update(&run_);
    string reply_line = receive_response_line();
    CPPUNIT_ASSERT_EQUAL(string("OP0\n"), reply_line);

    reply_line = receive_response_line();
    CPPUNIT_ASSERT_EQUAL(string("00000001000000010002\n"), reply_line);
}


void Run_commands_test::wv_command_test(void)
{
    // テストに使う変数を初期化
    for (int i = 0; i < 2; ++i) {
        run_.wheel[0].target_velocity = 0;
    }

    connection_initialize();

    // 応答が返されるかのテスト
    send_command("WV00000\n");
    protocol_update(&run_);
    string reply_line = receive_response_line();
    CPPUNIT_ASSERT_EQUAL(string("WV0\n"), reply_line);
    CPPUNIT_ASSERT_EQUAL(0, run_.wheel[0].target_velocity);

    // 値が適切に設定されるかのテスト
    send_command("WV00001\n");
    protocol_update(&run_);
    reply_line = receive_response_line();
    CPPUNIT_ASSERT_EQUAL(string("WV0\n"), reply_line);
    CPPUNIT_ASSERT_EQUAL(1, run_.wheel[0].target_velocity);

    send_command("WV10001\n");
    protocol_update(&run_);
    reply_line = receive_response_line();
    CPPUNIT_ASSERT_EQUAL(string("WV0\n"), reply_line);
    CPPUNIT_ASSERT_EQUAL(1, run_.wheel[1].target_velocity);

    send_command("WV0ffff\n");
    protocol_update(&run_);
    reply_line = receive_response_line();
    CPPUNIT_ASSERT_EQUAL(string("WV0\n"), reply_line);
    CPPUNIT_ASSERT_EQUAL(-1, run_.wheel[0].target_velocity);

    // 範囲外の ID がエラーになるかのテスト
    send_command("WV20000\n");
    protocol_update(&run_);
    reply_line = receive_response_line();
    CPPUNIT_ASSERT_EQUAL(string("WV2\n"), reply_line);
}
