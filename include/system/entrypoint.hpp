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
#include <memory>
#include "backend/all.hpp"

namespace zacc { namespace system {

    template<typename dispatcher>
    std::shared_ptr<entrypoint> resolve_entrypoint();

#if defined(ZACC_AVX512)
    template<>
    std::shared_ptr<entrypoint> resolve_entrypoint<zacc::avx512::types<zacc::branches::avx512>>();
#endif
#if defined(ZACC_AVX2)
    template<>
    std::shared_ptr<entrypoint> resolve_entrypoint<zacc::avx2::types<zacc::branches::avx2>>();
#endif
#if defined(ZACC_AVX)
    template<>
    std::shared_ptr<entrypoint> resolve_entrypoint<zacc::avx::types<zacc::branches::avx1>>();
#endif
#if defined(ZACC_SSE)
    template<>
    std::shared_ptr<entrypoint> resolve_entrypoint<zacc::sse::types<zacc::branches::sse41_fma4>>();
    template<>
    std::shared_ptr<entrypoint> resolve_entrypoint<zacc::sse::types<zacc::branches::sse41_fma3>>();
    template<>
    std::shared_ptr<entrypoint> resolve_entrypoint<zacc::sse::types<zacc::branches::sse41>>();

    template<>
    std::shared_ptr<entrypoint> resolve_entrypoint<zacc::sse::types<zacc::branches::sse3>>();

    template<>
    std::shared_ptr<entrypoint> resolve_entrypoint<zacc::sse::types<zacc::branches::sse2>>();
#endif
#if defined(ZACC_SCALAR)
    template<>
    std::shared_ptr<entrypoint> resolve_entrypoint<zacc::scalar::types<zacc::branches::scalar>>();
#endif
}}
