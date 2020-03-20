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

namespace zacc { namespace compute {

    template<typename Expression>
    class evaluator;

    template<typename... Args>
    class __evaluator;

    template<typename T, size_t Rows, size_t Cols, typename... Args>
    class evaluator<mat<T, Rows, Cols>, Args...> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::_args;
        protected:
        template<typename Expression>
        auto next(Expression&& expression)
        {
            return expression._data[reshape_xy_i(std::get<0>(_args), std::get<1>(_args), Cols)];
        }
    };

    // =================================================================================================================
    // ARITHMETIC
    // =================================================================================================================

    template<typename... Args>
    class evaluator<matrix_add_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(expression)
                 + next<1>(expression);
        }
    };

    // =================================================================================================================

    template<typename... Args>
    class evaluator<matrix_sub_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(expression)
                   - next<1>(expression);
        }
    };

    // =================================================================================================================

    template<typename... Args>
    class evaluator<matrix_mul_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
        using __evaluator<Args...>::_args;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            auto row = std::get<0>(_args);
            auto col = std::get<1>(_args);
            
            auto result = next<0>(expression, row, 0) * next<1>(expression, 0, col);

            for(size_t j = 1; j < extent_v<operand_type_t<1, Expression>, 1>; j++)
            {
                result += next<0>(expression, row, j) * next<1>(expression, j, col);
            }

            return result;
        }
    };

    template<typename... Args>
    class evaluator<matrix_scalar_mul_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(expression)
                * next<1>(expression);
        }
    };

    // =================================================================================================================

    template<typename... Args>
    class evaluator<matrix_scalar_div_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(expression)
                 * next<1>(expression);
        }
    };

    // =================================================================================================================

    template<typename... Args>
    class evaluator<matrix_neg_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return -next<0>(expression);
        }
    };

    template<typename... Args>
    class evaluator<matrix_promote_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return +next<0>(expression);
        }
    };

    // =================================================================================================================
    // COMPARISON
    // =================================================================================================================

    template<typename... Args>
    class evaluator<matrix_equal_to_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(expression)
                == next<1>(expression);
        }
    };

    template<typename... Args>
    class evaluator<matrix_not_equal_to_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(expression)
                != next<1>(expression);
        }
    };

    // =================================================================================================================

    template<typename... Args>
    class evaluator<matrix_transpose_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
        using __evaluator<Args...>::_args;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            auto row = std::get<0>(_args);
            auto col = std::get<1>(_args);

            return next<0>(expression, col, row);
        }
    };

    // =================================================================================================================
}}