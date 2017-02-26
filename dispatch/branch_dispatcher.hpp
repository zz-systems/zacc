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
#include "capability_dispatcher.hpp"

#include "../backend/scalar/types.hpp"
#include "../backend/sse/types.hpp"
#include "../backend/avx/types.hpp"
#include "../backend/avx2/types.hpp"
#include "../backend/avx512/types.hpp"

namespace zacc {

    template<uint64_t capability = 0>
    struct branch_dispatcher {

        using dispatcher = capability_dispatcher<capability>

        template<typename branch = scalar::types>
        using types = std::enable_if_t<!dispatcher::has_SSE && !dispatcher::has_AVX && !dispatcher::has_AVX512 && !dispatcher::has_OPENCL, branch<capability>>;

        template<typename branch = sse::types>
        using types = std::enable_if_t<dispatcher::has_SSE && !dispatcher::has_AVX && !dispatcher::has_AVX512 && !dispatcher::has_OPENCL, branch<capability>>;

        template<typename branch = avx::types>
        using types = std::enable_if_t<dispatcher::has_AVX && !dispatcher::has_AVX2 && !dispatcher::has_AVX512 && !dispatcher::has_OPENCL, branch<capability>>;

        template<typename branch = avx2::types>
        using types = std::enable_if_t<dispatcher::has_AVX && dispatcher::has_AVX2 && !dispatcher::has_AVX512 && !dispatcher::has_OPENCL, branch<capability>>;

        template<typename branch = avx512::types>
        using types = std::enable_if_t<dispatcher::has_AVX512 && !dispatcher::has_OPENCL, branch<capability>>;

        template<typename branch = opencl::types>
        using types = std::enable_if_t<dispatcher::has_OPENCL, branch<capability>>;
    };
}