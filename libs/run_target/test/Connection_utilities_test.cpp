/*!
  \file
  \brief CONNECTION_UTILITIES のテスト

  \author Satofumi KAMIMURA

  $Id: Connection_utilities_test.cpp 1927 2010-09-26 23:09:26Z satofumi $
*/

#include "Connection_utilities_test.h"
#include "connection_utilities.h"
#include "host_connection.h"
#include "connection.h"
#include <string>

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(Connection_utilities_test);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(Connection_utilities_test,
                                      "Connection_utilities_test");


void Connection_utilities_test::readline_test(void)
{
    connection_initialize();

    // 改行までの文字列が返されるかのテスト
    send_command("a\n");
    char buffer[CONNECTION_READLINE_BUFFER_SIZE];
    int n =connection_readline(buffer, CONNECTION_READLINE_BUFFER_SIZE);
    CPPUNIT_ASSERT_EQUAL(1, n);
    CPPUNIT_ASSERT_EQUAL(string("a"), string(buffer));

    // データがないときの読み出しが  -1 を返すかのテスト
    n =connection_readline(buffer, CONNECTION_READLINE_BUFFER_SIZE);
    CPPUNIT_ASSERT_EQUAL(-1, n);

    // 改行のみのときの読み出しがゼロを返すかのテスト
    send_command("\n");
    n =connection_readline(buffer, CONNECTION_READLINE_BUFFER_SIZE);
    CPPUNIT_ASSERT_EQUAL(0, n);

    // 再度、改行までの文字列が返されるかのテスト
    send_command("123\n");
    n =connection_readline(buffer, CONNECTION_READLINE_BUFFER_SIZE);
    CPPUNIT_ASSERT_EQUAL(3, n);
    CPPUNIT_ASSERT_EQUAL(string("123"), string(buffer));

}
