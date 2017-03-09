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

#include "common.hpp"

namespace zacc { namespace interface {

        template<typename base_t, typename composed_t>
        struct math : public base_t {
            FORWARD(math);

            composed_t abs() { return vabs(*this); }

            composed_t rcp() { return vrcp(*this); }

            composed_t trunc() { return vtrunc(*this); }

            composed_t floor() { return vfloor(*this); }

            composed_t ceil() { return vceil(*this); }

            composed_t round() { return vround(*this); }

            composed_t sqrt() { return vsqrt(*this); }
        };

        template<typename base_t, typename composed_t>
        struct fmath : public base_t {
            FORWARD(fmath);

            //composed_t floor() { return vfloor(*this); }

            //composed_t ceil() { return vceil(*this); }

            //composed_t round() { return vround(*this); }



            //composed_t sqrt() { return vsqrt(*this); }
        };

        template<typename base_t, typename composed_t>
        struct trigonometry : public base_t {
            FORWARD(trigonometry);

            composed_t sin() { return vsin(*this); }
            composed_t cos() { return vcos(*this); }
            composed_t tan() { return vtan(*this); }

            composed_t asin() { return vasin(*this); }
            composed_t acos() { return vacos(*this); }
            composed_t atan() { return vatan(*this); }
        };

    }}