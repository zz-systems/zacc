//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2019 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

namespace zacc { namespace compute {

    // =================================================================================================================

    template<typename T>
    struct complex : variable<complex<T>>
    {
        using value_type = T;
        constexpr static auto dim = std::make_tuple(2);

        // =============================================================================================================

        constexpr complex()
            : variable<complex>()
        {}

        constexpr complex(std::initializer_list<T> init_list)
            : variable<complex>()
        {
            std::copy(std::begin(init_list), std::end(init_list), std::begin(_data));
        }

        // =============================================================================================================

        constexpr auto real() { return _data[0]; }
        constexpr auto real() const { return _data[0]; }

        constexpr auto imag() { return _data[1]; }
        constexpr auto imag() const { return _data[1]; }

        // =============================================================================================================

        constexpr auto begin() { return _data.begin(); }
        constexpr auto begin() const { return _data.begin(); }

        constexpr auto end() { return _data.end(); }
        constexpr auto end() const { return _data.end(); }

    private:
        alignas(T) typename container<T, 2>::type _data;
    };

    // =================================================================================================================
    // Tags
    // =================================================================================================================

    // =================================================================================================================
    // ARITHMETIC
    // =================================================================================================================

    struct complex_op : operator_base
    {};

    // =================================================================================================================

    struct complex_identity_op : complex_op, identity_op
    {};

    struct complex_add_op : complex_op, add_op
    {};

    struct scalar_complex_add_op : complex_op, add_op
    {};

    struct complex_scalar_add_op : complex_op, add_op
    {};

    struct complex_promote_op : complex_op, promote_op
    {};

    struct complex_sub_op : complex_op, sub_op
    {};

    struct scalar_complex_sub_op : complex_op, sub_op
    {};

    struct complex_scalar_sub_op : complex_op, sub_op
    {};

    struct complex_mul_op : complex_op, mul_op
    {};

    struct complex_scalar_mul_op : complex_op, mul_op
    {};

    struct complex_div_op : complex_op, div_op
    {};

    struct complex_scalar_div_op : complex_op, div_op
    {};

    struct complex_neg_op : complex_op, neg_op
    {};

    // =================================================================================================================
    // COMPARISON
    // =================================================================================================================

    struct complex_equal_to_op : complex_op, equal_to_op
    {};

    struct complex_not_equal_to_op : complex_op, not_equal_to_op
    {};

}}