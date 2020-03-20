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

#include <stack>
#include <list>
#include <map>
#include <string>

namespace zacc::compute
{

    // TODO: -> traits
    template<typename Expr>
    constexpr static bool is_expr_v = std::is_base_of_v<expression<>, std::decay_t<Expr>>;

    template<typename T, typename = void>
    struct op
    {
        using type = void;
    };

    template<typename T>
    struct op<T, std::enable_if_t<is_expr_v<T>>>
    {
        using type = typename std::decay_t<T>::operator_type;
    };

    template<typename T>
    using op_t = typename op<T>::type;

    template<typename Expression>
    class dispatch_expression
    {
        template<typename>
        friend struct bla;
    public:
        constexpr explicit dispatch_expression(Expression const& expression)
            : _expression { expression }
        {}

        template<typename NewPolicy>
        constexpr auto operator()(NewPolicy = {}) const
        {
            return visit<NewPolicy>(_expression);
        }
    private:
        Expression const& _expression;

        template<typename Op, typename NewPolicy, typename... Ops>
        struct override_policy_impl;

        template<template<typename, typename...> class Op, typename Policy, typename NewPolicy, typename... Ops>
        struct override_policy_impl<Op<Policy>, NewPolicy, Ops...>
        {
            using type = Op<NewPolicy, Ops...>;
        };

        template<typename Op, typename NewPolicy, typename... Ops>
        using override_policy_t = typename override_policy_impl<Op, NewPolicy, Ops...>::type;

//        static_assert(std::is_same_v<select_op<scalar>, override_policy_t<select_op<>, scalar>>);
//        static_assert(std::is_same_v<select_op<scalar, bool, int, int>, override_policy_t<select_op<>, scalar, bool, int, int>>);

        template<typename Op, typename NewPolicy, typename Expr>
        constexpr static auto override_expression(Expr&& expr)
        {
            auto f = [](auto... x) constexpr {
                return make_expression<override_policy_t<Op, NewPolicy, decltype(visit<NewPolicy>(std::forward<decltype(x)>(x)))...>>(visit<NewPolicy>(std::forward<decltype(x)>(x))...);
            };

            return std::apply(f, std::forward<Expr>(expr).operands());
        }

        template<typename NewPolicy, typename Expr>
        constexpr static auto visit(Expr&& expr)
        {
            auto fe = std::forward<Expr>(expr);

            if constexpr(std::is_base_of_v<expression<>, std::decay_t<Expr>>)
            {
                using op = typename std::decay_t<Expr>::operator_type;

                return override_expression<op, NewPolicy>(fe);
            }
            else
            {
                return fe;
            }
        };
    };

    template<typename Expression>
    class strip_expression
    {
    public:
        constexpr explicit strip_expression(Expression expression)
            : _expression { expression }
        {}

        constexpr auto operator()() const
        {
            return visit(_expression);
        }
    private:
        Expression _expression;

        template<typename NewOp, typename Expr>
        constexpr static auto override_expression(Expr&& expr)
        {
            auto f = [](auto... x) constexpr {
                return make_expression<NewOp>(visit(std::forward<decltype(x)>(x))...);
            };

            return std::apply(f, std::forward<Expr>(expr).operands());
        }

        template<typename Expr>
        constexpr static auto visit(Expr&& expr)
        {
            auto fe = std::forward<Expr>(expr);

            if constexpr(std::is_base_of_v<expression<>, std::decay_t<Expr>>)
            {
                using op = typename std::decay_t<Expr>::operator_type;

                if constexpr (std::is_same_v<init_op<>, op>)
                {
                    return visit(fe.second());
                }
                else if constexpr (std::is_same_v<assign_op<>, op>)
                {
                    return visit(fe.second());
                }
                else
                {
                    return override_expression<op>(fe);
                }
            }
            else if constexpr(std::is_base_of_v<var<>, std::decay_t<Expr>>)
            {
                return visit(fe.initializer());
            }
            else
            {
                return fe;
            }
        };
    };

    template<typename Expression>
    struct merge_expression
    {
    public:
        constexpr explicit merge_expression(Expression expression)
            : _expression { expression }
        {}

        constexpr auto operator()() const
        {
            return visit(_expression);
        }
    private:
        Expression _expression;

        template<typename NewOp, typename Expr>
        constexpr static auto override_expression(Expr&& expr)
        {
            auto f = [](auto... x) constexpr {
                return make_expression<NewOp>(visit(std::forward<decltype(x)>(x))...);
            };

            return std::apply(f, std::forward<Expr>(expr).operands());
        }

        template<typename NewOp, typename Head, typename... Tail>
        constexpr static auto override_expression(Head&& head, Tail&& ...tail)
        {
            auto f = [](auto... x) constexpr {
                return make_expression<NewOp>(visit(std::forward<decltype(x)>(x))...);
            };

            return std::invoke(f, std::forward<Head>(head), std::forward<Tail>(tail)...);
        }

        template<typename Expr>
        constexpr static auto visit(Expr&& expr)
        {
            auto fe = std::forward<Expr>(expr);

            if constexpr(is_expr_v<Expr> && std::is_same_v<add_op<>, op_t<Expr>>)
            {
                if constexpr(is_expr_v<decltype(fe.first())>)
                {
                    if constexpr (std::is_same_v<mul_op<>, op_t<decltype(fe.first())>>)
                    {
                        return override_expression<fmadd_op<>>(fe.first().first(), fe.first().second(), fe.second());
                    }
                    else
                    {
                        return fe;
                    }
                }
                else if constexpr (is_expr_v<decltype(fe.second())>)
                {
                    if constexpr (std::is_same_v<mul_op<>, op_t<decltype(fe.second())>>)
                    {
                        return override_expression<fmadd_op<>>(fe.second().first(), fe.second().second(), fe.first());
                    }
                    else
                    {
                        return fe;
                    }
                }
                else
                {
                    return fe;
                }
            }
            else
            {
                return fe;
            }
        };
    };

    template<typename Expression>
    struct condense_expression
    {
    public:
        constexpr explicit condense_expression(Expression const& expression)
            : _expression { expression }
        {}

        constexpr auto operator()() const
        {
            return visit(_expression);
        }
    private:
        Expression const& _expression;

        template<typename Op, typename... NewOps>
        struct override_policy_impl;

        template<template<typename, typename...> class Op, typename Policy, typename... Ops, typename... NewOps>
        struct override_policy_impl<Op<Policy, Ops...>, NewOps...>
        {
            using type = Op<Policy, NewOps...>;
        };

        template<typename Op, typename... NewOps>
        using override_policy_t = typename override_policy_impl<Op, NewOps...>::type;

        template<typename Expr>
        constexpr static auto strip(Expr&& expr)
        {
            auto f = [](auto... x) constexpr {
                return override_policy_t<op_t<Expr>, decltype(visit(std::forward<decltype(x)>(x)))...> { visit(std::forward<decltype(x)>(x))... };
            };

            return std::apply(f, std::forward<Expr>(expr).operands());
        }

        template<typename Expr>
        constexpr static auto visit(Expr&& expr)
        {
            if constexpr(is_expr_v<std::decay_t<Expr>>)
            {
                return strip(std::forward<Expr>(expr));
            }
            else if constexpr(std::is_base_of_v<operator_base, std::decay_t<Expr>>)
            {
                return std::forward<Expr>(expr);
            }
            else
            {
                return std::forward<Expr>(expr);; // strip<op_t<Expr>>(std::forward<Expr>(expr));
            }
        };

        //static_assert(std::is_same_v<sub_op<scalar, mul_op<scalar, int, int>, int>, decltype(visit(sub_op<scalar, expression<mul_op<scalar, int, int>, int, int>, int>(0, 0))));
    };

    template<typename Expression>
    class builder;

    template<typename Expression>
    constexpr auto make_builder(Expression&& expression)
    {
        return builder { std::forward<Expression>(expression) };
    };

    template<typename Expression>
    class builder
    {
    public:
        constexpr explicit builder(Expression&& expression)
            : _expression { std::forward<Expression>(expression) }
        {}

        constexpr explicit builder(Expression const& expression)
            : _expression { expression }
        {}

        constexpr auto strip() const
        {
            return make_builder(strip_expression(_expression)());
        }

        constexpr auto merge() const
        {
            return make_builder(merge_expression(_expression)());
        }

        constexpr auto condense() const
        {
            return make_builder(condense_expression(_expression)());
        }

        template<typename Policy>
        constexpr auto dispatch(Policy policy = {}) const
        {
            return make_builder(dispatch_expression(_expression)(policy));
        }

        constexpr Expression result() const
        {
            return _expression;
        }

        template<typename Policy>
        constexpr auto build(Policy policy = {}) const
        {
            auto result = strip()
                .merge()
                .dispatch(policy)
                .condense()
                .result();

            if constexpr (std::is_base_of_v<expression<>, decltype(result)>)
            {
                return result;
            }
            else if constexpr (std::is_arithmetic_v<decltype(result)>)
            {
                return [result] { return result; };
            }
            else
            {
                return result;
            }
        }

    private:

        Expression _expression;
    };
}