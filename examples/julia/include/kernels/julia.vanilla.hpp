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


#include "zacc.hpp"

#include "system/dispatched_arch.hpp"

#include "math/complex.hpp"
#include "math/matrix.hpp"
#include "util/algorithm.hpp"

#include "interfaces/julia.vanilla.hpp"

namespace zacc { namespace examples {

    using namespace math;

    KERNEL_IMPL(julia_vanilla)
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
            vec2<float> center = _dim / 2.0;

            for(int i = 0; i < output.size(); i++)
            // populate output container
            //zacc::generate<int>(std::begin(output), std::end(output), [this](int i)
            {
                // compute 2D-position from 1D-index
                auto pos = reshape<vec2<float>>(i, _dim);

                std::complex<float> z(1.5 * (pos.x() - center.x()) / (_zoom * center.x()) + _offset.x(),
                                      1.0 * (pos.y() - center.y()) / (_zoom * center.y()) + _offset.y());

                int iterations;

                //for (iterations = 0; iterations < _max_iterations && std::abs(z) < 2.0; ++iterations)
                for (iterations = 0; iterations < _max_iterations && (z.real() * z.real() + z.imag() * z.imag()) < 4.0; ++iterations)
                    z = z*z + _c;

                //return iterations;
                output[i] = iterations;
            }//);
        }
    };

    /// implement shared library factory methods
    REGISTER_KERNEL(julia_vanilla);
}}