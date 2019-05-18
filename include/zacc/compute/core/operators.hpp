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

#include <zacc/compute/core/traits.hpp>
#include <zacc/util/string_view.hpp>

namespace zacc {namespace compute {

    // =================================================================================================================
    // ARITHMETIC
    // =================================================================================================================

    template<typename Expr, typename Enable = void>
    struct identity_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct plus_impl;

    template<typename Expr, typename Enable = void>
    struct promote_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct minus_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct multiplies_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct divides_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct modulus_impl;

    template<typename Expr, typename Enable = void>
    struct negate_impl;

    template<typename AExpr, typename BExpr, typename CExpr, typename Enable = void>
    struct fmadd_impl;

    // =================================================================================================================

    template<typename Expr>
    struct identity : un_expr<identity_impl<Expr>, Expr>
    {
        using un_expr<identity_impl<Expr>, Expr>::un_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct plus : bin_expr<plus_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<plus_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename Expr>
    struct promote : un_expr<promote_impl<Expr>, Expr>
    {
        using un_expr<promote_impl<Expr>, Expr>::un_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct minus : bin_expr<minus_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<minus_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct multiplies : bin_expr<multiplies_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<multiplies_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct divides : bin_expr<divides_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<divides_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct modulus : bin_expr<modulus_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<modulus_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename Expr>
    struct negate : un_expr<negate_impl<Expr>, Expr>
    {
        using un_expr<negate_impl<Expr>, Expr>::un_expr;
    };

    // =================================================================================================================

    /*
     * TODO:
     * Fused multiply–add can usually be relied on to give more accurate results.
     * However, William Kahan has pointed out that it can give problems if used unthinkingly.[3]
     * If x2 − y2 is evaluated as ((x×x) − y×y) using fused multiply–add, then the result may
     * be negative even when x = y due to the first multiplication discarding low significance
     * bits. This could then lead to an error if, for instance, the square root of the result
     * is then evaluated.
     */
    template<typename AExpr, typename BExpr, typename CExpr>
    struct fmadd : func_expr<fmadd_impl<AExpr, BExpr, CExpr>, AExpr, BExpr, CExpr>
    {
        using func_expr<fmadd_impl<AExpr, BExpr, CExpr>, AExpr, BExpr, CExpr>::func_expr;
    };

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<plus, Left, Right>
    operator+(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<minus, Left, Right>
    operator-(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<multiplies, Left, Right>
    operator*(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<divides, Left, Right>
    operator/(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<modulus, Left, Right>
    operator%(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Right>
    make_expr_t<negate, Right>
    operator-(const Right& right)
    {
        return { right };
    }

    // =================================================================================================================

    template<typename Right>
    make_expr_t<promote, Right>
    operator+(const Right& right)
    {
        return { right };
    }

    // =================================================================================================================
    // COMPARISON
    // =================================================================================================================

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct equal_to_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct not_equal_to_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct greater_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct less_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct greater_equal_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct less_equal_impl;

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct equal_to : bin_expr<equal_to_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<equal_to_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct not_equal_to : bin_expr<not_equal_to_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<not_equal_to_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct greater : bin_expr<greater_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<greater_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct less : bin_expr<less_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<less_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct greater_equal : bin_expr<greater_equal_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<greater_equal_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct less_equal : bin_expr<less_equal_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<less_equal_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<equal_to, Left, Right>
    operator==(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<not_equal_to, Left, Right>
    operator!=(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<greater, Left, Right>
    operator>(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<less, Left, Right>
    operator<(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<greater_equal, Left, Right>
    operator>=(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<less_equal, Left, Right>
    operator<=(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================
    // BOOLEAN
    // =================================================================================================================

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct logical_and_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct logical_or_impl;

    template<typename Expr, typename Enable = void>
    struct logical_not_impl;

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct logical_and : bin_expr<logical_and_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<logical_and_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct logical_or : bin_expr<logical_or_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<logical_or_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename Expr>
    struct logical_not : un_expr<logical_not_impl<Expr>, Expr>
    {
        using un_expr<logical_not_impl<Expr>, Expr>::un_expr;
    };

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<logical_and, Left, Right>
    operator&&(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<logical_or, Left, Right>
    operator||(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Right>
    make_expr_t<logical_not, Right>
    operator!(const Right& right)
    {
        return { right };
    }

    // =================================================================================================================
    // BITWISE
    // =================================================================================================================

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct bit_and_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct bit_or_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct bit_xor_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct bit_shl_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct bit_shr_impl;

    template<typename Expr, typename Enable = void>
    struct bit_not_impl;

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct bit_and : bin_expr<bit_and_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<bit_and_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct bit_or : bin_expr<bit_or_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<bit_or_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct bit_xor : bin_expr<bit_xor_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<bit_xor_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct bit_shl : bin_expr<bit_shl_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<bit_shl_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct bit_shr : bin_expr<bit_shr_impl<LExpr, RExpr>, LExpr, RExpr>
    {
        using bin_expr<bit_shr_impl<LExpr, RExpr>, LExpr, RExpr>::bin_expr;
    };

    // =================================================================================================================

    template<typename Expr>
    struct bit_not : un_expr<bit_not_impl<Expr>, Expr>
    {
        using un_expr<bit_not_impl<Expr>, Expr>::un_expr;
    };

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<bit_and, Left, Right>
    operator&(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<bit_or, Left, Right>
    operator|(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<bit_xor, Left, Right>
    operator^(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<bit_shl, Left, Right>
    operator<<(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    make_expr_t<bit_shr, Left, Right>
    operator>>(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Right>
    make_expr_t<bit_not, Right>
    operator~(const Right& right)
    {
        return { right };
    }

    // =================================================================================================================

}}