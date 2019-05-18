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

#include <vector>

#include <zacc/compute/core/core.hpp>
#include <zacc/compute/renderer/renderer.hpp>
#include <zacc/compute/transformer/transformer.hpp>

namespace zacc { namespace compute {

    // =================================================================================================================

    struct recorder
    {
        template<typename Target>
        recorder& operator<<(declare_expr<Target> expr)
        {
            declarations.emplace_back([expr]() { return expr_visitor<renderer>::visit(expr);  });

            return *this;
        }

        template<typename Target, typename Expr>
        recorder& operator<<(assign_expr<Target, Expr> expr)
        {
            declarations.emplace_back([expr]() { return expr_visitor<renderer>::visit(expr);  });

            return *this;
        }

        std::vector<std::function<generator()>> declarations;
        std::vector<std::function<generator()>> expressions;

        static recorder& current(){

            static recorder instance;

            return instance;
        }


        friend std::ostream& operator<<(std::ostream& os, const recorder& recorder)
        {
            for(auto d : recorder.declarations)
            {
                os << d() << std::endl;
            }

            for(auto e : recorder.expressions)
            {
                os << e() << std::endl;
            }

            return os;
        }
    };

    // =================================================================================================================

}}