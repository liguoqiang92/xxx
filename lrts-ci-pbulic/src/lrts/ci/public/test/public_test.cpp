/**
 * @file ver_public
 * @brief
 * @author dingjian
 * @date 2016-09-23
 *
 * $Id$
 */

#include <cppunit/extensions/HelperMacros.h>

#include "unifw.h"
#include "ci_public_comm.h"



extern "C"
{
    extern const mod_dscrp_t ver_public;
}

class test_public : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(test_public);
    CPPUNIT_TEST(test_public_ver            );
    CPPUNIT_TEST_SUITE_END();

public:
    test_public();
    virtual ~test_public();
    virtual void setUp();
    virtual void tearDown();
    void test_public_ver ();
};

test_public::test_public()
{
}

test_public::~test_public()
{
}

void test_public::setUp()
{
}

void test_public::tearDown()
{
}

void test_public::test_public_ver()
{
	msg_t m = 0x0101000D;
	uint32_t p_t = 0;
	void *p = &p_t;

    unit_print_module(&ver_public);
    CPPUNIT_EASSERT(0, ver_public.major);
    CPPUNIT_EASSERT(1, ver_public.minor);
    CPPUNIT_EASSERT(0, ver_public.patch);
    //main_loop();
    //main_logic();
    //data_init();
	m = 0x0101000C;
	p = NULL;
	CPPUNIT_EASSERT(1, route_add_autopass(m, p));
	m = 0x0101000D;
	p = NULL;
	CPPUNIT_EASSERT(2, route_add_autotrig(m, p));
	m = 0x0101000E;
	p = NULL;
	CPPUNIT_EASSERT(3, route_add_reentry(m, p));
	m = 0x01010010;
	p_t = 0x01000001;
	CPPUNIT_EASSERT(1, track_unlock_manu(m, p));
	//CPPUNIT_EASSERT(1, g_track[p_t].t_status);
}

CPPUNIT_TEST_SUITE_REGISTRATION(test_public);
