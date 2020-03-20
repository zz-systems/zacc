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

#include <zacc/compute/core/operators.hpp>

namespace zacc { namespace compute {

    // =================================================================================================================
    // Operators
    // =================================================================================================================

    // =================================================================================================================
    // ARITHMETIC
    // =================================================================================================================

    template<typename Left, typename Right,
    std::enable_if_t<
        disjunction<
            is_matrix_matrix_expr<Left, Right>,
            is_scalar_matrix_expr<expression_cast<Left>, Right>,
            is_matrix_scalar_expr<Left, expression_cast<Right>>
        >::value>* = nullptr>
    auto operator+(Left&& left, Right&& right)
    {
        return expression<matrix_add_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
    std::enable_if_t<
        disjunction<
            is_matrix_matrix_expr<Left, Right>,
            is_scalar_matrix_expr<expression_cast<Left>, Right>,
            is_matrix_scalar_expr<Left, expression_cast<Right>>
        >::value>* = nullptr>
    auto operator-(Left&& left, Right&& right)
    {
        return expression<matrix_sub_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
    std::enable_if_t<
        disjunction<
            is_matrix_matrix_mul_expr<Left, Right>,
            is_row_vector_matrix_expr<Left, Right>,
            is_matrix_col_vector_expr<Left, Right>,
            is_row_col_vector_expr<Left, Right>,
            is_col_row_vector_expr<Left, Right>
        >::value>* = nullptr>
    auto operator*(Left&& left, Right&& right)
    {
        return expression<matrix_mul_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    template<typename Left, typename Right,
    std::enable_if_t<
        disjunction<
            is_matrix_scalar_expr<Left, Right>,
            is_scalar_matrix_expr<Left, Right>
        >::value>* = nullptr>
    auto operator*(Left&& left, Right&& right)
    {
        return expression<matrix_scalar_mul_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<
            disjunction<
            is_matrix_scalar_expr<Left, Right>,
        is_scalar_matrix_expr<Left, Right>
        >::value>* = nullptr>
    auto operator/(Left&& left, Right&& right)
    {
        return expression<matrix_scalar_div_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Right,
        std::enable_if_t<is_matrix<Right>::value>* = nullptr>
    auto operator-(Right&& right)
    {
        return expression<matrix_neg_op, Right>(std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Right,
        std::enable_if_t<is_matrix<Right>::value>* = nullptr>
    auto operator+(Right&& right)
    {
        return expression<matrix_promote_op, Right>(std::forward<Right>(right));
    }

    // =================================================================================================================
    // COMPARISON
    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_matrix_matrix_expr<Left, Right>::value>* = nullptr>
    auto operator==(Left&& left, Right&& right)
    {
        return expression<matrix_equal_to_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_matrix_matrix_expr<Left, Right>::value>* = nullptr>
    auto operator!=(Left&& left, Right&& right)
    {
        return expression<matrix_not_equal_to_op, Left, Right>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Right, typename std::enable_if_t<is_matrix<Right>::value>* = nullptr>
    std::ostream& operator<<(std::ostream& os, Right&& rhs)
    {
        os << "[ ";

        for(auto i : execution_context::current().execute(std::forward<Right>(rhs)))
        {
            os  << i << " ";
        }

        os << "]";

        return os;
    }

    // =================================================================================================================

}}