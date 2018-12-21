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

namespace zacc { namespace traits {

    /**
     * @brief provides basic math function definitions, fluent interface
     * @tparam Base base type (e.g previous trait)
     * @tparam Composed final composed type (e.g zfloat32)
     */
    template<typename Impl, typename Base, typename Interface, typename Composed, typename Boolean>
    struct math :
        public Impl,
        public Base
    {
        constexpr auto self() const
        {
            return static_cast<const Composed*>(this);
        }

        /**
         * @brief absoulute value
         * @return |value|
         */
        Composed abs() const noexcept {
            return vabs(*self());
        }

        Composed max(const Composed other) const noexcept {
            return vmax(*self(), other);
        }

        Composed min(const Composed other) const noexcept {
            return vmin(*self(), other);
        }

        Composed clamp(const Composed from, const Composed to) const noexcept {
            return vclamp(*self(), from, to);
        }

        /**
         * @brief inverse value
         * @return 1 / value
         */
        Composed rcp() const noexcept {
            return vrcp(*self());
        }

        /**
         * @brief truncated value (integer part of a floating value)
         * @return 1.654743 -> 1.0
         */
        Composed trunc() const noexcept {
            return vtrunc(*self());
        }

        /**
         * @brief round down
         * @return 1.6 -> 1.0
         */
        Composed floor() const noexcept {
            return vfloor(*self());
        }

        /**
         * @brief round up
         * @return 1.4 -> 2.0
         */
        Composed ceil() const noexcept {
            return vceil(*self());
        }

        /**
         * @brief round to nearest integer
         * @return 1.6 -> 2.0; 1.4 -> 1.0
         */
        Composed round() const noexcept {
            return vround(*self());
        }

        /**
         * @brief pow
         * @return value ^ exponent
         */
        Composed pow(const Composed exponent) const noexcept {
            return vpow(*self(), exponent);
        }

        /**
         * @brief square root
         * @return sqrt(value)
         */
        Composed sqrt() const noexcept {
            return vsqrt(*self());
        }
    };
}}