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

namespace zacc { namespace compute {

    // =================================================================================================================
    template<template<typename...> class Visitor, typename Expression, typename... Args>
    auto visit(Expression&& expression, Args&& ...args);

    template<typename Expression>
    class evaluator;

    template<typename Expression, typename>
    struct execution_policy;

    template<typename Expression>
    struct execution_policy<Expression, std::enable_if_t<is_matrix_v<Expression>, Expression>>
    {
        static std::size_t begin()
        {
            return 0;
        }

        static std::size_t end()
        {
            return extent_v<Expression, 0> * extent_v<Expression, 1>;
        }

        static std::size_t step()
        {
            return 1;
        }

        static auto apply(Expression &expression, std::size_t index)
        {
            return visit<evaluator>(expression, reshape_i_xy(index, extent_v<1, Expression>));
        }
    };

    // =================================================================================================================


    // =================================================================================================================


    // =================================================================================================================

}}