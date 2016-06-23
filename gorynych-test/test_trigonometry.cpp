//
// Created by szuyev on 17.05.16.
//

//#include "../Catch/single_include/catch.hpp"
#include "../gorynych/gorynych.h"
#include "test_extensions.h"

namespace zzsystems { namespace gorynych { namespace  test {

#define TYPE_PREFIX TEST_PREFIX("trigonometric functions")

    using namespace gorynych::math;
    // Functions ===============================================================================================

    TEST_CASE(TYPE_PREFIX" sin", "[functions][trigonometry]")
    {
        test<vreal, sreal>(45, 23, [](auto a, auto b) { return sin(a); }, [](auto a, auto b) { return vsin(a); });
    }

    TEST_CASE(TYPE_PREFIX" cos", "[functions][trigonometry]")
    {
        test<vreal, sreal>(45, 23, [](auto a, auto b) { return cos(a); }, [](auto a, auto b) { return vcos(a); });
    }
}}}