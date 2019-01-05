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

#include "interfaces/julia.hpp"

#include "system/kernel_dispatcher.hpp"
#include "math/matrix.hpp"
#include "util/color.hpp"
#include "util/vector.hpp"

#include "host.hpp"

namespace zacc { namespace examples {

    class julia_host : public host<julia>
    {
        using input_container     = typename system::kernel_traits<julia>::input_container;
        using output_container    = typename system::kernel_traits<julia>::output_container;

    public:

        julia_host(const platform& platform)
                : host(platform, {2048, 2048})
        {
            using namespace util;
            std::vector<std::pair<const float, color_rgb>> colors;

            for(uint8_t i = 0; i < 255; i++)
            {
                colors.push_back({i, color_rgb(uint8_t((i >> 5) * 36), uint8_t((i >> 3 & 7) * 36), uint8_t((i & 3) * 85))});
            }

            _gradient = colors;
        }

    protected:

        virtual void configure() override
        {
            vec2<float> offset = { 0, 0 };
            vec2<float> c = { -0.7, 0.27015 };
            float zoom = 1;
            size_t max_iterations = 2048;

            configure_kernels(_dim, offset, c, zoom, max_iterations);
        }

        virtual util::color_rgb map_value(typename output_container::value_type value) override
        {
            return _gradient.getColor(value % 255);
        }

    private:
        util::gradient1D _gradient;
    };
}}