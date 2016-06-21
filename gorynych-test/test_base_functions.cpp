//
// Created by szuyev on 17.05.16.
//

//#include "../Catch/single_include/catch.hpp"
#include "../gorynych/gorynych.h"

#include "test_extensions.h"

namespace zzsystems { namespace gorynych { namespace  test {

#define TYPE_PREFIX TEST_PREFIX("base functions")

    // Functions ===============================================================================================

    TEST_CASE(TYPE_PREFIX" mixed type vsel", "[functions]")
    {
        test<vint, sint>(45, 23, [](auto a, auto b) { return false ? a : b; }, [](auto a, auto b) { return vsel(ccl<vreal>::zeros(), a, b); });
        test<vint, sint>(45, 23, [](auto a, auto b) { return true ? a : b; },  [](auto a, auto b) { return vsel(ccl<vreal>::ones(), a, b); });

        test<vreal, sreal>(45, 23, [](auto a, auto b) { return false ? a : b; }, [](auto a, auto b) { return vsel(ccl<vint>::zeros(), a, b); });
        test<vreal, sreal>(45, 23, [](auto a, auto b) { return true ? a : b; },  [](auto a, auto b) { return vsel(ccl<vint>::ones(), a, b); });
    }
}}}