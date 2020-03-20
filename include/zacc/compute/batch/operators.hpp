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

//    template<typename L, typename R, std::size_t... Is>
//    auto operator+(batch<L, Is...> left, batch<R, Is...> right)
//        -> make_expression<batch_expression, add_op, batch<L, Is...>, batch<R, Is...>>
//    {
//        return {left, right};
//    }
//
//    template<typename L, typename R, std::size_t... Is>
//    auto operator+(batch<L, Is...> left, literal<R> right)
//        -> std::enable_if_t<std::is_arithmetic<R>::value,
//            make_expression<batch_expression, add_op, batch<L, Is...>, literal<R>>>
//    {
//        return {left, right};
//    }
//
//    template<typename L, typename R, std::size_t... Is>
//    auto operator+(literal<L> left, batch<R, Is...> right)
//        -> std::enable_if_t<std::is_arithmetic<L>::value,
//            make_expression<batch_expression, add_op, literal<L>, batch<R, Is...>>>
//    {
//        return {left, right};
//    }

    static_assert(std::is_same<literal<int>, expression_cast<literal<int>>>::value, "");
    static_assert(std::is_same<literal<int>, expression_cast<int>>::value, "");
    static_assert(std::is_same<expression<int, int, int>, expression_cast<expression<int, int, int>>>::value, "");
    static_assert(std::is_same<batch<int, 2>, expression_cast<batch<int, 2>>>::value, "");


    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator+(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, add_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator-(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, sub_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator*(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, mul_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator/(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, div_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator%(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, mod_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Right,
        std::enable_if_t<is_batch_v<Right> || is_batch_v<result_of_t<Right>>>* = nullptr>
    auto operator-(Right&& right)
    {
        return make_expression<batch_expression, neg_op>(std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Right,
        std::enable_if_t<is_batch_v<Right> || is_batch_v<result_of_t<Right>>>* = nullptr>
    auto operator+(Right&& right)
    {
        return make_expression<batch_expression, promote_op>(std::forward<Right>(right));
    }

    // =================================================================================================================
    // COMPARISON
    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator==(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, equal_to_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator!=(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, not_equal_to_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator>(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, greater_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator<(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, less_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator>=(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, greater_equal_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator<=(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, less_equal_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================
    // BOOLEAN
    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator&&(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, bool_and_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator||(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, bool_or_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Right,
        std::enable_if_t<is_batch_v<Right> || is_batch_v<result_of_t<Right>>>* = nullptr>
    auto operator!(Right&& right)
    {
        return make_expression<batch_expression, bool_not_op>(std::forward<Right>(right));
    }

    // =================================================================================================================
    // BITWISE
    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator&(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, bit_and_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator|(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, bit_or_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator^(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, bit_xor_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator<<(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, bit_shl_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Left, typename Right,
        std::enable_if_t<is_batch_expr<Left, Right>::value>* = nullptr>
    auto operator>>(Left&& left, Right&& right)
    {
        return make_expression<batch_expression, bit_shr_op>(std::forward<Left>(left), std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Right,
        std::enable_if_t<is_batch_v<Right> || is_batch_v<result_of_t<Right>>>* = nullptr>
    auto operator~(Right&& right)
    {
        return make_expression<batch_expression, bit_not_op>(std::forward<Right>(right));
    }

    // =================================================================================================================

    template<typename Right,
        std::enable_if_t<is_batch_v<Right> || is_batch_v<result_of_t<Right>>>* = nullptr>
    std::ostream& operator<<(std::ostream& os, Right&& rhs)
    {
        os << "[ ";

        for(auto i : make_iterator(std::forward<Right>(rhs)))
        {
            os  << i << " ";
        }

//        eval(std::forward<Right>(rhs), [&os](auto const& i){
//            os  << i << " ";
//        });

        os << "]";

        return os;
    }

    // =================================================================================================================
}}