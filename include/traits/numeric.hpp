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

#include "common.hpp"
#include <type_traits>
#include <limits>

namespace zacc { namespace traits {

    /**
     * @brief provides numeric value definitions, fluent interface
     * @tparam base_t base type (e.g previous trait)
     * @tparam composed_t final composed type (e.g zfloat32)
     */
    template<typename base_t, typename composed_t>
    struct numeric : public base_t {
        FORWARD(numeric);

        /**
         * @brief NaN value
         * @see std::numeric_limits
         * @return NaN
         */
        static constexpr composed_t quiet_NaN() noexcept {
            return std::numeric_limits<typename base_t::scalar_t>::quiet_NaN();
        };

        /**
         * @brief is the current value infinite?
         * @return true if infinite
         */
        composed_t is_infinite() const noexcept {
            return (*this) == infinity();
        };

        /**
         * @brief infinity value
         * @see std::numeric_limits
         * @return infinity
         */
        static constexpr composed_t infinity() noexcept {
            return std::numeric_limits<typename base_t::scalar_t>::infinity();
        };

        /**
         * @brief minimum value for current type
         * @see std::numeric_limits
         * @return minimum value
         */
        static constexpr composed_t min() noexcept {
            return std::numeric_limits<typename base_t::scalar_t>::min();
        }

        /**
         * @brief maximum value for current type
         * @see std::numeric_limits
         * @return maximum value
         */
        static constexpr composed_t max() noexcept {
            return std::numeric_limits<typename base_t::scalar_t>::max();
        }
    };
}}