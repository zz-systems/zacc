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

#include <algorithm>
#include <functional>

namespace zacc { namespace compute {

    // =================================================================================================================

    template<typename, size_t>
    struct container;

    template<typename, typename...>
    struct expression;

    template<typename, typename...>
    struct batch_expression;

    template<typename Operator>
    struct batch_op
    {};

    class recorder;

    // =================================================================================================================


    template<typename T, size_t Size>
    struct batch
        : variable<batch<T, Size>>//, iterable_mixin<batch<T, Size>>
    {
        using value_type = std::decay_t<T>;
        using operator_type = batch<T, Size>;
        constexpr static auto dim = std::make_tuple(Size);

        constexpr batch()
            : variable<batch>(), _data{}
        {
        }

        constexpr batch(std::initializer_list<T> init_list)
            : variable<batch>(initializer<batch>{init_list})
        {
        }

        using variable<batch<T, Size>>::variable;

        template<typename Expression>
        batch& operator=(Expression&& expr)
        {
            variable<batch>::operator=(std::forward<Expression>(expr));

            return *this;
        }

        constexpr auto begin() { return _data.begin(); }
        constexpr auto begin() const { return _data.begin(); }

        constexpr auto end() { return _data.end(); }
        constexpr auto end() const { return _data.end(); }

    //private:
        typename container<T, Size>::type _data;
    };

    template<typename Operator, typename... Operands>
    struct batch_expression : expression<Operator, Operands...>
    {
        static_assert(fold(std::logical_or<>{}, true, is_batch_v<Operands>...), "");

        using typename expression<Operator, Operands...>::operator_type;
        using return_type = batch<std::common_type_t<value_type_t<result_of_t<Operands>>...>, max(extent_v<Operands, 0>...)>;
        using typename expression<Operator, Operands...>::operands_type;

        using expression<Operator, Operands...>::expression;
    };

    template<typename T, size_t Size>
    class evaluator<batch<T, Size>> : public __evaluator<size_t>
    {
        using __evaluator<size_t>::__evaluator;
        using __evaluator<size_t>::_args;
    public:
        template<typename Expression>
        auto visit(Expression&& expression, scalar_policy<>)
        {
            return expression._data[std::get<0>(_args)];
        }
    };
    // =================================================================================================================
}}