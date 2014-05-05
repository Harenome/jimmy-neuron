/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_test_suite_neuron_init = false;
#include "/home/harenome/Code/L3S6/Projets/ia/tests/test_neuron.hpp"

static test_suite_neuron suite_test_suite_neuron;

static CxxTest::List Tests_test_suite_neuron = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_test_suite_neuron( "test_neuron.hpp", 28, "test_suite_neuron", suite_test_suite_neuron, Tests_test_suite_neuron );

static class TestDescription_suite_test_suite_neuron_test_constructor_void : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_suite_neuron_test_constructor_void() : CxxTest::RealTestDescription( Tests_test_suite_neuron, suiteDescription_test_suite_neuron, 109, "test_constructor_void" ) {}
 void runTest() { suite_test_suite_neuron.test_constructor_void(); }
} testDescription_suite_test_suite_neuron_test_constructor_void;

static class TestDescription_suite_test_suite_neuron_test_constructor_weights : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_suite_neuron_test_constructor_weights() : CxxTest::RealTestDescription( Tests_test_suite_neuron, suiteDescription_test_suite_neuron, 120, "test_constructor_weights" ) {}
 void runTest() { suite_test_suite_neuron.test_constructor_weights(); }
} testDescription_suite_test_suite_neuron_test_constructor_weights;

static class TestDescription_suite_test_suite_neuron_test_constructor_neuron : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_suite_neuron_test_constructor_neuron() : CxxTest::RealTestDescription( Tests_test_suite_neuron, suiteDescription_test_suite_neuron, 135, "test_constructor_neuron" ) {}
 void runTest() { suite_test_suite_neuron.test_constructor_neuron(); }
} testDescription_suite_test_suite_neuron_test_constructor_neuron;

static class TestDescription_suite_test_suite_neuron_test_weights : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_suite_neuron_test_weights() : CxxTest::RealTestDescription( Tests_test_suite_neuron, suiteDescription_test_suite_neuron, 151, "test_weights" ) {}
 void runTest() { suite_test_suite_neuron.test_weights(); }
} testDescription_suite_test_suite_neuron_test_weights;

static class TestDescription_suite_test_suite_neuron_test_weight_number : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_suite_neuron_test_weight_number() : CxxTest::RealTestDescription( Tests_test_suite_neuron, suiteDescription_test_suite_neuron, 167, "test_weight_number" ) {}
 void runTest() { suite_test_suite_neuron.test_weight_number(); }
} testDescription_suite_test_suite_neuron_test_weight_number;

static class TestDescription_suite_test_suite_neuron_test_accumulate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_suite_neuron_test_accumulate() : CxxTest::RealTestDescription( Tests_test_suite_neuron, suiteDescription_test_suite_neuron, 176, "test_accumulate" ) {}
 void runTest() { suite_test_suite_neuron.test_accumulate(); }
} testDescription_suite_test_suite_neuron_test_accumulate;

static class TestDescription_suite_test_suite_neuron_test_attempt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_suite_neuron_test_attempt() : CxxTest::RealTestDescription( Tests_test_suite_neuron, suiteDescription_test_suite_neuron, 194, "test_attempt" ) {}
 void runTest() { suite_test_suite_neuron.test_attempt(); }
} testDescription_suite_test_suite_neuron_test_attempt;

static class TestDescription_suite_test_suite_neuron_test_operator_square_brackets : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_suite_neuron_test_operator_square_brackets() : CxxTest::RealTestDescription( Tests_test_suite_neuron, suiteDescription_test_suite_neuron, 221, "test_operator_square_brackets" ) {}
 void runTest() { suite_test_suite_neuron.test_operator_square_brackets(); }
} testDescription_suite_test_suite_neuron_test_operator_square_brackets;

static class TestDescription_suite_test_suite_neuron_test_begin : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_suite_neuron_test_begin() : CxxTest::RealTestDescription( Tests_test_suite_neuron, suiteDescription_test_suite_neuron, 235, "test_begin" ) {}
 void runTest() { suite_test_suite_neuron.test_begin(); }
} testDescription_suite_test_suite_neuron_test_begin;

static class TestDescription_suite_test_suite_neuron_test_end : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_suite_neuron_test_end() : CxxTest::RealTestDescription( Tests_test_suite_neuron, suiteDescription_test_suite_neuron, 250, "test_end" ) {}
 void runTest() { suite_test_suite_neuron.test_end(); }
} testDescription_suite_test_suite_neuron_test_end;

static class TestDescription_suite_test_suite_neuron_test_begin_const : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_suite_neuron_test_begin_const() : CxxTest::RealTestDescription( Tests_test_suite_neuron, suiteDescription_test_suite_neuron, 269, "test_begin_const" ) {}
 void runTest() { suite_test_suite_neuron.test_begin_const(); }
} testDescription_suite_test_suite_neuron_test_begin_const;

static class TestDescription_suite_test_suite_neuron_test_end_const : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_suite_neuron_test_end_const() : CxxTest::RealTestDescription( Tests_test_suite_neuron, suiteDescription_test_suite_neuron, 284, "test_end_const" ) {}
 void runTest() { suite_test_suite_neuron.test_end_const(); }
} testDescription_suite_test_suite_neuron_test_end_const;

static class TestDescription_suite_test_suite_neuron_test_add_weight : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_suite_neuron_test_add_weight() : CxxTest::RealTestDescription( Tests_test_suite_neuron, suiteDescription_test_suite_neuron, 303, "test_add_weight" ) {}
 void runTest() { suite_test_suite_neuron.test_add_weight(); }
} testDescription_suite_test_suite_neuron_test_add_weight;

static class TestDescription_suite_test_suite_neuron_test_set_weight : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_test_suite_neuron_test_set_weight() : CxxTest::RealTestDescription( Tests_test_suite_neuron, suiteDescription_test_suite_neuron, 323, "test_set_weight" ) {}
 void runTest() { suite_test_suite_neuron.test_set_weight(); }
} testDescription_suite_test_suite_neuron_test_set_weight;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
