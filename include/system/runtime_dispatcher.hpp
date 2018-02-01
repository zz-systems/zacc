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
#include "system/capabilities.hpp"
#include "system/runtime_loader.hpp"

namespace zacc { namespace system {

    /**
     * @brief Provides functionality to select a branch to run during runtime
     * Inject your own logic via subclassing (crtp) or simply using a type alias
     * @example using engine_dispatcher = runtime_dispatcher<engine_dispatcher_impl>;
     * @tparam _Impl
     */
    template<typename _Impl>
    struct runtime_dispatcher : public _Impl
    {
        FORWARD2(runtime_dispatcher, _Impl);
        /**
         * @brief execute all _valid_ code paths
         */
        template<typename ...Args>
        void dispatch_some(Args&&... args)
        {
            dispatch(false, std::forward<Args>(args)...);
        }

        /**
         * @brief execute one _valid_ code path (highest featureset)
         */
        template<typename ...Args>
        void dispatch_one(Args&&... args)
        {
            dispatch(true, std::forward<Args>(args)...);
        }

        /**
         * @brief execute all or one _valid_ code paths (highest featureset)
         * @param select_one if ture, only one path will be executed
         */
        template<typename ...Args>
        void operator()(bool select_one, Args&&... args)
        {
            dispatch(select_one, std::forward<Args>(args)...);
        }

        /**
         * @brief execute all or one _valid_ code paths (highest featureset)
         * @param select_one if ture, only one path will be executed
         */
        template<typename ...Args>
        void dispatch(bool select_one, Args&&... args)
        {
            auto p = &platform::global();

#if defined(ZACC_OPENCL)
            if(p->is_set(capabilities::OPENCL))
            {
                // not implemented yet
                //_Impl::dispatch_impl<opencl::types<branches::opencl>>(std::forward<Args>(args)...);
            }
#endif

#if defined(ZACC_AVX512)
            if(p->is_set(capabilities::AVX512))
            {
                // not implemented yet
                //_Impl::dispatch_impl<avx512::types<branches::avx512>>(std::forward<Args>(args)...);
            }
#endif

#if defined(ZACC_AVX2)
            if(p->is_set(capabilities::AVX2))
            {
                log_branch<branches::avx2>();
                _Impl::template dispatch_impl<branches::avx2>(std::forward<Args>(args)...);
                log_branch_end<branches::avx2>();

                if(select_one)
                    return;
            }
#endif

#if defined(ZACC_AVX)
            if(p->is_set(capabilities::AVX1))
            {
                if(p->is_set(capabilities::FMA3))
                {
                    log_branch<branches::avx1_fma3>();
                    _Impl::template dispatch_impl<branches::avx1_fma3>(std::forward<Args>(args)...);
                    log_branch_end<branches::avx1_fma3>();

                    if(select_one)
                        return;
                }

                log_branch<branches::avx1>();
                _Impl::template dispatch_impl<branches::avx1>(std::forward<Args>(args)...);
                log_branch_end<branches::avx1>();
                if(select_one)
                    return;
            }
#endif

#if defined(ZACC_SSE)
            if(p->is_set(capabilities::SSE41))
            {
                if(p->is_set(capabilities::FMA4))
                {
                    log_branch<branches::sse41_fma4>();
                    _Impl::template dispatch_impl<branches::sse41_fma4>(std::forward<Args>(args)...);
                    log_branch_end<branches::sse41_fma4>();

                    if(select_one)
                        return;
                }

                if(p->is_set(capabilities::FMA3))
                {
                    log_branch<branches::sse41_fma3>();
                    _Impl::template dispatch_impl<branches::sse41_fma3>(std::forward<Args>(args)...);
                    log_branch_end<branches::sse41_fma3>();

                    if(select_one)
                        return;
                }

                // no fma
                log_branch<branches::sse41>();
                _Impl::template dispatch_impl<branches::sse41>(std::forward<Args>(args)...);
                log_branch_end<branches::sse41>();

                if(select_one)
                    return;
            }

            if(p->is_set(capabilities::SSSE3) && p->is_set(capabilities::SSE3))
            {
                log_branch<branches::sse3>();
                _Impl::template dispatch_impl<branches::sse3>(std::forward<Args>(args)...);
                log_branch_end<branches::sse3>();

                if(select_one)
                    return;
            }

            if(p->is_set(capabilities::SSE2))
            {
                log_branch<branches::sse2>();
                _Impl::template dispatch_impl<branches::sse2>(std::forward<Args>(args)...);
                log_branch_end<branches::sse2>();

                if(select_one)
                    return;
            }
#endif

#if defined(ZACC_SCALAR)
            // scalar
            log_branch<branches::scalar>();
            _Impl::template dispatch_impl<branches::scalar>(std::forward<Args>(args)...);
            log_branch_end<branches::scalar>();
#endif
        }
        /**
         * @brief displays the selected branch with extended information
         */
        template<typename branch> void log_branch() const
        {
            std::cout << "Dispatching: " << branch::branch_name()
                      << " [" << join(platform::global().make_capabilities(branch::value), ", ") << "]"
                      << std::endl;
        }

        /**
         * @brief displays the selected branch with extended information
         */
        template<typename branch> void log_branch_end() const
        {
            std::cout << "Dispatched: " << branch::branch_name()
                      << " [" << join(platform::global().make_capabilities(branch::value), ", ") << "]"
                      << std::endl;
        }
    };
}}
