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

#include "util/algorithm.hpp"
#include "platform.hpp"
#include "backend/all.hpp"
#include "system/capabilities.hpp"

namespace zacc {

    template<typename base_t>
    struct runtime_dispatcher : public base_t
    {
        FORWARD(runtime_dispatcher);

        template<typename ...Args>
        void dispatch_some(Args&&... args)
        {
            dispatch(false, std::forward<Args>(args)...);
        }

        template<typename ...Args>
        void dispatch_one(Args&&... args)
        {
            dispatch(true, std::forward<Args>(args)...);
        }

        template<typename ...Args>
        void operator()(bool select_one, Args&&... args)
        {
            dispatch(select_one, std::forward<Args>(args)...);
        }

        template<typename ...Args>
        void dispatch(bool select_one, Args&&... args)
        {
            auto p = &platform::instance();

            _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
            _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

#if defined(ZACC_OPENCL)
            if(p->is_set(capabilities::OPENCL))
            {
                // not implemented yet
                //base_t::dispatch_impl<opencl::types<branches::opencl>>(std::forward<Args>(args)...);
            }
#endif

#if defined(ZACC_AVX512)
            if(p->is_set(capabilities::AVX512))
            {
                // not implemented yet
                //base_t::dispatch_impl<avx512::types<branches::avx512>>(std::forward<Args>(args)...);
            }
#endif

#if defined(ZACC_AVX2)
            if(p->is_set(capabilities::AVX2))
            {
                log_branch<avx2::types<branches::avx2>>();
                base_t::template dispatch_impl<avx2::types<branches::avx2>>(std::forward<Args>(args)...);

                if(select_one)
                    return;
            }
#endif

#if defined(ZACC_AVX)
            if(p->is_set(capabilities::AVX1))
            {
                log_branch<avx::types<branches::avx1>>();
                base_t::template dispatch_impl<avx::types<branches::avx1>>(std::forward<Args>(args)...);

                if(select_one)
                    return;
            }
#endif

#if defined(ZACC_SSE)
            if(p->is_set(capabilities::SSE41))
            {
                if(p->is_set(capabilities::FMA4))
                {
                    log_branch<sse::types<branches::sse41_fma4>>();
                    base_t::template dispatch_impl<sse::types<branches::sse41_fma4>>(std::forward<Args>(args)...);

                    if(select_one)
                        return;
                }

                if(p->is_set(capabilities::FMA3))
                {
                    log_branch<sse::types<branches::sse41_fma3>>();
                    base_t::template dispatch_impl<sse::types<branches::sse41_fma3>>(std::forward<Args>(args)...);

                    if(select_one)
                        return;
                }

                // no fma
                log_branch<sse::types<branches::sse41>>();
                base_t::template dispatch_impl<sse::types<branches::sse41>>(std::forward<Args>(args)...);

                if(select_one)
                    return;
            }

            if(p->is_set(capabilities::SSSE3) && p->is_set(capabilities::SSE3))
            {
                log_branch<sse::types<branches::sse3>>();
                base_t::template dispatch_impl<sse::types<branches::sse3>>(std::forward<Args>(args)...);

                if(select_one)
                    return;
            }

            if(p->is_set(capabilities::SSE2))
            {
                log_branch<sse::types<branches::sse2>>();
                base_t::template dispatch_impl<sse::types<branches::sse2>>(std::forward<Args>(args)...);

                if(select_one)
                    return;
            }
#endif

#if defined(ZACC_SCALAR)
            // scalar
            log_branch<scalar::types<branches::scalar>>();
            base_t::template dispatch_impl<scalar::types<branches::scalar>>(std::forward<Args>(args)...);
#endif
        }

        template<typename ...Args>
        void dispatch_all(Args&&... args)
        {
            _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
            _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

#if defined(ZACC_OPENCL)
            // opencl - not implemented yet
            //base_t::dispatch_impl<zacc::opencl::types<branches::opencl>>(std::forward<Args>(args)...);
#endif
#if defined(ZACC_AVX512)
            // avx512 - not implemented yet
            //base_t::dispatch_impl<zacc::avx512::types<branches::avx512>>(std::forward<Args>(args)...);
#endif
#if defined(ZACC_AVX2)
            // avx2
            base_t::template dispatch_impl<avx2::types<branches::avx2>>(std::forward<Args>(args)...);
#endif
#if defined(ZACC_AVX)
            // avx1
            base_t::template dispatch_impl<avx::types<branches::avx1>>(std::forward<Args>(args)...);
#endif
#if defined(ZACC_SSE)
            // sse41 - fma4
            base_t::template dispatch_impl<sse::types<branches::sse41_fma4>>(std::forward<Args>(args)...);
            // sse41 - fma3
            base_t::template dispatch_impl<sse::types<branches::sse41_fma3>>(std::forward<Args>(args)...);
            // sse41 - no fma
            base_t::template dispatch_impl<sse::types<branches::sse41>>(std::forward<Args>(args)...);

            // sse3
            base_t::template dispatch_impl<sse::types<branches::sse3>>(std::forward<Args>(args)...);
            // sse2
            base_t::template dispatch_impl<sse::types<branches::sse2>>(std::forward<Args>(args)...);
#endif

#if defined(ZACC_SCALAR)
            // scalar
            base_t::template dispatch_impl<scalar::types<branches::scalar>>(std::forward<Args>(args)...);
#endif
        }

    private:
        DISPATCHED void log_branch() const
        {
            std::cout << "Dispatching: " << dispatcher::major_branch_name()
                      << " [" << join(platform::instance().make_capabilities(dispatcher::capability::value), ", ") << "]"
                      << std::endl;
        }
    };

}