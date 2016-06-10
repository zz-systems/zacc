//
// Created by szuyev on 17.05.16.
//

#include "../Catch/single_include/catch.hpp"
#include "../gorynych/gorynych.h"
#include "test_extensions.h"

namespace zzsystems { namespace gorynych { namespace  test {

#define TYPE_PREFIX TEST_PREFIX("fastload int")


//            TEST_CASE(TYPE_PREFIX" fastload min", "[fastload]")
//            {
//                test<vint, sint>([]() { return ccl<sint>::min(); }, []() { return ccl<vint>::min(); });
//            }
//
//            TEST_CASE(TYPE_PREFIX" fastload max", "[fastload]")
//            {
//                test<vint, sint>([]() { return ccl<sint>::max(); }, []() { return ccl<vint>::max(); });
//            }

//            TEST_CASE(TYPE_PREFIX" fastload sign1all0", "[fastload]")
//            {
//                test<vint, sint>([]() { return ccl<sint>::sign1all0(); }, []() { return ccl<vint>::sign1all0(); });
//            }
//
//            TEST_CASE(TYPE_PREFIX" fastload sign0all1", "[fastload]")
//            {
//                test<vint, sint>([]() { return ccl<sint>::sign0all1(); }, []() { return ccl<vint>::sign0all1(); });
//            }

            //SCENARIO()
            TEST_CASE(TYPE_PREFIX" fastload 0", "[fastload]")
            {
                test<vint, sint>([]() { return 0; }, []() { return cfl<vint, 0>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 1", "[fastload]")
            {
                test<vint, sint>([]() { return 1; }, []() { return cfl<vint, 1>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 2", "[fastload]")
            {
                test<vint, sint>([]() { return 2; }, []() { return cfl<vint, 2>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 3", "[fastload]")
            {
                test<vint, sint>([]() { return 3; }, []() { return cfl<vint, 3>::val(); });
            }

            TEST_CASE(TYPE_PREFIX" fastload 4", "[fastload]")
            {
                test<vint, sint>([]() { return 4; }, []() { return cfl<vint, 4>::val(); });
            }

            TEST_CASE(TYPE_PREFIX" fastload 5", "[fastload]")
            {
                test<vint, sint>([]() { return 5; }, []() { return cfl<vint, 5>::val(); });
            }

            TEST_CASE(TYPE_PREFIX" fastload 6", "[fastload]")
            {
                test<vint, sint>([]() { return 6; }, []() { return cfl<vint, 6>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 7", "[fastload]")
            {
                test<vint, sint>([]() { return 7; }, []() { return cfl<vint, 7>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 8", "[fastload]")
            {
                test<vint, sint>([]() { return 8; }, []() { return cfl<vint, 8>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 9", "[fastload]")
            {
                test<vint, sint>([]() { return 9; }, []() { return cfl<vint, 9>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 10", "[fastload]")
            {
                test<vint, sint>([]() { return 10; }, []() { return cfl<vint, 10>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 11", "[fastload]")
            {
                test<vint, sint>([]() { return 11; }, []() { return cfl<vint, 11>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 12", "[fastload]")
            {
                test<vint, sint>([]() { return 12; }, []() { return cfl<vint, 12>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 13", "[fastload]")
            {
                test<vint, sint>([]() { return 13; }, []() { return cfl<vint, 13>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 14", "[fastload]")
            {
                test<vint, sint>([]() { return 14; }, []() { return cfl<vint, 14>::val(); });
            }
            TEST_CASE(TYPE_PREFIX" fastload 15", "[fastload]")
            {
                test<vint, sint>([]() { return 15; }, []() { return cfl<vint, 15>::val(); });
            }
        }
    }
}