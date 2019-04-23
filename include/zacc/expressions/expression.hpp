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

namespace zacc {

    struct expr
    {
    };

    template<typename T>
    struct arg : expr
    {
        T operator() (T val)
        {
            return val;
        }
    };

    template<typename T>
    struct term : expr//<term<T>>
    {
        term& _self;

        constexpr term()
            : _self(*this)
        {}

        size_t id() const {
            std::stringstream sstream;
            sstream << static_cast<const void*>(&_self);

            return std::hash<std::string>()(sstream.str());
        }
    };

    template<typename T>
    struct lit : expr//<lit<T>>
    {
        const T& _val;

        lit(const T& val) : _val(val)
        {}

        const T& operator()(size_t) const
        {
            return _val;
        }
    };



    template<typename Func, typename Expr>
    struct apply_expr : expr//<assign_expr<T, Expr>>
    {
        Func _func;
        Expr _expr;

        apply_expr(Func func, Expr expr)
            : _func(func), _expr(expr)
        {
        }

        auto operator()(size_t i)
        {
            return func(_expr(i));
        }
    };

    template<typename T, typename Expr>
    struct assign_expr : expr//<assign_expr<T, Expr>>
    {
        T& _target;
        Expr _expr;

        assign_expr(T& target, Expr expr)
            : _target(target), _expr(expr)
        {
        }

        static constexpr auto size() { return T::size(); }

        auto operator()(size_t i)
        {
            return _target(i) = _expr(i);
        }
    };

    template<typename T>
    struct declare_expr : expr//<declare_expr<T>>
    {
        T& _target;
//        Expr _expr;

        declare_expr(T& target)
            : _target(target)
        {
        }
//        declare_expr(T& target, const assign_expr<T, Expr>& expr)
//            : _target(target), _expr(expr)
//        {
//        }
    };

//    template<typename Op, typename... Expr>
//    struct m_expr : expr
//    {
//        std::tuple<Expr...> _expr;
//
//        explicit m_expr(Expr&&... expr)
//            : _expr(std::make_tuple(std::forward<Expr>(expr)...))
//        {}
//
//        auto operator()(size_t i) { return Op::apply(_a(i), _b(i), _c(i)); }
//    };

    template<typename FuncOp, typename AExpr, typename BExpr, typename CExpr>
    struct func_expr : expr//<func_expr<FuncOp, AExpr, BExpr, CExpr>>
    {
        AExpr _a;
        BExpr _b;
        CExpr _c;

        func_expr(AExpr a, BExpr b, CExpr c)
            : _a(a), _b(b), _c(c)
        {}

        auto operator()(size_t i) { return FuncOp::apply(_a(i), _b(i), _c(i)); }
    };

    template<typename TriOp, typename AExpr, typename BExpr, typename CExpr>
    struct tri_expr : expr//<tri_expr<TriOp, AExpr, BExpr, CExpr>>
    {
        AExpr _a;
        BExpr _b;
        CExpr _c;

        tri_expr(AExpr a, BExpr b, CExpr c)
            : _a(a), _b(b), _c(c)
        {}

        auto operator()(size_t i) { return TriOp::apply(_a(i), _b(i), _c(i)); }
    };

    template<typename BinOp, typename Left, typename Right>
    struct bin_expr : expr//<bin_expr<BinOp, Left, Right>>
    {
        Left _left;
        Right _right;

        bin_expr(Left left, Right right)
            : _left(left), _right(right)
        {}

        auto operator()(size_t i) { return BinOp::apply(_left(i), _right(i)); }
    };

    template<typename UnOp, typename Expr>
    struct un_expr : expr//<un_expr<UnOp, Expr>>
    {
        Expr _expr;

        un_expr(Expr expr)
            : _expr(expr)
        {}

        auto operator()(size_t i) { return UnOp::apply(_expr(i)); }
    };

    // =================================================================================================================

//    template<typename LExpr = void, typename RExpr = void>
//    struct plus;
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct minus;
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct multiplies;
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct divides;
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct modulus;
//
//    template<typename RExpr = void>
//    struct negate;
//
//    template<typename RExpr = void>
//    struct promote;
//
//    template<typename AExpr = void, typename BExpr = void, typename CExpr = void>
//    struct fmadd;
//
//    // =================================================================================================================
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct equal_to;
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct not_equal_to;
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct greater;
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct less;
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct greater_equal;
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct less_equal;
//
//    // =================================================================================================================
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct logical_and;
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct logical_or;
//
//    template<typename RExpr = void>
//    struct logical_not;
//
//    // =================================================================================================================
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct bit_and;
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct bit_or;
//
//    template<typename LExpr = void, typename RExpr = void>
//    struct bit_xor;
//
//    template<typename RExpr = void>
//    struct bit_not;

    // =================================================================================================================
}