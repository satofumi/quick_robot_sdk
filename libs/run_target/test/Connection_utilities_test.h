#ifndef QRK_CONNECTION_UTILITIES_TEST_H
#define QRK_CONNECTION_UTILITIES_TEST_H

/*!
  \file
  \brief connection_utilities.c のテスト

  \author Satofumi KAMIMURA

  $Id: Connection_utilities_test.h 1927 2010-09-26 23:09:26Z satofumi $
*/

#include <cppunit/extensions/HelperMacros.h>


//! connection_utilities.c のテストクラス
class Connection_utilities_test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(Connection_utilities_test);
    CPPUNIT_TEST(readline_test);
    CPPUNIT_TEST_SUITE_END();

public:
    void readline_test(void);
};

#endif /* !QRK_CONNECTION_UTILITIES_TEST_H */
