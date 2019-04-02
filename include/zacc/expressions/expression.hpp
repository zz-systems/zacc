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

    //template<typename T>
    struct expr
    {
//        auto operator()(size_t i)
//        {
//            return static_cast<const T*>(this)->operator()(i);
//        }
    };

//    template<>
//    struct expr<void>
//    {};

    template<typename T>
    struct arg : expr//<arg<T>>
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

//        T& operator()(size_t i)
//        {
//            return _val;
//        }

        const T& operator()(size_t i) const
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

    template<typename Left, typename Right, typename SizeProxy = void>
    struct pipe : expr
    {
        Left _left;
        Right _right;

        pipe(Left left, Right right)
            : _left(left), _right(right)
        {}

        auto operator()() { return _left(_right); }

        template<typename... Args>
        auto operator()(Args&& ...args) { return _left(_right(std::forward<Args>(args)...)); }
    };

    template<typename Left, typename Right>
    struct pipe<Left, Right, void_t<decltype( Right::size )>>
    {
        Left _left;
        Right _right;

        pipe(Left left, Right right)
            : _left(left), _right(right)
        {}

        auto operator()() { return _left(_right); }

        template<typename... Args>
        auto operator()(Args&& ...args) { return _left(_right(std::forward<Args>(args)...)); }

        static constexpr auto size()
        {
            return Right::size();
        }
    };

    template<typename T>
    struct is_pipe : std::false_type
    {};

//    template<typename Left, typename Right>
//    struct is_pipe<pipe<Left, Right>> : std::true_type
//    {};

    template<typename Left, typename Right, typename SizeProxy>
    struct is_pipe<pipe<Left, Right, SizeProxy>> : std::true_type
    {};

    // =================================================================================================================

    template<typename LExpr = void, typename RExpr = void>
    struct plus;

    template<typename LExpr = void, typename RExpr = void>
    struct minus;

    template<typename LExpr = void, typename RExpr = void>
    struct multiplies;

    template<typename LExpr = void, typename RExpr = void>
    struct divides;

    template<typename LExpr = void, typename RExpr = void>
    struct modulus;

    template<typename RExpr = void>
    struct negate;

    template<typename RExpr = void>
    struct promote;

    template<typename AExpr = void, typename BExpr = void, typename CExpr = void>
    struct fmadd;

    // =================================================================================================================

    template<typename LExpr = void, typename RExpr = void>
    struct equal_to;

    template<typename LExpr = void, typename RExpr = void>
    struct not_equal_to;

    template<typename LExpr = void, typename RExpr = void>
    struct greater;

    template<typename LExpr = void, typename RExpr = void>
    struct less;

    template<typename LExpr = void, typename RExpr = void>
    struct greater_equal;

    template<typename LExpr = void, typename RExpr = void>
    struct less_equal;

    // =================================================================================================================

    template<typename LExpr = void, typename RExpr = void>
    struct logical_and;

    template<typename LExpr = void, typename RExpr = void>
    struct logical_or;

    template<typename RExpr = void>
    struct logical_not;

    // =================================================================================================================

    template<typename LExpr = void, typename RExpr = void>
    struct bit_and;

    template<typename LExpr = void, typename RExpr = void>
    struct bit_or;

    template<typename LExpr = void, typename RExpr = void>
    struct bit_xor;

    template<typename RExpr = void>
    struct bit_not;

    // =================================================================================================================


//    template<template<typename> class Op, typename Head>
//    struct require_expr<Op<Head>>
//    {
//        using type = std::enable_if_t<std::is_base_of<expr, Op<Head>>::value, Op<Head>>;
//    };

    template<typename T>
    using is_expr = std::is_base_of<expr, T>;

    template<typename Expr>
    using expr_t = std::enable_if_t<is_expr<Expr>::value, Expr>;

    template<template<class> class Expr, typename Right>
    using un_expr_t = std::enable_if_t<is_expr<Right>::value, Expr<Right>>;

    template<typename Left, typename Right>
    using is_bin_expr = std::integral_constant<bool, is_expr<Left>::value && is_expr<Right>::value && !is_pipe<Left>::value && !is_pipe<Right>::value>;

    template<typename Left, typename Right>
    using is_lr_cast = std::integral_constant<bool, std::is_arithmetic<Left>::value && is_expr<Right>::value && !is_pipe<Right>::value>; //!is_expr<Left>::value && !is_functor<Left>::value && is_expr<Right>::value>;

    template<typename Left, typename Right>
    using is_rl_cast = std::integral_constant<bool, is_expr<Left>::value && std::is_arithmetic<Right>::value && !is_pipe<Left>::value>; //is_expr<Left>::value && !is_expr<Right>::value && !is_functor<Right>::value>;

    template<template<class, class> class Expr, template<class> class Cast, typename Left, typename Right>
    using bin_expr_t = select_t<
        when<is_bin_expr<Left, Right>::value, Expr<Left, Right>>, //Expr<std::decay<Left>, std::decay<Right>>>,
        when<is_lr_cast<Left, Right>::value, Expr<Cast<Left>, Right>>,
        when<is_rl_cast<Left, Right>::value, Expr<Left, Cast<Right>>>>;

//    template<template<class, class> class Expr, typename Left, typename Right>
//    using bin_expr_t = std::enable_if_t<is_bin_expr<Left, Right>::value, Expr<Left, Right>>;
//
//    template<template<class, class> class Expr, template<class> class Cast, typename Left, typename Right>
//    using lr_cast_expr_t = std::enable_if_t<is_lr_cast<Left, Right>::value, Expr<Cast<Left>, Right>>;
//
//    template<template<class, class> class Expr, template<class> class Cast, typename Left, typename Right>
//    using rl_cast_expr_t = std::enable_if_t<is_rl_cast<Left, Right>::value, Expr<Left, Cast<Right>>>;


//    template<typename Expr, typename A, typename B, typename C>
//    struct require_expr
//    {
//        using type = std::enable_if_t<
//            std::is_base_of<expr, A>::value
//            && std::is_base_of<expr, B>::value
//            && std::is_base_of<expr, C>::value,
//            Expr>;
//    };
//
//    template<class Expr, typename A, typename B>
//    struct require_expr<Expr, A, B, void>
//    {
//        using type = std::enable_if_t<
//            std::is_base_of<expr, A>::value
//            && std::is_base_of<expr, B>::value,
//            Expr>;
//    };
//
//    template<typename Expr, typename A>
//    struct require_expr<Expr, A, void, void>
//    {
//        using type = std::enable_if_t<std::is_base_of<expr, A>::value, Expr>;
//    };
//
//
//    template<typename Expr>
//    struct require_expr<Expr, void, void, void>
//    {
//        using type = std::enable_if_t<std::is_base_of<expr, Expr>::value, Expr>;
//    };
//
//    template<typename... Expr>
//    using require_expr_t = typename require_expr<Expr...>::type;

}