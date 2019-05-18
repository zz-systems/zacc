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

#include <zacc/compute/core/operators.hpp>

namespace zacc { namespace compute {

    // =================================================================================================================

    template<typename Expr>
    struct negate<negate<Expr>> : identity<Expr>
    {
        negate(negate<Expr> expr)
            : identity<Expr>(expr._expr)
        {}
    };

    // =================================================================================================================

    template<typename AExpr, typename BExpr, typename CExpr>
    struct plus<AExpr, multiplies<BExpr, CExpr>> : fmadd<AExpr, BExpr, CExpr>
    {
        plus(AExpr left, multiplies<BExpr, CExpr> right)
            : fmadd<AExpr, BExpr, CExpr>(left, right._left, right._right)
        {}
    };

    template<typename AExpr, typename BExpr, typename CExpr>
    struct plus<multiplies<AExpr, BExpr>, CExpr> : fmadd<AExpr, BExpr, CExpr>
    {
        plus(multiplies<AExpr, BExpr> left, CExpr right)
            : fmadd<AExpr, BExpr, CExpr>(left._left, left._right, right)
        {}
    };

    /*
     * cover cases such as y = a * a + b * b;
     */
    template<typename AExpr, typename BExpr, typename CExpr, typename DExpr>
    struct plus<multiplies<AExpr, BExpr>, multiplies<CExpr, DExpr>> : fmadd<AExpr, BExpr, multiplies<CExpr, DExpr>>
    {
        plus(multiplies<AExpr, BExpr> left, multiplies<CExpr, DExpr> right)
            : fmadd<AExpr, BExpr, multiplies<CExpr, DExpr>>(left._left, left._right, right)
        {}
    };

    // =================================================================================================================

}}