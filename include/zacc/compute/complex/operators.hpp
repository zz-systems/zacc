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
    // Operators
    // =================================================================================================================

    // =================================================================================================================
    // ARITHMETIC
    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_complex_complex_expr<Left, Right>::value>* = nullptr>
    auto operator+(Left&& left, Right&& right)
    {
        return expression<complex_add_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    template<typename Left, typename Right,
        std::enable_if_t<is_scalar_complex_expr<Left, Right>::value>* = nullptr>
    auto operator+(Left&& left, Right&& right)
    {
        return expression<scalar_complex_add_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    template<typename Left, typename Right,
        std::enable_if_t<is_complex_scalar_expr<Left, Right>::value>* = nullptr>
    auto operator+(Left&& left, Right&& right)
    {
        return expression<complex_scalar_add_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_complex_complex_expr<Left, Right>::value>* = nullptr>
    auto operator-(Left&& left, Right&& right)
    {
        return expression<complex_sub_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    template<typename Left, typename Right,
        std::enable_if_t<is_scalar_complex_expr<Left, Right>::value>* = nullptr>
    auto operator-(Left&& left, Right&& right)
    {
        return expression<scalar_complex_sub_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    template<typename Left, typename Right,
        std::enable_if_t<is_complex_scalar_expr<Left, Right>::value>* = nullptr>
    auto operator-(Left&& left, Right&& right)
    {
        return expression<complex_scalar_sub_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_complex_complex_expr<Left, Right>::value>* = nullptr>
    auto operator*(Left&& left, Right&& right)
    {
        return expression<complex_mul_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    template<typename Left, typename Right,
    std::enable_if_t<is_complex_scalar_expr<Left, Right>::value>* = nullptr>
    auto operator*(Left&& left, Right&& right)
    {
        return expression<complex_scalar_mul_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
    std::enable_if_t<
        is_complex_complex_expr<Left, Right>::value>* = nullptr>
    auto operator/(Left&& left, Right&& right)
    {
        return expression<complex_div_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    template<typename Left, typename Right,
        std::enable_if_t<is_complex_scalar_expr<Left, Right>::value>* = nullptr>
    auto operator/(Left&& left, Right&& right)
    {
        return expression<complex_scalar_div_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Right,
        std::enable_if_t<is_complex<Right>::value>* = nullptr>
    auto operator-(Right&& right)
    {
        return expression<complex_neg_op, Right>(std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Right,
        std::enable_if_t<is_complex<Right>::value>* = nullptr>
    auto operator+(Right&& right)
    {
        return expression<complex_promote_op, Right>(std::forward<Right>(right));
    }

    // =================================================================================================================
    // COMPARISON
    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_complex_complex_expr<Left, Right>::value>* = nullptr>
    auto operator==(Left&& left, Right&& right)
    {
        return expression<complex_equal_to_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_complex_complex_expr<Left, Right>::value>* = nullptr>
    auto operator!=(Left&& left, Right&& right)
    {
        return expression<complex_not_equal_to_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Right,
        std::enable_if_t<is_complex<Right>::value>* = nullptr>
    std::ostream& operator<<(std::ostream& os, Right&& rhs)
    {
        os  << execution_context::current().execute(std::forward<Right>(rhs), 0)
            << " + "
            << execution_context::current().execute(std::forward<Right>(rhs), 1)
            << "i";

        return os;
    }

    // =================================================================================================================

}}