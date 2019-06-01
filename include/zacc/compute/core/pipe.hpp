
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

#include <zacc/compute/core/expressions.hpp>

namespace zacc { namespace compute {

    // =================================================================================================================

    template <typename T>
    struct expr;

    template<typename Left, typename Right, typename SizeProxy = void>
    struct pipe : expr<pipe<Left, Right, SizeProxy>>
    {
        Left _left;
        Right _right;

        pipe(Left const& left, Right const& right)
            : _left(left), _right(right)
        {}

        auto eval() const
        {
            return _left(_right);
        }

        template<typename... Args>
        auto eval(Args&& ...args) const
        {
            return _left(_right(std::forward<Args>(args)...));
        }

        constexpr static Tokens type()
        {
            return Tokens::PipeExpr;
        }
    };

    template<typename Left, typename Right>
    std::enable_if_t<is_pipe_expr<Left>, pipe<decltype(Left::_left), pipe<decltype(Left::_right), Right>>>
    operator<<(Left const& left, Right const& right)
    {
        return { left._left, {left._right, right} };
    }

    // =================================================================================================================

}}