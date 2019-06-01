//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2018 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------------


#include <iostream>

#include <zacc/system/arch.hpp>
#include <zacc/compute/expressions.hpp>
#include <zacc/compute/impl/default.hpp>
#include <zacc/compute/impl/matrix2d.hpp>
#include <zacc/compute/impl/complex.hpp>

#include <functional>

int main(int argc, char** argv)
{
    using namespace zacc;
    using namespace zacc::compute;

//    auto e = bin_expr<std::plus<>, lit<int>, lit<int>>(lit<int>(1), lit<int>(2));
//
//    std::cout << e() << std::endl;

    {
        std::cout << "arithmetic" << std::endl << std::endl;

        scope<recorder> scope;

        batch<int, 2> a{{1, 2}};
        batch<int, 2> b{{2, 4}};

        batch<int, 2> basic;

        basic = a + b;
        basic = b + a;

        basic = a - b;
        basic = b - a;

        basic = a * b;
        basic = b * a;

        basic = a / b;
        basic = b / a;

        basic = a % b;
        basic = b % a;

        basic = -a;
        basic = -b;

        basic = -(-a);
        basic = -(-b);

        basic = +a;
        basic = +b;

        std::cout << scope << std::endl;
    }

    {
        std::cout << "fma" << std::endl << std::endl;

        scope<recorder> scope;

        batch<int, 2> a{{1, 2}};
        batch<int, 2> b{{2, 4}};
        batch<int, 2> c{{3, 6}};
        batch<int, 2> d{{4, 8}};

        batch<int, 2> fma;

        fma = a + b * c;
        fma = a * b + c;
        fma = a * a + b * b;
        fma = a * a - b * b;
        fma = a * a + b * b + c * c;
        fma = a * a - b * b + c * c;

        std::cout << scope << std::endl;
    }

    {
        std::cout << "comparisons" << std::endl << std::endl;

        scope<recorder> scope;

        batch<int, 2> a{{1, 2}};
        batch<int, 2> b{{2, 2}};

        batch<bool, 2> basic;

        basic = a == b;
        basic = b == a;

        basic = a != b;
        basic = b != a;

        basic = a > b;
        basic = b > a;

        basic = a < b;
        basic = b < a;

        basic = a >= b;
        basic = b >= a;

        basic = a <= b;
        basic = b <= a;

        std::cout << scope << std::endl;
    }

    {
        std::cout << "logical operations" << std::endl << std::endl;

        scope<recorder> scope;

        batch<bool, 2> a{{ false, true}};
        batch<bool, 2> b{{ true, true }};

        batch<bool, 2> basic;

        basic = a && b;
        basic = b && a;

        basic = a || b;
        basic = b || a;

        basic = !a;
        basic = !b;

        basic = !!a;
        basic = !!b;

       //std::cout << evaluator::current() << b && a << std::endl;

        std::cout << scope << std::endl;
    }

    {
        std::cout << "cast" << std::endl << std::endl;

        scope<recorder> scope;

        batch<int, 2> a{{1, 2}};
        batch<int, 2> b{{2, 4}};

        batch<int, 2> basic;

        basic = a + 1;
        //basic = 1 + a;

        std::cout << scope << std::endl;
    }

    {
        std::cout << "cout << expression" << std::endl << std::endl;

        scope<recorder> scope;

        batch<int, 2> a{{1, 2}};
        batch<int, 2> b{{2, 4}};

        batch<int, 2> basic;

        std::cout << (a + b) << std::endl;
        std::cout << (a - b) << std::endl;
        std::cout << (a * b) << std::endl;
        std::cout << (a / b) << std::endl;

        std::cout << (a + b * b) << std::endl;
        std::cout << (a * a + b * b) << std::endl;
        std::cout << (a * (a + b) * b) << std::endl;

        std::cout << (basic = a * a + b * b) << std::endl;
        std::cout << (basic = a * (a + b) * b) << std::endl;


        std::cout << scope << std::endl;
    }

    {
        std::cout << "cout << matrix / matrix" << std::endl << std::endl;

        scope<recorder> scope;

        mat<int, 2, 2> a{{1, 2, 3, 4}};
        mat<int, 2, 2> b{{2, 4, 5, 6}};

        mat<int, 2, 2> basic;

        std::cout << (basic = a + b) << std::endl;
        std::cout << (basic = b + a) << std::endl;

        std::cout << (basic = a - b) << std::endl;
        std::cout << (basic = b - a) << std::endl;

        std::cout << (basic = -a) << std::endl;
        std::cout << (basic = -b) << std::endl;

        std::cout << (basic = -(-a)) << std::endl;
        std::cout << (basic = -(-b)) << std::endl;

        std::cout << (basic = +a) << std::endl;
        std::cout << (basic = +b) << std::endl;

        std::cout << scope << std::endl;
    }

    {
        std::cout << "cout << matrix / vector" << std::endl << std::endl;

        scope<recorder> scope;

        mat<int, 2, 2> a{{1, 2, 3, 4}};
        mat<int, 2, 1> b{{2, 4}};

        std::cout << (a + 1) << std::endl;
        std::cout << (a + 2) << std::endl;
        std::cout << (a + 4) << std::endl;

        std::cout << (a - 1) << std::endl;
        std::cout << (a - 2) << std::endl;
        std::cout << (a - 4) << std::endl;

        std::cout << (a * 1) << std::endl;
        std::cout << (a * 2) << std::endl;
        std::cout << (a * 4) << std::endl;

        std::cout << (a / 1) << std::endl;
        std::cout << (a / 2) << std::endl;
        std::cout << (a / 4) << std::endl;

        std::cout << (a + a) << std::endl;
        std::cout << (a - a) << std::endl;
        std::cout << (a * b) << std::endl;

        std::cout << (b.transpose() * a) << std::endl;
        std::cout << (b.transpose() * b) << std::endl;
        std::cout << (b * b.transpose()) << std::endl;


        std::cout << scope << std::endl;
    }

    {
        std::cout << "cout << complex" << std::endl << std::endl;

        scope<recorder> scope;

        complex<float> a{{1, 0}};
        complex<float> b{{1, 1}};
        complex<float> c{{2, 4}};

        std::cout << (a + 2) << std::endl;
        std::cout << (a - 2) << std::endl;
        std::cout << (a * 2) << std::endl;
        std::cout << (a / 2) << std::endl;

        std::cout << (2 + b) << std::endl;
        std::cout << (2 - b) << std::endl;
        std::cout << (2 * b) << std::endl;
        std::cout << (2 / b) << std::endl;

        std::cout << (a + b) << std::endl;
        std::cout << (a - b) << std::endl;
        std::cout << (a * b) << std::endl;
        std::cout << (a / b) << std::endl;


        std::cout << scope << std::endl;
    }

    return 0;
}