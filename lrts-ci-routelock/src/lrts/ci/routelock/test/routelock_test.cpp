/**
 * @file ver_routelock
 * @brief
 * @author admin
 * @date 2016-09-23
 *
 * $Id$
 */

#include <cppunit/extensions/HelperMacros.h>

#include "unifw.h"
#include "ci_public_comm.h"
#include "routelock.h"
#include "routeopen.h"
#include "routelock_in.h"
#include "signal.h"


extern "C"
{
    extern const mod_dscrp_t ver_routelock;
}

class test_routelock : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(test_routelock);
    CPPUNIT_TEST(test_routelock_ver            );
    CPPUNIT_TEST_SUITE_END();

public:
    test_routelock();
    virtual ~test_routelock();
    virtual void setUp();
    virtual void tearDown();
    void test_routelock_ver ();
};

test_routelock::test_routelock()
{
}

test_routelock::~test_routelock()
{
}

void test_routelock::setUp()
{
}

void test_routelock::tearDown()
{
}

void test_routelock::test_routelock_ver()
{
    uint32_t track_id;
    uint32_t route_id;

    msg_t m = 0x0101000D;
    uint32_t p_t = 0;
    void *p = &p_t;

    unit_print_module(&ver_routelock);
    CPPUNIT_EASSERT(0, ver_routelock.major);
    CPPUNIT_EASSERT(1, ver_routelock.minor);
    CPPUNIT_EASSERT(0, ver_routelock.patch);

    track_id = 0x01000001;
    route_id = 0x02000003;
    track_lock_check(track_id);

    route_lock_advance(m, p);

    route_lock_prox(m, p);

    route_lock_prox(m, p);

}

CPPUNIT_TEST_SUITE_REGISTRATION(test_routelock);
