//
// Created by szuyev on 17.05.16.
//

//#include "../Catch/single_include/catch.hpp"
#include "../gorynych/gorynych.h"

#include "test_extensions.h"

namespace zzsystems { namespace gorynych { namespace  test {

#define TYPE_PREFIX TEST_PREFIX("float")


            const float _num1 = 45.56345f;
            const float _num2 = -23.00005f;
            const float _num3 = 192.060194f;

            //SCENARIO()
            TEST_CASE(TYPE_PREFIX" arithmetic add", "[arithmetic]")
            {
                test<vreal, sreal>(_num1, _num2, std::plus<sreal>(), std::plus<vreal>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic sub", "[arithmetic]")
            {
                test<vreal, sreal>(_num1, _num2, std::minus<sreal>(), std::minus<vreal>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic mul", "[arithmetic]")
            {
                test<vreal, sreal>(_num1, _num2, std::multiplies<sreal>(), std::multiplies<vreal>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic div", "[aritmetic]")
            {
                test<vreal, sreal>(_num1, _num2, std::divides<sreal>(), std::divides<vreal>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic neg", "[arithmetic]")
            {
                test<vreal, sreal>(_num2, std::negate<sreal>(), std::negate<vreal>());
            }

            TEST_CASE(TYPE_PREFIX" fused multiply add", "[arithmetic]")
            {
                test<vreal, sreal>(_num1, _num2, _num3, [](auto a, auto b, auto c) { return a * b + c; }, [](auto a, auto b, auto c) { return vfmadd(a, b, c); });
            }

            TEST_CASE(TYPE_PREFIX" fused multiply sub", "[arithmetic]")
            {
                test<vreal, sreal>(_num1, _num2, _num3, [](auto a, auto b, auto c) { return a * b - c; }, [](auto a, auto b, auto c) { return vfmsub(a, b, c); });
            }

            // Bitwise =================================================================================================

//            TEST_CASE(TYPE_PREFIX" bitwise and", "[bitwise]")
//            {
//                test<vreal, sreal>(_num1, _num2, std::bit_and<sreal>(), std::bit_and<vreal>());
//            }
//
//            TEST_CASE(TYPE_PREFIX" bitwise or", "[bitwise]")
//            {
//                test<vreal, sreal>(_num1, _num2, std::bit_or<sreal>(), std::bit_or<vreal>());
//            }
//
//            TEST_CASE(TYPE_PREFIX" bitwise not", "[bitwise]")
//            {
//                test<vreal, sreal>(_num2, std::bit_not<sreal>(), std::bit_not<vreal>());
//            }
//
//            TEST_CASE(TYPE_PREFIX" bitwise xor", "[bitwise]")
//            {
//                test<vreal, sreal>(_num1, _num2, std::bit_xor<sreal>(), std::bit_xor<vreal>());
//            }

            // Logic ===================================================================================================

            TEST_CASE(TYPE_PREFIX" logic gt", "[logic]")
            {
                btest<vreal, sreal>(_num1, _num2, std::greater<sreal>(), [](auto a, auto b) { return a > b; });
                btest<vreal, sreal>(_num2, _num1, std::greater<sreal>(), [](auto a, auto b) { return a > b; });
            }

            TEST_CASE(TYPE_PREFIX" logic lt", "[logic]")
            {
                btest<vreal, sreal>(_num1, _num2, std::less<sreal>(), [](auto a, auto b) { return a < b; });
                btest<vreal, sreal>(_num2, _num1, std::less<sreal>(), [](auto a, auto b) { return a < b; });
            }

            TEST_CASE(TYPE_PREFIX" logic eq", "[logic]")
            {
                btest<vreal, sreal>(_num1, _num2, std::equal_to<sreal>(), [](auto a, auto b) { return a == b; });
                btest<vreal, sreal>(_num2, _num2, std::equal_to<sreal>(), [](auto a, auto b) { return a == b; });
            }

            TEST_CASE(TYPE_PREFIX" logic neq", "[logic]")
            {
                btest<vreal, sreal>(_num1, _num2, std::not_equal_to<sreal>(), [](auto a, auto b) { return a != b; });
                btest<vreal, sreal>(_num2, _num2, std::not_equal_to<sreal>(), [](auto a, auto b) { return a != b; });
            }

            // Functions ===============================================================================================

            TEST_CASE(TYPE_PREFIX" functions vabs", "[functions]")
            {
                test<vreal, sreal>(_num1, [](auto a) { return vabs(a); }, [](auto a) { return vabs(a); });
                test<vreal, sreal>(_num2, [](auto a) { return vabs(a); }, [](auto a) { return vabs(a); });
            }

            TEST_CASE(TYPE_PREFIX" functions vmin", "[functions]")
            {
                test<vreal, sreal>(_num1, _num2, [](auto a, auto b) { return vmin(a, b); }, [](auto a, auto b) { return vmin(a, b); });
                test<vreal, sreal>(_num2, _num1, [](auto a, auto b) { return vmin(a, b); }, [](auto a, auto b) { return vmin(a, b); });
            }

            TEST_CASE(TYPE_PREFIX" functions vmax", "[functions]")
            {
                test<vreal, sreal>(_num1, _num2, [](auto a, auto b) { return vmax(a, b); }, [](auto a, auto b) { return vmax(a, b); });
                test<vreal, sreal>(_num2, _num1, [](auto a, auto b) { return vmax(a, b); }, [](auto a, auto b) { return vmax(a, b); });
            }

            TEST_CASE(TYPE_PREFIX" functions vsel", "[functions]")
            {
                test<vreal, sreal>(_num1, _num2, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
                test<vreal, sreal>(_num2, _num1, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
                test<vreal, sreal>(_num2, _num2, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
            }
            
            // Rounding ================================================================================================

            TEST_CASE(TYPE_PREFIX" truncate", "[rounding]")
            {
                test<vreal, sreal>(_num1, [](auto a) { return std::trunc(a); }, [](auto a) { return vtrunc(a); });
                test<vreal, sreal>(_num2, [](auto a) { return std::trunc(a); }, [](auto a) { return vtrunc(a); });
                test<vreal, sreal>(_num3, [](auto a) { return std::trunc(a); }, [](auto a) { return vtrunc(a); });
            }

            TEST_CASE(TYPE_PREFIX" floor", "[rounding]")
            {
                test<vreal, sreal>(_num1, [](auto a) { return std::floor(a); }, [](auto a) { return vfloor(a); });
                test<vreal, sreal>(_num2, [](auto a) { return std::floor(a); }, [](auto a) { return vfloor(a); });
                test<vreal, sreal>(_num3, [](auto a) { return std::floor(a); }, [](auto a) { return vfloor(a); });
            }

            TEST_CASE(TYPE_PREFIX" ceil", "[rounding]")
            {
                test<vreal, sreal>(_num1, [](auto a) { return std::ceil(a); }, [](auto a) { return vceil(a); });
                test<vreal, sreal>(_num2, [](auto a) { return std::ceil(a); }, [](auto a) { return vceil(a); });
                test<vreal, sreal>(_num3, [](auto a) { return std::ceil(a); }, [](auto a) { return vceil(a); });
            }

            TEST_CASE(TYPE_PREFIX" round", "[rounding]")
            {
                test<vreal, sreal>(_num1, [](auto a) { return std::round(a); }, [](auto a) { return vround(a); });
                test<vreal, sreal>(_num2, [](auto a) { return std::round(a); }, [](auto a) { return vround(a); });
                test<vreal, sreal>(_num3, [](auto a) { return std::round(a); }, [](auto a) { return vround(a); });
            }
        }
    }
}