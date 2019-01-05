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

#include "util/algorithm.hpp"
#include "platform.hpp"
#include "system/platform.hpp"
#include "system/dlloader.hpp"

namespace zacc { namespace system {

    /**
     * @brief Provides functionality to select a arch to run during runtime
     * Inject your own logic via subclassing (crtp) or simply using a type alias
     * @code using engine_dispatcher = runtime_dispatcher<engine_dispatcher_impl>;
     * @tparam _Impl
     */
    template<typename _Impl>
    struct dispatcher : public _Impl {
        //FORWARD2(dispatcher, _Impl);

        dispatcher()
                : _Impl() {}

        dispatcher(platform platform)
                : _Impl(), _platform(std::move(platform))
        {
        }

        /**
         * @brief execute all _valid_ code paths
         */
        template<typename ...Args>
        arch dispatch_some(Args &&... args) {
            return dispatch(false, std::forward<Args>(args)...);
        }

        /**
         * @brief execute one _valid_ code path (highest featureset)
         */
        template<typename ...Args>
        arch dispatch_one(Args &&... args) {
            return dispatch(true, std::forward<Args>(args)...);
        }

        /**
         * @brief execute all or one _valid_ code paths (highest featureset)
         * @param select_one if ture, only one path will be executed
         */
        template<typename ...Args>
        arch operator()(bool select_one, Args &&... args) {
            return dispatch(select_one, std::forward<Args>(args)...);
        }

        /**
         * @brief execute all or one _valid_ code paths (highest featureset)
         * @param select_one if ture, only one path will be executed
         */
        template<typename... Args>
        arch dispatch(bool select_one, Args&& ...args) {
            arch selected_arch;

            auto can_select = [select_one, &selected_arch](){ return !select_one || selected_arch.is_none(); };

            selected_arch = (can_select() ? dispatch_opencl(select_one, std::forward<Args>(args)...) : selected_arch);
            selected_arch = (can_select() ? dispatch_avx(select_one, std::forward<Args>(args)...) : selected_arch);
            selected_arch = (can_select() ? dispatch_sse(select_one, std::forward<Args>(args)...) : selected_arch);
            selected_arch = (can_select() ? dispatch_scalar(select_one, std::forward<Args>(args)...) : selected_arch);

            return selected_arch;
        }

        template<typename... Args>
        arch dispatch_opencl(bool select_one, Args &&...args)
        {
            arch selected_arch;

#if defined(ZACC_OPENCL)
            if(_platform.is_set(features::OPENCL))
            {
                selected_arch = dispatch_branch<arch::opencl>(std::forward<Args>(args)...);
            }
#endif

            return selected_arch;
        }

        template<typename... Args>
        arch dispatch_avx(bool select_one, Args &&...args)
        {
            arch selected_arch;

#if defined(ZACC_AVX512)

            _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

            if(p->is_set(features::AVX512))
            {
                selected_arch = dispatch_branch<arch::avx512>(std::forward<Args>(args)...);

                if (select_one)
                    return selected_arch;
            }
#endif

#if defined(ZACC_AVX2)

            _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

            if (_platform.is_set(features::AVX2)) {
                selected_arch = dispatch_branch<arch::avx2>(std::forward<Args>(args)...);

                if (select_one)
                    return selected_arch;
            }
#endif

#if defined(ZACC_AVX)

            _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

            if(_platform.is_set(features::AVX1))
            {
                if(_platform.is_set(features::FMA3))
                {
                    selected_arch = dispatch_branch<arch::avx1_fma3>(std::forward<Args>(args)...);

                    if (select_one)
                        return selected_arch;
                }

                selected_arch = dispatch_branch<arch::avx1>(std::forward<Args>(args)...);
            }
#endif

            return selected_arch;
        }

        template<typename... Args>
        arch dispatch_sse(bool select_one, Args &&...args)
        {
            arch selected_arch;

#if defined(ZACC_SSE)

            _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

            if (_platform.is_set(features::SSE41)) {
                if (_platform.is_set(features::FMA4)) {
                    selected_arch = dispatch_branch<arch::sse41_fma4>(std::forward<Args>(args)...);

                    if (select_one)
                        return selected_arch;
                }

                if (_platform.is_set(features::FMA3)) {
                    selected_arch = dispatch_branch<arch::sse41_fma3>(std::forward<Args>(args)...);

                    if (select_one)
                        return selected_arch;;
                }

                // no fma
                selected_arch = dispatch_branch<arch::sse41>(std::forward<Args>(args)...);

                if (select_one)
                    return selected_arch;
            }

            if (_platform.is_set(features::SSSE3) && _platform.is_set(features::SSE3)) {
                selected_arch = dispatch_branch<arch::sse3>(std::forward<Args>(args)...);

                if (select_one)
                    return selected_arch;
            }

            if (_platform.is_set(features::SSE2)) {
                selected_arch = dispatch_branch<arch::sse2>(std::forward<Args>(args)...);
            }
#endif

            return selected_arch;
        }

        template<typename... Args>
        arch dispatch_scalar(bool select_one, Args &&...args)
        {
            arch selected_arch;

#if defined(ZACC_SCALAR)
            selected_arch = dispatch_branch<arch::scalar>(std::forward<Args>(args)...);
#endif

            return selected_arch;
        }


        template<typename Arch, typename... Args>
        arch dispatch_branch(Args&& ...args)
        {
            log_branch<Arch>();
            _Impl::template dispatch_impl<Arch>(std::forward<Args>(args)...);
            log_branch_end<Arch>();

            return Arch {};
        }
        /**
         * @brief displays the selected arch with extended information
         */
        template<typename arch> void log_branch() const
        {
            std::cout << "Dispatching: " << arch::name()
                      << " [" << join(_platform.make_capabilities(arch::value), ", ") << "]"
                      << std::endl;
        }

        /**
         * @brief displays the selected arch with extended information
         */
        template<typename arch> void log_branch_end() const
        {
            std::cout << "Dispatched: " << arch::name()
                      << " [" << join(_platform.make_capabilities(arch::value), ", ") << "]"
                      << std::endl;
        }

        inline const platform& platform() const
        {
            return this->_platform;
        }

        inline struct platform& platform()
        {
            return this->_platform;
        }



    private:


        struct platform _platform;
    };
}}
