/**
 * @file ver_signal
 * @brief
 * @author admin
 * @date 2016-09-28
 *
 * $Id$
 */

#include <cppunit/extensions/HelperMacros.h>

#include "unifw.h"
#include "signal.h"

extern "C"
{
    extern const mod_dscrp_t ver_signal;
}

class test_signal : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(test_signal);
    CPPUNIT_TEST(test_signal_ver            );
    CPPUNIT_TEST_SUITE_END();

public:
    test_signal();
    virtual ~test_signal();
    virtual void setUp();
    virtual void tearDown();
    void test_signal_ver ();
};

test_signal::test_signal()
{
}

test_signal::~test_signal()
{
}

void test_signal::setUp()
{
}

void test_signal::tearDown()
{
}

void test_signal::test_signal_ver()
{
    unit_print_module(&ver_signal);
    CPPUNIT_EASSERT(0, ver_signal.major);
    CPPUNIT_EASSERT(1, ver_signal.minor);
    CPPUNIT_EASSERT(0, ver_signal.patch);
    signal_check_gob_red(0x03000006);
    signal_set_dis(0x03000007, RED);
    signal_get_status(0x03000007);
    signal_set_dis(0x03000008, GREEN_WITHOUT_PROTECT);
    signal_get_status(0x03000008);


}

CPPUNIT_TEST_SUITE_REGISTRATION(test_signal);
