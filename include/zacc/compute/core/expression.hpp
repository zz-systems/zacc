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
#include <optional>

namespace zacc::compute
{
    template<typename... Operands>
    class expression;

        template<typename T>
        class literal;

    template<typename>
    class var;

    template<typename T>
    constexpr decltype(auto) eval(T&& t)
    {
        if constexpr (std::is_base_of_v<expression<>, std::decay_t<T>>)
            return std::forward<T>(t)();
        else
            return std::forward<T>(t);
    }

    template<typename T>
    constexpr decltype(auto) eval(var<T>&& v)
    {
        return std::forward<T>(v)();
    }

    template<typename Operator, typename... Operands>
    constexpr decltype(auto) eval(expression<Operator, Operands...>&& v)
    {
        return std::forward<expression<Operator, Operands...>>(v)();
    }

    template<typename T>
    auto expression_cast(T&& arg)
        -> std::conditional_t<std::is_base_of<term<>, T>::value,
                T,
                literal<std::decay_t<T>>>
    {
        return std::forward<T>(arg);
    }

    template<typename Operator, typename... Ts>
    auto make_expression(Ts&& ...args)
    {
        return expression<Operator, decltype(expression_cast(std::forward<Ts>(args)).cast())...>(expression_cast(std::forward<Ts>(args)).cast()...);
    }

    template<typename Operator, typename... Ts>
    auto make_expression(std::tuple<Ts...>&& operands)
    {
        return make_expression<Operator>(std::get<Ts>(std::forward<std::tuple<Ts...>>(operands))...);
    }

    template<>
    class expression<>
    {
    protected:
        constexpr expression() = default;
    };

    template<typename Operator, typename First>
    class expression<Operator, First>
        : public expression<>
        , public term<expression<Operator, First>>
    {
    public:
        using operator_type = std::remove_cv_t<Operator>;
        using operands_type = std::tuple<First>;
        constexpr explicit expression(First&& first)
            : _first { std::forward<First>(first) }
        {}

        constexpr auto operator()() const
        {
            return Operator { eval(_first) };
        };

        constexpr auto operands() const
        {
            return std::make_tuple(_first);
        }

        constexpr auto operands()
        {
            return std::make_tuple(_first);
        }

        constexpr auto first() const
        {
            return _first;
        }

    private:
        First _first;
    };

    template<typename Operator, typename First, typename Second>
    class expression<Operator, First, Second>
        : public expression<>
        , public term<expression<Operator, First, Second>>
    {
    public:
        using operator_type = std::remove_cv_t<Operator>;
        using operands_type = std::tuple<First, Second>;
        constexpr explicit expression(First&& first, Second&& second)
            : _first { std::forward<First>(first) }
            , _second { std::forward<Second>(second) }
        {}

        constexpr auto operator()() const
        {
            return Operator { eval(_first), eval(_second) };
        };

        constexpr auto operands() const
        {
            return std::make_tuple(_first, _second);
        }

        constexpr auto operands()
        {
            return std::make_tuple(_first, _second);
        }

        constexpr auto first() const
        {
            return _first;
        }

        constexpr auto second() const
        {
            return _second;
        }

    private:
        First _first;
        Second _second;
    };

    template<typename Operator, typename... Operands>
    class expression<Operator, Operands...>
        : public expression<>
        , public term<expression<Operator, Operands...>>
    {
    public:
        using operator_type = std::remove_cv_t<Operator>;
        using operands_type = std::tuple<Operands...>;
        constexpr explicit expression(Operands&& ...operands)
            : _operands { std::forward<Operands>(operands)... }
        {}

        constexpr auto operator()() const
        {
            return apply(std::index_sequence_for<Operands...>{});
        };

        template<size_t... Idx>
        constexpr auto apply(std::index_sequence <Idx...>) const
        {
            return Operator { eval(std::get<Idx>(_operands))... };
        }

        constexpr auto operands() const
        {
            return _operands;
        }

        constexpr auto operands()
        {
            return _operands;
        }

        template<auto I>
        constexpr auto operand() const
        {
            return std::get<I>(_operands);
        }

        template<auto I>
        constexpr auto operand()
        {
            return std::get<I>(_operands);
        }
    private:
        operands_type _operands;
    };
}