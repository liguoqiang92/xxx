/**
 * @file ver_routearr
 * @brief
 * @author root
 * @date 2016-09-24
 *
 * $Id$
 */

#include <cppunit/extensions/HelperMacros.h>

#include "unifw.h"
#include "routearr.h"
#include "public_arr.h"

extern "C"
{
    extern const mod_dscrp_t ver_routearr;
}


class test_routearr : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(test_routearr);
    CPPUNIT_TEST(test_routearr_ver            );
    CPPUNIT_TEST_SUITE_END();

public:
    test_routearr();
    virtual ~test_routearr();
    virtual void setUp();
    virtual void tearDown();
    void test_routearr_ver ();
};

test_routearr::test_routearr()
{
}

test_routearr::~test_routearr()
{
}

void test_routearr::setUp()
{
}

void test_routearr::tearDown()
{
}

void test_routearr::test_routearr_ver()
{

    unit_print_module(&ver_routearr);
    CPPUNIT_EASSERT(0, ver_routearr.major);
    CPPUNIT_EASSERT(1, ver_routearr.minor);
    CPPUNIT_EASSERT(0, ver_routearr.patch);

    //unit_print_module(&main_test);
    //CPPUNIT_EASSERT(1003, main_test.r_id);
    //unit_print_module(&route_choose);



    //data_init();

    printf("\n/************************************************************/\n");

    uint32_t s_id[2] = {0x03000003, 0x03000004};
    printf("g_route-> = %d\n", g_route->r_id);
    CPPUNIT_EASSERT(g_route->r_id, main_test(g_route, g_track, g_signal));

    CPPUNIT_EASSERT(0x02000003, route_choose(0, s_id));
    CPPUNIT_EASSERT(0, route_choose_check(&g_route[4]));
    CPPUNIT_EASSERT(0, track_check(&g_track[0], 3));
    CPPUNIT_EASSERT(0, signal_check(&g_signal[1]));

    printf("\n/************************************************************/\n");
}

CPPUNIT_TEST_SUITE_REGISTRATION(test_routearr);
