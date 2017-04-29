//---------------------------------------------------------------------------------
// The MIT License (MIT)
// 
// Copyright (c) 2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

#include <cmath>
#include "math/common.hpp"
#include "system/branch.hpp"

namespace zacc { namespace math {

        /**
         * @brief  Sine function. Algorithm taken from SLEEF 2.80 and vecmathlib
         * @tparam type [zfloat, zdouble]
         * @param val [-pi; pi] rad
         * @return [-1; 1]
         */
        template<typename vreal_t>
        std::enable_if_t<is_floating_point<vreal_t>::value && !vreal_t::dispatcher::has_integer_types, vreal_t> vsin(vreal_t val)
        {
            auto vv = val.data();

            alignas(vreal_t::alignment) typename vreal_t::extracted_t raw_result;

            for(auto i = 0; i < vreal_t::dim; i++)
            {
                raw_result[i] = std::sin(vv[i]);
            }

            return raw_result;
        }

        /**
         * @brief  Cosine function. Algorithm taken from SLEEF 2.80 and vecmathlib
         * @tparam type [zfloat, zdouble]
         * @param val [-pi; pi] rad
         * @return [-1; 1]
         */
        template<typename vreal_t>
        std::enable_if_t<is_floating_point<vreal_t>::value && !vreal_t::dispatcher::has_integer_types, vreal_t> vcos(vreal_t val)
        {
            auto vv = val.data();

            alignas(vreal_t::alignment) typename vreal_t::extracted_t raw_result;

            for(auto i = 0; i < vreal_t::dim; i++)
            {
                raw_result[i] = std::cos(vv[i]);
            }

            return raw_result;
        }

        /**
         * @brief  Tangens function. Algorithm taken from SLEEF 2.80 and vecmathlib
         * @tparam type [zfloat, zdouble]
         * @param val [-pi/2; pi/2] rad
         * @return [-1; 1]
         */
        template <typename vreal_t>
        std::enable_if_t<is_floating_point<vreal_t>::value && !vreal_t::dispatcher::has_integer_types, vreal_t> vtan(vreal_t val)
        {
            auto vv = val.data();

            alignas(vreal_t::alignment) typename vreal_t::extracted_t raw_result;

            for(auto i = 0; i < vreal_t::dim; i++)
            {
                raw_result[i] = std::tan(vv[i]);
            }

            return raw_result;
        }

        /**
         * @brief  Cosine function. Algorithm taken from SLEEF 2.80 and vecmathlib
         * @tparam type [zfloat, zdouble]
         * @param val [-1; 1] rad
         * @return [-1; 1]
         */
        template<typename vreal_t>
        std::enable_if_t<is_floating_point<vreal_t>::value && !vreal_t::dispatcher::has_integer_types, vreal_t> vatan2(vreal_t y, vreal_t x)
        {
            auto xx = x.data();
            auto yy = y.data();

            alignas(vreal_t::alignment) typename vreal_t::extracted_t raw_result;

            for(auto i = 0; i < vreal_t::dim; i++)
                raw_result[i] = std::atan2(yy[i], xx[i]);

            return raw_result;
        }
    }}