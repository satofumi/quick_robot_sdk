#ifndef QRK_RUN_COMMANDS_TEST_H
#define QRK_RUN_COMMANDS_TEST_H

/*!
  \file
  \brief run_commands.c のテスト

  \author Satofumi KAMIMURA

  $Id: Run_commands_test.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include <cppunit/extensions/HelperMacros.h>


//! run_commands.c のテストクラス
class Run_commands_test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(Run_commands_test);
    CPPUNIT_TEST(wv_command_test);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void wv_command_test(void);
};

#endif /* !QRK_RUN_COMMANDS_TEST_H */
