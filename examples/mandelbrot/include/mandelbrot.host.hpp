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

#include<chrono>

#include "interfaces/mandelbrot.hpp"
#include "interfaces/mandelbrot.vanilla.hpp"

#include "system/kernel_dispatcher.hpp"
#include "math/matrix.hpp"
#include "util/color.hpp"

#include "host.hpp"

namespace zacc { namespace examples {
    class mandelbrot_host : public host<mandelbrot, mandelbrot_vanilla>
    {
        using input_container     = typename system::kernel_traits<mandelbrot>::input_container;
        using output_container    = typename system::kernel_traits<mandelbrot>::output_container;

        vec2<float> _cmin;
        vec2<float> _cmax;

        size_t _max_iterations;
    public:

        mandelbrot_host(const sysinfo& sysinfo, vec2<int> dim = { 2048, 2048 }, vec2<float> cmin = { -2, -2 }, vec2<float> cmax = { 2, 2 }, size_t max_iterations = 2048)
                : host(sysinfo, dim), _cmin { cmin }, _cmax { cmax }, _max_iterations { max_iterations }
        {
            using namespace util;

            _gradient = {
                    { -1, color_rgb(0, 0, 0 ) },
                    { 0, color_rgb(66, 30, 15 ) },
                    { 1, color_rgb(25, 7, 26 ) },
                    { 2, color_rgb(9, 1, 47 ) },
                    { 3, color_rgb(4, 4, 73 ) },
                    { 4, color_rgb(0, 7, 100 ) },
                    { 5, color_rgb(12, 44, 138 ) },
                    { 6, color_rgb(24, 82, 177 ) },
                    { 7, color_rgb(57, 125, 209 ) },
                    { 8, color_rgb(134, 181, 229 ) },
                    { 9, color_rgb(211, 236, 248 ) },
                    { 10, color_rgb(241, 233, 191 ) },
                    { 11, color_rgb(248, 201, 95 ) },
                    { 12, color_rgb(255, 170, 0 ) },
                    { 13, color_rgb(204, 128, 0 ) },
                    { 14, color_rgb(153, 87, 0 ) },
                    { 15, color_rgb(106, 52, 3 ) }
            };
        }

    protected:

        virtual void configure() override
        {
            configure_kernels(_dim, _cmin, _cmax, _max_iterations);
        }

        virtual util::color_rgb map_value(typename output_container::value_type value) override
        {
            return _gradient.getColor(value % 32);
        }

    private:
        util::gradient1D _gradient;
    };

}}