//
// Created by Sergej Zuyev on 12/13/2016.
//

#include "../common/conversion/arithmetic.hpp"
#include "../machine/scalar/scalar.hpp"
#include "../machine/sse/sse.hpp"

#include <iostream>

int main() {
    zacc::zfloat f(10.5);

    std::cout << f + 10.3;

    zacc::sse::zfloat32 fv(12, 13, 14, 15);

    float v = f.get_value();

    std::cout << 10 * fv;

    std::cout << -((10.0f * fv + 24) * 123.0f) * 0 + 42 + f.get_value();

    std::cout << "conditional:" << fv.when(0).otherwise({1, 2, 3, 4});
    //zacc::
    getchar();

    return 0;
}
