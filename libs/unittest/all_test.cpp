#include <string>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/HelperMacros.h>
#include <stdexcept>
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
  static_cast<void>(argc);
  static_cast<void>(argv);

  CPPUNIT_NS::TestResult controller;

  CPPUNIT_NS::TestResultCollector result;
  controller.addListener(&result);

  //CPPUNIT_NS::TextTestProgressListener progress;
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener(&progress);

  CPPUNIT_NS::TestRunner runner;
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());

  runner.run(controller, "");

  CPPUNIT_NS::CompilerOutputter outputter(&result, cerr);
  outputter.write();

#if defined(_MSC_VER)
  getchar();
#endif
  return result.wasSuccessful() ? 0 : 1;
}
