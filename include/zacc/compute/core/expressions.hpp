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

#include <zacc/compute/core/traits.hpp>
#include <zacc/util/string_view.hpp>

#include <string>

namespace zacc { namespace compute {

    // =================================================================================================================

    struct __expr {};

    template<typename T>
    struct expr : __expr
    {
        constexpr static expr_tag expr_tag = expr_tag::scalar;
        constexpr static uint64_t mask = 0;

        operator T const& () const
        {
            return *static_cast<const T*>(this);
        }

        template<typename... Args>
        auto operator()(Args&&... args)
        {
            return static_cast<T*>(this)->eval(std::forward<Args>(args)...);
        }

        template<typename... Args>
        auto operator()(Args&&... args) const
        {
            return static_cast<const T*>(this)->eval(std::forward<Args>(args)...);
        }
    };

    // =================================================================================================================

    template<typename T>
    struct arg : expr<arg<T>>
    {
        auto eval(T val) const
        {
            return val;
        }
    };

    // =================================================================================================================

    template<typename T>
    struct term : expr<term<T>>
    {
        term& _self;

        constexpr term()
            : _self(*this)
        {}

        size_t id() const {
            //return std::hash<std::string>()(std::to_string(reinterpret_cast<std::uintptr_t>(&_self)));
            return std::hash<std::uintptr_t>()(reinterpret_cast<std::uintptr_t>(&_self));
        }

        template<typename... Args>
        auto eval(Args&&... args)
        {
            return static_cast<T*>(this)->eval(std::forward<Args>(args)...);
        }

        template<typename... Args>
        auto eval(Args&&... args) const
        {
            return static_cast<const T*>(this)->eval(std::forward<Args>(args)...);
        }
    };

    // =================================================================================================================

    template<typename T>
    struct lit : expr<lit<T>>
    {
        constexpr static expr_tag expr_tag = expr_tag::scalar;
        const T& _val;

        constexpr lit(T const& value)
            : _val(value)
        {}

        template<typename... Args>
        auto eval(Args&& ...) const
        {
            return _val;
        }
    };

    // =================================================================================================================

    template<typename T, typename Expr>
    struct assign_expr : expr<assign_expr<T, Expr>>
    {
        T& _target;
        Expr _expr;

        constexpr assign_expr(T& target, Expr const& expr)
            : _target(target), _expr(expr)
        {}

        template<typename... Args>
        auto eval(Args&& ...args)
        {
            return _target.eval(std::forward<Args>(args)...) = _expr(std::forward<Args>(args)...);
        }
    };

    // =================================================================================================================

    template<typename T>
    struct declare_expr : expr<declare_expr<T>>
    {
        const T& _target;

        constexpr declare_expr(T const& target)
            : _target(target)
        {}
    };

    // =================================================================================================================

    template<typename FuncOp, typename AExpr, typename BExpr, typename CExpr>
    struct func_expr : expr<func_expr<FuncOp, AExpr, BExpr, CExpr>>
    {
        AExpr _a;
        BExpr _b;
        CExpr _c;

        constexpr func_expr(AExpr const& a, BExpr const& b, CExpr const& c)
            : _a(a), _b(b), _c(c)
        {}

        template<typename... Args>
        auto eval(Args&& ...args) const
        {
            return FuncOp::apply(_a(std::forward<Args>(args)...), _b(std::forward<Args>(args)...), _c(std::forward<Args>(args)...));
        }
    };

    // =================================================================================================================

    template<typename TriOp, typename AExpr, typename BExpr, typename CExpr>
    struct tri_expr : expr<tri_expr<TriOp, AExpr, BExpr, CExpr>>
    {
        AExpr _a;
        BExpr _b;
        CExpr _c;

        constexpr tri_expr(AExpr const& a, BExpr const& b, CExpr const& c)
            : _a(a), _b(b), _c(c)
        {}

        template<typename... Args>
        auto eval(Args&& ...args) const
        {
            return TriOp::apply(_a(std::forward<Args>(args)...), _b(std::forward<Args>(args)...), _c(std::forward<Args>(args)...));
        }
    };

    // =================================================================================================================

    template<typename BinOp, typename Left, typename Right>
    struct bin_expr : expr<bin_expr<BinOp, Left, Right>>
    {
        Left _left;
        Right _right;

        constexpr bin_expr(Left const& left, Right const& right)
            : _left(left), _right(right)
        {}

        template<typename... Args>
        auto eval(Args&& ...args) const
        {
            return BinOp::apply(_left(std::forward<Args>(args)...), _right(std::forward<Args>(args)...));
        }
    };

    // =================================================================================================================

    template<typename UnOp, typename Expr>
    struct un_expr : expr<un_expr<UnOp, Expr>>
    {
        Expr _expr;

        constexpr un_expr(Expr const& expr)
            : _expr(expr)
        {}

        template<typename... Args>
        auto eval(Args&& ...args) const
        {
            return UnOp::apply(_expr(std::forward<Args>(args)...));
        }
    };

    // =================================================================================================================

}}