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


#pragma once

#include "system/platform.hpp"
#include "system/arch.hpp"
#include "util/algorithm.hpp"
#include "gtest/gtest.h"

namespace zacc { namespace test {

#define ZTRACE_TEST_OUTPUT(cmd) //ZTRACE_INTERNAL(cmd)
#define REQUIRES(raw) \
    do { \
        auto c = zacc::platform::global().match_capabilities(zacc::architectures::raw::value); \
        std::string str; \
        \
        if(c.size() != 0) {\
            str = join(std::begin(c), std::end(c), ", "); \
            ZTRACE_TEST_OUTPUT("[  SKIPPED ] Features [" << str << "] not supported");\
            return;\
        }\
    } while(0)


    template <typename T, typename U>
    std::enable_if_t<std::is_fundamental<T>::value && std::is_convertible<U, T>::value, ::testing::AssertionResult>
    vassert_eq(const char* actual_expr, const char* expected_expr, const T& actual, const U& expected)
    {
        return ::testing::internal::CmpHelperEQ(actual_expr, expected_expr, actual, static_cast<T>(expected));
    }

    template <typename T, typename U>
    std::enable_if_t<is_zval<T>::value && is_integral<T>::value, ::testing::AssertionResult>
    vassert_eq(const char* actual_expr, const char* expected_expr, const T& actual, const U& expected)
    {
        auto actual_dataset = actual.data();
        auto expected_dataset = static_cast<T>(expected).data();

        bool isValid = zacc::accumulate(actual_dataset.begin(), actual_dataset.end(), expected_dataset.begin(), true, [&](auto acc, auto a, auto e){
            return acc && a == e;
        });

//        auto dataset = zip(actual.data(), static_cast<T>(expected).data());
//        element_type_t<T> actual_elem, expected_elem;
//
//        bool isValid = std::accumulate(std::begin(dataset), std::end(dataset), true, [&](auto acc, auto pair)
//        {
//            std::tie(actual_elem, expected_elem) = pair;
//
//            return acc && actual_elem == expected_elem;
//        });

        if(isValid)
            return ::testing::AssertionSuccess();

        return ::testing::AssertionFailure()
                << actual_expr << " and " << expected_expr
                << " (" << actual << " and " << expected << ") are not equal";
    }

    template <typename T, typename U>
    std::enable_if_t<is_zval<T>::value && is_floating_point<T>::value, ::testing::AssertionResult>
    vassert_eq(const char* actual_expr, const char* expected_expr, const T& actual, const U& expected)
    {
        auto actual_dataset = actual.data();
        auto expected_dataset = static_cast<T>(expected).data();

        bool isValid = zacc::accumulate(actual_dataset.begin(), actual_dataset.end(), expected_dataset.begin(), true, [&](auto acc, auto a, auto e){

            const ::testing::internal::FloatingPoint<element_t<T>> lhs(a), rhs(e);

            return acc && lhs.AlmostEquals(rhs);
        });


//        auto dataset = zip(actual.data(), static_cast<T>(expected).data());
//        element_type_t<T> actual_elem, expected_elem;
//
//        bool isValid = std::accumulate(std::begin(dataset), std::end(dataset), true, [&](auto acc, auto pair)
//        {
//            std::tie(actual_elem, expected_elem) = pair;
//
//            const ::testing::internal::FloatingPoint<element_type_t<T>> lhs(actual_elem), rhs(expected_elem);
//
//            return acc && lhs.AlmostEquals(rhs);
//        });

        if(isValid)
            return ::testing::AssertionSuccess();

        return ::testing::AssertionFailure()
                << actual_expr << " and " << expected_expr
                << " (" << actual << " and " << expected << ") are not equal";
    }

    template <typename T, typename U>
    std::enable_if_t<is_bval<T>::value, ::testing::AssertionResult>
    vassert_eq(const char* actual_expr, const char* expected_expr, const T& actual, const U& expected)
    {
        auto actual_dataset = actual.data();
        auto expected_dataset = static_cast<T>(expected).data();

        bool isValid = zacc::accumulate(actual_dataset.begin(), actual_dataset.end(), expected_dataset.begin(), true, [&](auto acc, auto a, auto e){

            return acc && a == e;
        });

//        auto dataset = zip(actual.data(), static_cast<T>(expected).data());
//        element_type_t<T> actual_elem, expected_elem;
//
//        bool isValid = std::accumulate(std::begin(dataset), std::end(dataset), true, [&](auto acc, auto pair)
//        {
//            std::tie(actual_elem, expected_elem) = pair;
//
//            return acc && actual_elem == expected_elem;
//        });

        if(isValid)
            return ::testing::AssertionSuccess();

        return ::testing::AssertionFailure()
                << actual_expr << " and " << expected_expr
                << " (" << actual << " and " << expected << ") are not equal";
    }


    template <typename T, typename U>
    std::enable_if_t<is_floating_point<T>::value /*&& std::is_constructible<T, U>::value*/, ::testing::AssertionResult>
    vexpect_near(const char* actual_expr,
                 const char* expected_expr,
                 const char* abs_error_expr,

                 const T& actual,
                 const U& expected,
                 double abs_error)
    {
        auto actual_dataset = actual.data();
        auto expected_dataset = static_cast<T>(expected).data();

        bool isValid = zacc::accumulate(actual_dataset.begin(), actual_dataset.end(), expected_dataset.begin(), true, [&](auto acc, auto a, auto e){

            return acc && abs_error >= std::abs(a - e);
        });

//        auto dataset = zip(actual.data(), static_cast<T>(expected).data());
//        element_type_t<T> actual_elem, expected_elem;
//
//        bool isValid = std::accumulate(std::begin(dataset), std::end(dataset), true, [&](auto acc, auto pair)
//        {
//            std::tie(actual_elem, expected_elem) = pair;
//
//            return acc && abs_error >= std::abs(actual_elem - expected_elem);
//        });

        if(isValid)
            return ::testing::AssertionSuccess();

        return ::testing::AssertionFailure()
                << "The difference between " << actual_expr << " and " << expected_expr
                << " exceeds " << abs_error_expr << ", where\n"
                << actual_expr << " evaluates to " << actual << ",\n"
                << expected_expr << " evaluates to " << expected << ", and\n"
                << abs_error_expr << " evaluates to " << abs_error << ".";
    }

#define VASSERT_EQ(actual, expected) ASSERT_PRED_FORMAT2(::zacc::test::vassert_eq, actual, expected)
#define VEXPECT_EQ(actual, expected) EXPECT_PRED_FORMAT2(::zacc::test::vassert_eq, actual, expected)
#define VASSERT_NEAR(actual, expected, abs_error) ASSERT_PRED_FORMAT3(::zacc::test::vexpect_near, actual, expected, abs_error)
#define VEXPECT_NEAR(actual, expected, abs_error) EXPECT_PRED_FORMAT3(::zacc::test::vexpect_near, actual, expected, abs_error)

}}
