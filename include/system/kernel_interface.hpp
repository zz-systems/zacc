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

// @file mandelbrot_engine.hpp

#include "zacc.hpp"
#include "system/entrypoint.hpp"

namespace zacc { namespace system {

    /**
     * Kernel traits - extract information from kernel
     * @tparam KernelInterface
     */
    template<typename KernelInterface>
    struct kernel_traits
    {
        /// Output container
        using output_container = std::remove_reference_t<typename KernelInterface::output_container>;
        /// Input container
        using input_container  = std::remove_reference_t<typename KernelInterface::input_container>;

        /// Kernel name
        static constexpr auto kernel_name() { return KernelInterface::kernel_name(); }
    };

    /**
     * Public kernel interface wrapper.
     * Provides basic operator() implementations for the dispatcher
     * @tparam KernelInterface
     */
    template<typename KernelInterface>
    struct kernel_interface : KernelInterface
    {
        /// Output container
        using output_container = typename kernel_traits<KernelInterface>::output_container;
        /// Input container
        using input_container  = typename kernel_traits<KernelInterface>::input_container;

        /**
         * Configure kernel (Any argument)
         * @tparam Args any
         * @param args any
         */
        template<typename... Args>
        void operator()(Args&&... args)
        {
            _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

            this->configure(std::forward<Args>(args)...);
        }

        /**
         * Process (process input, produce output)
         * @param input
         * @param output
         */
        void operator()(const input_container &input, output_container &output)
        {
            _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

            this->run(input, output);
        }

        /**
         * Generate (output only)
         * @param output
         */
        void operator()(output_container &output)
        {
            _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

            this->run(output);
        }
    };
}}