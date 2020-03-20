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

#include <zacc/compute/compute.hpp>
#include <functional>

using namespace zacc;
using namespace zacc::compute;

auto krnl(var<int> a, var<int> b, var<int> c)
{
    return 2 * a * b + c;
}

int main(int argc, char** argv)
{

    //return krnl(1, 2, 3)();

    //print(krnl(1, 2, 3));

    var a { 2 };
    var b { 3 };
    var c { 4 };

    {
        print(a);
        print(a + 1);
    }

    {
        auto d = a + b;

        print(d);

        std::cout << print_expr(d) << " = " << builder(d).build(scalar{})() << std::endl;
    }

    {
        auto d = a - b;

        print(d);

        std::cout << print_expr(d) << " = " << builder(d).build(scalar{})() << std::endl;
    }

    {
        auto d = a * b;

        print(d);

        std::cout << print_expr(d) << " = " << builder(d).build(scalar{})() << std::endl;
    }

    {
        auto d = a * b - c;

        print(d);

        std::cout << print_expr(d) << " = " << builder(d).build(scalar{})() << std::endl;
    }

//    {
//        auto d = a * b + c;
//
//        print(d);
//
//        auto e = a * 2 * b + c;
//
//        print(e);
//
//        auto f = when(a)
//            .then(b)
//            .otherwise(c);
//
//        std::cout << print_expr(f) << " = " << builder(f).build(scalar{})() << std::endl;
//    }

//    {
//        auto d = (a * b + c);
//        std::cout << print_expr(d) << " = " << builder(d).build(scalar{})() << std::endl;
//
//        auto e = (a + b * c);
//        std::cout << print_expr(e) << " = " << builder(e).build(scalar{})() << std::endl;
//
//        auto f = 1 + (a * b + c) * (a * b + c);
//        std::cout << print_expr(f) << " = " << builder(f).build(scalar{})() << std::endl;
//    }




    //std::cout << print_expr(builder(g).build(scalar{})) << std::endl;
    //print(g);
//
//    auto d = a * 2 * b + c;
//
//    std::cout << print_expr(d) << std::endl;
//
//    auto x = d;
//    std::cout << print_expr(x) << std::endl;
//
//    print(d);
//    print(x);
//
//    expression z = d * x;
//    std::cout << print_expr(z) << std::endl;
//
////    c = d;
//
//    print(z);
//
//    print(c);
//
//    std::cout << print_expr(c) << std::endl;

//    var<int> y = d;


//    {
//        a,
//        b
//    };

    //static_assert(!is_expression_v<initializer<batch<int, 4>>>, "");

//    {
//        std::cout << "arithmetic" << std::endl << std::endl;
//        evaluator<>::policy(scalar_policy<>{});
//
//        scope<recorder> scope;
//
//        batch<int, 2> a{{1, 2}};
//        batch<int, 2> b{{2, 4}};
//
//        std::cout << a << " + " << b << " = " << (a + b) << std::endl;
//        std::cout << b << " + " << a << " = " << (b + a) << std::endl;
//
//        std::cout << a << " - " << b << " = " << (a - b) << std::endl;
//        std::cout << b << " - " << a << " = " << (b - a) << std::endl;
//
//        std::cout << a << " * " << b << " = " << (a * b) << std::endl;
//        std::cout << b << " * " << a << " = " << (b * a) << std::endl;
//
//        std::cout << a << " / " << b << " = " << (a / b) << std::endl;
//        std::cout << b << " / " << a << " = " << (b / a) << std::endl;
//
//        std::cout << a << " % " << b << " = " << (a % b) << std::endl;
//        std::cout << b << " % " << a << " = " << (b % a) << std::endl;
//
//        std::cout << "-" << a << " = " << (-a) << std::endl;
//        std::cout << "-" << b << " = " << (-b) << std::endl;
//
//        std::cout << "(-(-" << a << "))" << " = " << (-(-a)) << std::endl;
//        std::cout << "(-(-" << b << "))" << " = " << (-(-b)) << std::endl;
//
//        std::cout << "+" << a << " = " << (+a) << std::endl;
//        std::cout << "+" << b << " = " << (+b) << std::endl;
//
//        std::cout << scope << std::endl;
//    }
//
//    {
//        std::cout << "fma" << std::endl << std::endl;
//
//        scope<recorder> scope;
//
//        batch<int, 2> a{{1, 2}};
//        batch<int, 2> b{{2, 4}};
//        batch<int, 2> c{{3, 6}};
//        batch<int, 2> d{{4, 8}};
//
//        batch<int, 2> fma;
//
//        fma = a + b * c;
//        fma = a * b + c;
//        fma = a * a + b * b;
//        fma = a * a - b * b;
//        fma = a * a + b * b + c * c;
//        fma = a * a - b * b + c * c;
//
//        std::cout << scope << std::endl;
//    }
//
//    {
//        std::cout << "comparisons" << std::endl << std::endl;
//
//        scope<recorder> scope;
//
//        batch<int, 2> a{{1, 2}};
//        batch<int, 2> b{{2, 2}};
//
//        batch<bool, 2> basic;
//
//        basic = a == b;
//        basic = b == a;
//
//        basic = a != b;
//        basic = b != a;
//
//        basic = a > b;
//        basic = b > a;
//
//        basic = a < b;
//        basic = b < a;
//
//        basic = a >= b;
//        basic = b >= a;
//
//        basic = a <= b;
//        basic = b <= a;
//
//        std::cout << scope << std::endl;
//    }
//
//    {
//        std::cout << "logical operations" << std::endl << std::endl;
//
//        scope<recorder> scope;
//
//        batch<bool, 2> a{{ false, true}};
//        batch<bool, 2> b{{ true, true }};
//
//        batch<bool, 2> basic;
//
//        basic = a && b;
//        basic = b && a;
//
//        basic = a || b;
//        basic = b || a;
//
//        basic = !a;
//        basic = !b;
//
//        basic = !(!a);
//        basic = !(!b);
//
//        std::cout << scope << std::endl;
//    }
//
//    {
//        std::cout << "cast" << std::endl << std::endl;
//
//        scope<recorder> scope;
//
//        batch<int, 2> a{{1, 2}};
//        batch<int, 2> b{{2, 4}};
//
//        batch<int, 2> basic;
//
//        basic = a + 1;
//        //basic = 1 + a;
//
//        std::cout << scope << std::endl;
//    }
//
//    {
//        std::cout << "cout << expression" << std::endl << std::endl;
//
//        scope<recorder> scope;
//
//        batch<int, 2> a{{1, 2}};
//        batch<int, 2> b{{2, 4}};
//
//        batch<int, 2> c{{3, 6}};
//
//        std::cout << (a + b) << std::endl;
//        std::cout << (a - b) << std::endl;
//        std::cout << (a * b) << std::endl;
//        std::cout << (a / b) << std::endl;
//
//        std::cout << (a + b * b) << std::endl;
//        std::cout << (a * a + b * b) << std::endl;
//        std::cout << (a * (a + b) * b) << std::endl;
//
//
//        std::cout << (c = a * a + b * b) << std::endl;
//        std::cout << (c = a * (a + b) * b) << std::endl;
//
//        auto expr = a * a + b / 2;//(a * (a + b) * b);
//
//        std::cout << scope << std::endl;
//    }
//
//
//    {
//        std::cout << "sse test" << std::endl << std::endl;
//
//        scope<recorder> scope;
//
//        batch<int, 4> a{{1, 2, 3, 4}};
//        batch<int, 4> b{{2, 3, 4, 5}};
//
//        std::cout << (a + b) << std::endl;
//
//        std::cout << scope << std::endl;
//    }
//
//    {
//        std::cout << "cout << matrix / matrix" << std::endl << std::endl;
//
//        scope<recorder> scope;
//
//        mat<int, 2, 2> a{{1, 2, 3, 4}};
//        mat<int, 2, 2> b{{2, 4, 5, 6}};
//
//        mat<int, 2, 2> basic;
//
//        std::cout << (basic = a + b) << std::endl;
//        std::cout << (basic = b + a) << std::endl;
//
//        std::cout << (basic = a - b) << std::endl;
//        std::cout << (basic = b - a) << std::endl;
//
//        std::cout << (basic = -a) << std::endl;
//        std::cout << (basic = -b) << std::endl;
//
//        std::cout << (basic = -(-a)) << std::endl;
//        std::cout << (basic = -(-b)) << std::endl;
//
//        std::cout << (basic = +a) << std::endl;
//        std::cout << (basic = +b) << std::endl;
//
//        std::cout << scope << std::endl;
//    }
//
//    {
//        std::cout << "cout << matrix / vector" << std::endl << std::endl;
//
//        scope<recorder> scope;
//
//        mat<int, 2, 2> a{{1, 2, 3, 4}};
//        mat<int, 2, 1> b{{2, 4}};
//
//        std::cout << (a + 1) << std::endl;
//        std::cout << (a + 2) << std::endl;
//        std::cout << (a + 4) << std::endl;
//
//        std::cout << (a - 1) << std::endl;
//        std::cout << (a - 2) << std::endl;
//        std::cout << (a - 4) << std::endl;
//
//        std::cout << (a * 1) << std::endl;
//        std::cout << (a * 2) << std::endl;
//        std::cout << (a * 4) << std::endl;
//
//        std::cout << (a / 1) << std::endl;
//        std::cout << (a / 2) << std::endl;
//        std::cout << (a / 4) << std::endl;
//
//        std::cout << (a + a) << std::endl;
//        std::cout << (a - a) << std::endl;
//        std::cout << (a * b) << std::endl;
//
//        std::cout << (b.transpose() * a) << std::endl;
//        std::cout << (b.transpose() * b) << std::endl;
//        std::cout << (b * b.transpose()) << std::endl;
//
//
//        std::cout << scope << std::endl;
//    }
//
//    {
//        std::cout << "cout << complex" << std::endl << std::endl;
//
//        scope<recorder> scope;
//
//        complex<float> a{{1, 0}};
//        complex<float> b{{1, 1}};
//        complex<float> c{{2, 4}};
//
//        std::cout << (a + 2) << std::endl;
//        std::cout << (a - 2) << std::endl;
//        std::cout << (a * 2) << std::endl;
//        std::cout << (a / 2) << std::endl;
//
//        std::cout << (2 + b) << std::endl;
//        std::cout << (2 - b) << std::endl;
//        std::cout << (2 * b) << std::endl;
//        std::cout << (2 / b) << std::endl;
//
//        std::cout << (a + b) << std::endl;
//        std::cout << (a - b) << std::endl;
//        std::cout << (a * b) << std::endl;
//        std::cout << (a / b) << std::endl;
//
//
//        std::cout << scope << std::endl;
//    }

    return 0;
}