/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include </Users/Jacob/Xcode/labs/cxxtest/cxxtest/TestListener.h>
#include </Users/Jacob/Xcode/labs/cxxtest/cxxtest/TestTracker.h>
#include </Users/Jacob/Xcode/labs/cxxtest/cxxtest/TestRunner.h>
#include </Users/Jacob/Xcode/labs/cxxtest/cxxtest/RealDescriptions.h>
#include </Users/Jacob/Xcode/labs/cxxtest/cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "simple.cxxtest.cpp"

static MyTestSuite suite_MyTestSuite;

static CxxTest::List Tests_MyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite( "simple.cxxtest.cpp", 6, "MyTestSuite", suite_MyTestSuite, Tests_MyTestSuite );

static class TestDescription_MyTestSuite_test1 : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test1() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 8, "test1" ) {}
 void runTest() { suite_MyTestSuite.test1(); }
} testDescription_MyTestSuite_test1;

#include </Users/Jacob/Xcode/labs/cxxtest/cxxtest/Root.cpp>
