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

    // =================================================================================================================
    
    template<typename>
    class evaluator;

    template<typename...>
    class __evaluator;

    template<typename T, size_t Size>
    class evaluator<batch<T, Size>> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::_args;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return expression._data[std::get<0>(_args)];
        }
    };

    // =================================================================================================================

    template<>
    class evaluator<select_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<call_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression));
        }
    };

    // =================================================================================================================
    // ARITHMETIC
    // =================================================================================================================

    template<>
    class evaluator<identity_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<add_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   + next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<sub_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   - next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<mul_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   * next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<div_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   / next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<mod_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   % next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<neg_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return -next<0>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<promote_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return +next<0>(std::forward<Expression>(expression));
        }
    };

    // =================================================================================================================
    // COMPARISON
    // =================================================================================================================

    template<>
    class evaluator<equal_to_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   == next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<not_equal_to_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   != next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<greater_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   > next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<less_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   < next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<greater_equal_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   >= next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<less_equal_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   <= next<1>(std::forward<Expression>(expression));
        }
    };

    // =================================================================================================================
    // BOOLEAN
    // =================================================================================================================

    template<>
    class evaluator<bool_and_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   && next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<bool_or_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   || next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<bool_not_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return !next<0>(std::forward<Expression>(expression));
        }
    };

    // =================================================================================================================
    // BITWISE
    // =================================================================================================================

    template<>
    class evaluator<bit_and_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   & next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<bit_or_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   | next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<bit_xor_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                   ^ next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<bit_shl_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                << next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<bit_shr_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return next<0>(std::forward<Expression>(expression))
                >> next<1>(std::forward<Expression>(expression));
        }
    };

    template<>
    class evaluator<bit_not_op> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::next;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            return ~next<0>(std::forward<Expression>(expression));
        }
    };

    // =================================================================================================================
}}