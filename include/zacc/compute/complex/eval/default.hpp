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

//    template<typename Expression, typename... Args>
//    class evaluator;
//
//    template<typename... Args>
//    class __evaluator;

    template<typename T, typename... Args>
    class evaluator<complex<T>, Args...> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::_args;
    protected:
        template<typename Expression>
        auto next(Expression&& expression)
        {
            return expression._data[std::get<0>(_args)];
        }
    };

    // =================================================================================================================
    // ARITHMETIC
    // =================================================================================================================

    template<typename... Args>
    class evaluator<complex_add_op> : public __evaluator<Args...>
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

    template<typename... Args>
    class evaluator<complex_scalar_add_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
        using __evaluator<Args...>::_args;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            if(std::get<0>(_args) == 0)
            {
                return next<0>(expression)
                       + next<1>(expression);
            }
            else
            {
                return next<1>(expression);
            }
        }
    };

    template<typename... Args>
    class evaluator<scalar_complex_add_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
        using __evaluator<Args...>::_args;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            if(std::get<0>(_args) == 0)
            {
                return next<0>(expression)
                       + next<1>(expression);
            }
            else
            {
                return next<1>(expression);
            }
        }
    };

    // =================================================================================================================

    template<typename... Args>
    class evaluator<complex_sub_op> : public __evaluator<Args...>
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

    template<typename... Args>
    class evaluator<complex_scalar_sub_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
        using __evaluator<Args...>::_args;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            if(std::get<0>(_args) == 0)
            {
                return next<0>(expression)
                       - next<1>(expression);
            }
            else
            {
                return next<0>(expression);
            }
        }
    };

    template<typename... Args>
    class evaluator<scalar_complex_sub_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
        using __evaluator<Args...>::_args;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            if(std::get<0>(_args) == 0)
            {
                return next<0>(expression)
                       - next<1>(expression);
            }
            else
            {
                return next<1>(expression);
            }
        }
    };

    // =================================================================================================================

    template<typename... Args>
    class evaluator<complex_mul_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
        using __evaluator<Args...>::_args;
    public:
        template<typename Expression>
        auto visit(Expression&& expression)
        {
            if(std::get<0>(_args) == 0)
            {
                return next<0>(expression, 0) * next<1>(expression, 0)
                       - next<0>(expression, 1) * next<1>(expression, 1);
            }
            else if(std::get<0>(_args) == 1)
            {
                return next<0>(expression, 1) * next<1>(expression, 0)
                    - next<0>(expression, 0) * next<1>(expression, 1);
            }
        }
    };

    template<typename... Args>
    class evaluator<complex_scalar_mul_op> : public __evaluator<Args...>
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
    class evaluator<complex_div_op> : public __evaluator<Args...>
    {
        using __evaluator<Args...>::__evaluator;
        using __evaluator<Args...>::next;
        using __evaluator<Args...>::_args;
    public:

        template<typename Expression>
        auto visit(Expression&& expression)
        {
            auto div = next<1>(expression, 0) * next<1>(expression, 0)
                       + next<1>(expression, 1) * next<1>(expression, 1);

            if(std::get<0>(_args) == 0)
            {
                return (next<0>(expression, 0) * next<1>(expression, 0)
                        + next<0>(expression, 1) * next<1>(expression, 1))
                       / div;
            }
            else if(std::get<0>(_args) == 1)
            {
                return (next<0>(expression, 1) * next<1>(expression, 0)
                        + next<0>(expression, 0) * next<1>(expression, 1))
                       / div;
            }
        }
    };

    template<typename... Args>
    class evaluator<complex_scalar_div_op> : public __evaluator<Args...>
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
    class evaluator<complex_neg_op> : public __evaluator<Args...>
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
    class evaluator<complex_promote_op> : public __evaluator<Args...>
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
    class evaluator<complex_equal_to_op> : public __evaluator<Args...>
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
    class evaluator<complex_not_equal_to_op> : public __evaluator<Args...>
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
}}