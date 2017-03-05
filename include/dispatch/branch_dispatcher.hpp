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

#include "system/platform.hpp"
#include <type_traits>

#include ZACC_MAJOR_BRANCH_INC

/*
#if defined(ZACC_SCALAR)
    #include "backend/scalar/types.hpp"
#elif defined(ZACC_SSE2) || defined(ZACC_SSE3) || defined(ZACC_SSE4) || defined(ZACC_SSE4FMA)
    #include "backend/sse/types.hpp"
#elif defined(ZACC_AVX)
    #include "backend/avx/types.hpp"
#elif defined(ZACC_AVX2)
    #include "backend/avx2/types.hpp"
#elif defined(ZACC_AVX512)
    #include "backend/avx512/types.hpp"
#endif*/


namespace zacc {
    
    struct branch_dispatcher {

        static const uint64_t capability = capability::fill_up_to(capabilities::ZACC_MAX_CAPABILITY);
        using capability_t =  std::integral_constant<uint64_t, capability>;

        using types = ZACC_MAJOR_BRANCH::types<capability>;
    };
}