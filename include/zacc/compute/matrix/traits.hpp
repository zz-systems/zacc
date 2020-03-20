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

#include <type_traits>

namespace zacc { namespace compute {

    // =================================================================================================================

    template<typename, size_t, size_t>
    struct mat;

    template<typename, typename...>
    struct __expression;

    template<typename, typename...>
    struct expression;

    template<typename>
    struct literal;

    template<typename>
    struct is_expression;

    template<typename>
    struct is_literal;

    template<typename...>
    struct conjunction;

    template<typename...>
    struct disjunction;

    template<typename...>
    struct common_type;

    template<typename>
    struct rank;

    template<typename, std::size_t>
    struct extent;

    // =================================================================================================================

    template<typename T>
    struct is_matrix;

    // =================================================================================================================

    template<typename T, size_t... Is>
    struct expression<mat<T, Is...>>
        : __expression<mat<T, Is...>>
    {
        using __expression<mat<T, Is...>>::operator_type;
        using __expression<mat<T, Is...>>::operands_type;
        using __expression<mat<T, Is...>>::__expression;

        using return_type = mat<T, Is...>;
    };

    template<typename T, size_t... Is>
    struct __is_expression<mat<T, Is...>>
        : std::true_type
    {};

    template<typename = void>
    struct __is_matrix
        : std::false_type
    {};

//    template<typename T>
//    struct __is_matrix
//        : std::true_type
//    {};

    template<typename T, size_t... Is>
    struct __is_matrix<mat<T, Is...>>
        : std::true_type
    {};

    template<typename T>
    struct is_matrix
        : __is_matrix<std::remove_reference_t<T>>
    {};

    template<typename T>
    constexpr bool is_matrix_v = is_matrix<T>::value;

    template<typename T>
    struct __is_row_vector
        : std::integral_constant<bool,
            is_matrix<T>::value
            && extent<T, 0>::value == 1
            && (extent<T, 1>::value > 1)>
    {};

    template<typename T>
    struct is_row_vector
        : __is_row_vector<std::remove_reference_t<T>>
    {};

    template<typename T>
    struct __is_col_vector
        : std::integral_constant<bool,
            is_matrix<T>::value
            && (extent<T, 0>::value > 1)
            && extent<T, 1>::value == 1>
    {};

    template<typename T>
    struct is_col_vector
        : __is_col_vector<std::remove_reference_t<T>>
    {};

    template<typename T>
    struct __is_vector
        : std::integral_constant<bool,
            is_row_vector<T>::value
            || is_col_vector<T>::value>
    {};

    template<typename T>
    struct is_vector
        : __is_vector<std::remove_reference_t<T>>
    {};

    template<typename T>
    struct __is_square_matrix
        : std::integral_constant<bool,
            is_matrix<T>::value
            && extent<T, 0>::value == extent<T, 1>::value
            && (extent<T, 0>::value > 1)>
    {};

    template<typename T>
    struct is_square_matrix
        : __is_square_matrix<std::remove_reference_t<T>>
    {};

    // =================================================================================================================

    template<typename T, size_t... Is>
    struct __rank<mat<T, Is...>>
        : std::integral_constant<size_t, sizeof...(Is)>
    {};

    // =================================================================================================================

    template<typename T, std::size_t N, std::size_t... Is>
    struct __extent<mat<T, Is...>, N>
        : std::integral_constant<size_t, std::get<N>(std::make_tuple(Is...))>
    {};

    // =================================================================================================================

    template<typename... Ts, size_t... Is>
    struct __common_type<void, mat<Ts, Is...>...>
    {
        using type = common_type<Ts...>;
    };

    // =================================================================================================================

    template<typename Left, typename Right>
    struct __is_row_col_vector_expr
        : std::integral_constant<bool,
            is_row_vector<Left>::value
            && is_col_vector<Right>::value
        >
    {};

    template<typename Left, typename Right>
    struct is_row_col_vector_expr
        : __is_row_col_vector_expr<std::remove_reference_t<Left>, std::remove_reference_t<Right>>
    {};

    template<typename Left, typename Right>
    struct __is_col_row_vector_expr
        : std::integral_constant<bool,
            is_col_vector<Left>::value
            && is_row_vector<Right>::value
        >
    {};

    template<typename Left, typename Right>
    struct is_col_row_vector_expr
        : __is_col_row_vector_expr<std::remove_reference_t<Left>, std::remove_reference_t<Right>>
    {};

    template<typename Left, typename Right>
    struct __is_matrix_col_vector_expr
        : std::integral_constant<bool,
            is_matrix<Left>::value && is_col_vector<Right>::value
            && extent<Left, 1>::value == extent<Right, 0>::value
            && (extent<Left, 0>::value > 1)
        >
    {};

    template<typename Left, typename Right>
    struct is_matrix_col_vector_expr
        : __is_matrix_col_vector_expr<std::remove_reference_t<Left>, std::remove_reference_t<Right>>
    {};

    template<typename Left, typename Right>
    struct __is_row_vector_matrix_expr
        : std::integral_constant<bool,
            is_row_vector<Left>::value && is_matrix<Right>::value
            && extent<Left, 1>::value == extent<Right, 0>::value
            && (extent<Right, 0>::value > 1)
        >
    {};

    template<typename Left, typename Right>
    struct is_row_vector_matrix_expr
        : __is_row_vector_matrix_expr<std::remove_reference_t<Left>, std::remove_reference_t<Right>>
    {};

    template<typename Left, typename Right>
    struct __is_vector_vector_expr
        : std::integral_constant<bool,
            is_matrix<Left>::value && is_matrix<Right>::value
            && extent<Left, 0>::value == extent<Right, 0>::value
            && extent<Left, 1>::value == extent<Right, 1>::value
            && (((extent<Left, 0>::value == 1) && (extent<Left, 0>::value > 1))
            || ((extent<Left, 1>::value > 1) && (extent<Left, 1>::value == 1)))
        >
    {};

    template<typename Left, typename Right>
    struct is_vector_vector_expr
        : __is_vector_vector_expr<std::remove_reference_t<Left>, std::remove_reference_t<Right>>
    {};

    template<typename Left, typename Right>
    struct __is_matrix_matrix_expr
        : std::integral_constant<bool,
            is_matrix<Left>::value && is_matrix<Right>::value
            && extent<Left, 0>::value == extent<Right, 0>::value
            && extent<Left, 1>::value == extent<Right, 1>::value
            && (extent<Left, 0>::value > 1)
            && (extent<Right, 1>::value > 1)
        >
    {};

    template<typename Left, typename Right>
    struct is_matrix_matrix_expr
        : __is_matrix_matrix_expr<std::remove_reference_t<Left>, std::remove_reference_t<Right>>
    {};

    template<typename Left, typename Right>
    struct __is_matrix_matrix_mul_expr
        : std::integral_constant<bool,
            is_matrix<Left>::value && is_matrix<Right>::value
            && extent<Left, 1>::value == extent<Right, 0>::value
            && (extent<Left, 0>::value > 1)
            && (extent<Right, 1>::value > 1)
        >
    {};

    template<typename Left, typename Right>
    struct is_matrix_matrix_mul_expr
        : __is_matrix_matrix_mul_expr<std::remove_reference_t<Left>, std::remove_reference_t<Right>>
    {};

    template<typename Left, typename Right>
    struct __is_matrix_scalar_expr
        : std::integral_constant<bool,
            is_matrix<Left>::value && is_literal<Right>::value
        >
    {};

    template<typename Left, typename Right>
    struct is_matrix_scalar_expr
        : __is_matrix_scalar_expr<std::remove_reference_t<Left>, std::remove_reference_t<Right>>
    {};

    template<typename Left, typename Right>
    struct __is_scalar_matrix_expr
        : std::integral_constant<bool,
            is_matrix<Left>::value && is_literal<Right>::value
        >
    {};

    template<typename Left, typename Right>
    struct is_scalar_matrix_expr
        : __is_scalar_matrix_expr<std::remove_reference_t<Left>, std::remove_reference_t<Right>>
    {};

    // =================================================================================================================

    struct matrix_transpose_op;

    /**
     * matrix (i, j) -> matrix (j, i)
     * @tparam Left
     */
    template<typename Left>
    struct expression<matrix_transpose_op, Left>
        : __expression<matrix_transpose_op, Left>
    {
        using __expression<matrix_transpose_op, Left>::operator_type;
        using __expression<matrix_transpose_op, Left>::operands_type;

        using __expression<matrix_transpose_op, Left>::__expression;

        using return_type = mat<
            typename common_type<Left>::type,
            extent<Left, 1>::value,
            extent<Left, 0>::value
        >;
    };

    struct matrix_mul_op;


    template<typename Left, typename Right>
    struct expression<matrix_mul_op, Left, Right>
        : __expression<matrix_mul_op, Left, Right>
    {
        using __expression<matrix_mul_op, Left, Right>::operator_type;
        using __expression<matrix_mul_op, Left, Right>::operands_type;

        using __expression<matrix_mul_op, Left, Right>::__expression;

        using return_type = select_t<

            /**
             * row vector (1, j) * col vector (j, 1) -> scalar (1, 1)
             * @tparam Left row vector
             * @tparam Right col vector
             */
            when<
                is_row_col_vector_expr<Left, Right>::value,
                typename common_type<Left, Right>::type
            >,

            /**
             * matrix (i, k) * matrix (k, j) -> matrix (i, j)
             * @tparam Left
             * @tparam Right
             */
            when<
                is_matrix_matrix_expr<Left, Right>::value,
                mat<
                    typename common_type<Left, Right>::type,
                    extent<Left, 0>::value,
                    extent<Right, 1>::value
                >
            >,

            /**
             * matrix (i, j) * scalar (1, 1) -> matrix (i, j)
             * @tparam Left row vector
             * @tparam Right col vector
             */
            when<
                is_matrix_scalar_expr<Left, Right>::value,
                mat<
                    typename common_type<
                        typename Left::return_type,
                        typename Right::return_type
                    >::type,
                    extent<Left, 0>::value,
                    extent<Left, 1>::value
                >
            >,

            /**
             * scalar (1, 1) * matrix (i, j) -> matrix (i, j)
             * @tparam Left row vector
             * @tparam Right col vector
             */
            when<
                is_scalar_matrix_expr<Left, Right>::value,
                mat<
                    typename common_type<
                        typename Left::return_type,
                        typename Right::return_type
                    >::type,
                    extent<Right, 0>::value,
                    extent<Right, 1>::value
                >
            >
        >;
    };

}}