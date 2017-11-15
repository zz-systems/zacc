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
#include "math/complex.hpp"
#include "math/matrix.hpp"
#include "util/algorithm.hpp"
#include "system/branch_entrypoint.hpp"
#include "../../kernel.hpp"

namespace zacc { namespace examples {

    using namespace math;




    template<typename T, std::enable_if_t<zval_traits<T>::is_vector>>
    constexpr auto make_index(T index)
    {
        return make_index_impl(index, std::make_integer_sequence<size_t, zval_traits<T>::size>());
    }

    template<typename T, std::enable_if_t<!zval_traits<T>::is_vector>>
    constexpr auto make_index(T index)
    {
        return index;
    }

    namespace
    {
        template<typename T, size_t... seq, typename enable = void>
        constexpr auto make_index_impl(T index, std::index_sequence<seq...>)
        {
            return index + { seq... };
        }
    }

    template<typename _OutputContainer>
    struct mandelbrot_factory {

        struct mandelbrot_init {
            vec2<int> dim;
            vec2<float> cmin;
            vec2<float> cmax;

            size_t max_iterations;
        };

        struct mandelbrot_run
        {
        };

        DISPATCHED
        struct mandelbrot : kernel<mandelbrot_init, mandelbrot_run, _OutputContainer>
        {
            vec2<zint> _dim;
            vec2<zfloat> _cmin;
            vec2<zfloat> _cmax;

            size_t _max_iterations;

            void configure(mandelbrot_init data) override
            {
                _dim = data.dim;
                _cmax = data.cmax;
                _cmin = data.cmin;

                _max_iterations = data.max_iterations;
            }


            void run(_OutputContainer output, mandelbrot_run) override
            {
                zacc::generate<zint8>(std::begin(output), std::end(output), [this](auto i) {
                    zint ix, iy;
                    std::tie(ix, iy) = reshape_i_xy(make_index<zint>(i), _dim.x);

                    zcomplex<zfloat> c(_cmin.x + ix / (_dim.x - 1.0) * (_cmax.x - _cmin.x),
                                       _cmin.y + iy / (_dim.y - 1.0) * (_cmax.y - _cmin.x));
                    zcomplex<zfloat> z = 0;

                    zfloat done = 0;
                    zint iterations;

                    for (auto j = 0; j < _max_iterations; ++j) {
                        done = z.magnitude() >= 2.0;

                        z = z
                                .when(done)
                                .otherwise(z * z + c);

                        iterations = iterations
                                .when(done)
                                .otherwise(iterations + 1);

                        if (done.is_set())
                            break;
                    }
                });
            }
        };
    };
}}