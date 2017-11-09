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

DISPATCHED class mandelbrot_engine : zacc::system::entrypoint
{
public:
    std::size_t width, height;

    zfloat cxmin, cxmax, cymin, cymax;
    zfloat set_color, non_set_color;

    void run(float *target)
    {
        zacc::generate(target, target + width * height, [this](auto i)
        {
            zint ix = i % width;
            zint iy = i / width;

            vec2<zfloat> c =
                    {
                            cxmin + ix / (width  - 1.0) * (cxmax - cxmin),
                            cymin + iy / (height - 1.0) * (cymax - cymin)
                    };

            vec2<zfloat> z = 0;

            zfloat limit = 0;

            zint iterations = 0;

            for(auto j = 0; j < max_iterations; ++j)
            {
                limit = z.magnitude() >= 2.0;

                z = z
                        .when(limit)
                        .otherwise(z * z + c);

                iterations = iterations
                        .when(limit)
                        .otherwise(iterations + 1);

                if(limit.is_set())
                    break;
            }

            return set_color
                    .when(iterations == max_iterations)
                    .otherwise(non_set_color);
        })
    }
};