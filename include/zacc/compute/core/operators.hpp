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

namespace zacc::compute {

    // =================================================================================================================

    struct operator_base
    {
        constexpr operator_base() = default;
    };

    // =================================================================================================================

    template<typename = void, typename...>
    struct select_op : operator_base
    {};

    template<typename = void, typename...>
    struct call_op : operator_base
    {};

    template<typename = void, typename...>
    struct init_op : operator_base
    {};

    template<typename = void, typename...>
    struct assign_op : operator_base
    {};

    // =================================================================================================================
    // ARITHMETIC
    // =================================================================================================================

    struct arithmetic_op : operator_base
    {};

    // =================================================================================================================

    template<typename = void, typename...>
    struct identity_op : arithmetic_op
    {};

    template<typename = void, typename...>
    struct add_op : arithmetic_op
    {};

    template<typename = void, typename...>
    struct promote_op : arithmetic_op
    {};

    template<typename = void, typename...>
    struct sub_op : arithmetic_op
    {};

    template<typename = void, typename...>
    struct mul_op : arithmetic_op
    {};

    template<typename = void, typename...>
    struct div_op : arithmetic_op
    {};

    template<typename = void, typename...>
    struct mod_op : arithmetic_op
    {};

    template<typename = void, typename...>
    struct neg_op : arithmetic_op
    {};

    // =================================================================================================================
    // COMPARISON
    // =================================================================================================================

    struct comparison_op : operator_base
    {};

    // =================================================================================================================

    template<typename = void, typename...>
    struct equal_to_op : comparison_op
    {};

    template<typename = void, typename...>
    struct not_equal_to_op : comparison_op
    {};

    template<typename = void, typename...>
    struct greater_op : comparison_op
    {};

    template<typename = void, typename...>
    struct less_op : comparison_op
    {};

    template<typename = void, typename...>
    struct greater_equal_op : comparison_op
    {};

    template<typename = void, typename...>
    struct less_equal_op : comparison_op
    {};

    // =================================================================================================================
    // BOOLEAN
    // =================================================================================================================

    struct bool_op : operator_base
    {};

    // =================================================================================================================

    template<typename = void, typename...>
    struct bool_and_op : bool_op
    {};

    template<typename = void, typename...>
    struct bool_or_op : bool_op
    {};

    template<typename = void, typename...>
    struct bool_not_op : bool_op
    {};

    // =================================================================================================================
    // BITWISE
    // =================================================================================================================

    struct bitwise_op : operator_base
    {};

    // =================================================================================================================

    template<typename = void, typename...>
    struct bit_and_op : bitwise_op
    {};

    template<typename = void, typename...>
    struct bit_or_op : bitwise_op
    {};

    template<typename = void, typename...>
    struct bit_xor_op : bitwise_op
    {};

    template<typename = void, typename...>
    struct bit_not_op : bitwise_op
    {};

    template<typename = void, typename...>
    struct bit_shl_op : bitwise_op
    {};

    template<typename = void, typename...>
    struct bit_shr_op : bitwise_op
    {};

    // =================================================================================================================
    // OTHER
    // =================================================================================================================

    template<typename = void, typename...>
    struct fmadd_op : operator_base
    {};

    template<typename = void, typename...>
    struct fmsub_op : operator_base
    {};

    // =================================================================================================================
}