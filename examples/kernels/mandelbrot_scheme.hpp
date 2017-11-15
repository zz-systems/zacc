//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

// @file mandelbrot_engine.hpp

#include "zacc.hpp"
#include "math/matrix.hpp"
#include "util/algorithm.hpp"
#include "system/branch_entrypoint.hpp"

namespace zacc { namespace examples {

    using namespace math;

    template<typename _Kernel>
    struct kernel_traits
    {
        using output_container_t = std::vector<int>&;
        using input_container_t  = std::vector<int>;

        static constexpr auto kernel_name() { return _Kernel::kernel_name(); }
    };


    struct mandelbrot
    {
        using output_container_t = kernel_traits<mandelbrot>::output_container_t;

        static constexpr auto kernel_name() { return "mandelbrot"; }

        virtual void configure(vec2<int> dim, vec2<float> cmin, vec2<float> cmax, size_t max_iterations) = 0;
        virtual void run(output_container_t output) = 0;

        virtual void operator()(vec2<int> dim, vec2<float> cmin, vec2<float> cmax, size_t max_iterations)
        {
            configure(dim, cmin, cmax, max_iterations);
        }

        virtual void operator()(output_container_t output)
        {
            run(output);
        }
    };

}}