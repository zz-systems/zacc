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

#include "system/dispatched_arch.hpp"

#include "math/complex.hpp"
#include "math/matrix.hpp"
#include "util/algorithm.hpp"

#include "interfaces/julia.sse.hpp"

namespace zacc { namespace examples {

    using namespace math;

    KERNEL_IMPL(julia_sse)
    {
        vec2<int> _dim;
        vec2<float> _offset;
        std::complex<float> _c;
        float _zoom;

        size_t _max_iterations;

        virtual void configure(vec2<int> dim, vec2<float> offset, vec2<float> c, float zoom, size_t max_iterations) override
        {
            _dim = dim;
            _offset = offset;
            _c = { c.x(), c.y() };

            _zoom = zoom;

            _max_iterations = max_iterations;
        }

        virtual void run(std::vector<int> &output) override
        {
            // TODO;
        }
    };

    /// implement shared library factory methods
    REGISTER_KERNEL(julia_sse);
}}