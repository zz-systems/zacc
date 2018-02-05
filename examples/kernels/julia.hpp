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

// @file mandelbrot_engine.hpp

#include "zacc.hpp"
#include "math/complex.hpp"
#include "math/matrix.hpp"
#include "util/algorithm.hpp"
#include "system/kernel.hpp"
#include "../interfaces/julia.hpp"

namespace zacc { namespace examples {

    using namespace math;

    DISPATCHED struct julia_kernel : system::kernel<julia>,
                                     allocatable<julia_kernel, arch>
    {
        vec2<zint> _dim;
        vec2<zfloat> _offset;
        zcomplex<zfloat> _c;
        zfloat _zoom;

        size_t _max_iterations;

        virtual void configure(vec2<int> dim, vec2<float> offset, vec2<float> c, float zoom, size_t max_iterations) override
        {
            _dim = dim;
            _offset = offset;
            _c = { c.x, c.y };
            _zoom = zoom;

            _max_iterations = max_iterations;
        }


        virtual void run(mandelbrot::output_container &output) override
        {
            vec2<zfloat> center = _dim / 2.0;

            zacc::generate<zint>(std::begin(output), std::end(output), [this, center](auto i)
            {
                // compute 2D-position from 1D-index
                auto pos = reshape<vec2<zfloat>>(make_index<zint>(zint(i)), _dim);

                zcomplex<zfloat> z(1.5 * (pos.x - center.x) / (_zoom * center.x) + _offset.x,
                                   1.0 * (pos.y - center.y) / (_zoom * center.y) + _offset.y);

                bfloat done = false;
                zint iterations = 0;

                for (size_t j = _max_iterations; j > 1; --j)
                {
                    // done when magnitude is >= 2 (or square magnitude is >= 4)
                    done = done || z.sqr_magnitude() >= 4.0;

                    // compute next complex if not done
                    z = z
                           .when(done)
                           .otherwise(z * z + _c);

                    // increment if not done
                    iterations = iterations
                            .when(done)
                            .otherwise(iterations + 1);

                    // break if all elements are not zero
                    if (is_set(done))
                        break;
                }

                return iterations;
            });
        }
    };

}}