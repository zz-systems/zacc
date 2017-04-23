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

#include "platform.hpp"

namespace zacc {

    template<typename base_t>
    struct runtime_dispatcher : public base_t
    {
        template<typename Args... args>
        void dispatch(Args... args)
        {
            auto p = &platform::instance();

            if(p->is_set(capabilities::OPENCL))
            {
                // not implemented yet
                //base_t::execute<opencl::types<opencl::value>(std::forward<Args>(args)...);
            }
            else if(p->is_set(capabilities::AVX512))
            {
                // not implemented yet
                //base_t::execute<avx512::types<avx512::value>(std::forward<Args>(args)...);
            }
            else if(p->is_set(capabilities::AVX2))
            {
                base_t::execute<avx::types<avx2::value>(std::forward<Args>(args)...);
            }
            else if(p->is_set(capabilities::AVX1))
            {
                base_t::execute<avx::types<avx1::value>(std::forward<Args>(args)...);
            }
            else if(p->is_set(capabilities::SSE41))
            {
                if(p->is_set(capabilities::FMA4))
                {
                    base_t::execute<sse::types<sse41fma4::value>(std::forward<Args>(args)...);
                }
                else if(p->is_set(capabilities::FMA3))
                {
                    base_t::execute<sse::types<sse41fma3::value>(std::forward<Args>(args)...);
                }
                else
                {
                    base_t::execute<sse::types<sse41::value>(std::forward<Args>(args)...);
                }
            }
            else if(p->is_set(capabilities::SSSE3) && p->is_set(capabilities::SSE3))
            {
                base_t::execute<sse::types<sse3::value>(std::forward<Args>(args)...);
            }
            else if(p->is_set(capabilities::SSE2))
            {
                base_t::execute<sse::types<sse2::value>(std::forward<Args>(args)...);
            }
            else
            {
                base_t::execute<scalar::types<scalar::value>(std::forward<Args>(args)...);
            }
        }
    };

}