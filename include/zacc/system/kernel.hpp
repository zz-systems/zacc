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

#include <zacc.hpp>
#include <zacc/traits/allocatable.hpp>
#include <zacc/system/entrypoint.hpp>

namespace zacc { namespace system {

    template<typename... Ts> struct make_void { typedef void type;};
    template<typename... Ts> using void_t = typename make_void<Ts...>::type;

    /**
    * Kernel traits - extract information from kernel
    * @tparam KernelInterface
    */
    template<typename KernelInterface>
    struct kernel_traits
    {
        using traits = function_traits<decltype(&KernelInterface::run)>;

        /// Output container
        using output_container = std::remove_reference_t<typename traits::template argument<1>::type>;
        /// Input container (same as output container if not specified)
        using input_container  = std::remove_reference_t<typename traits::template argument<(traits::arity > 2 ? 2 : 1)>::type>;

        /// Kernel name
        static constexpr auto kernel_name() { return KernelInterface::name(); }


        template<typename T, typename = void>
        struct kt
        {
            static constexpr feature compatible()
            {
                return feature().set();
            }
        };


        template<typename T>
        struct kt<T, void_t< decltype( T::compatible )> >
        {
            static constexpr feature compatible()
            {
                return T::compatible();
            }
        };

        static constexpr feature compatible()
        {
            return kt<KernelInterface>::compatible();
        }
    };

    /**
    * Public kernel interface wrapper.
    * Provides basic operator() implementations for the dispatcher
    * @tparam KernelInterface
    */
    template<typename KernelInterface>
    struct kernel : public zacc::system::entrypoint
    {
        /**
         * Configure kernel (Any argument)
         * @tparam Args any
         * @param args any
         */
        template<typename... Args>
        void operator()(Args&&... args)
        {
            static_cast<KernelInterface*>(this)->configure(std::forward<Args>(args)...);
        }

        /**
         * Process (process input, produce output)
         * @param input
         * @param output
         */
        template<typename InputContainer, typename OutputContainer>
        void operator()(OutputContainer &output, const InputContainer &input)
        {
            static_cast<KernelInterface*>(this)->run(output, input);
        }

        /**
         * Generate (output only)
         * @param output
         */
        template<typename OutputContainer>
        void operator()(OutputContainer &output)
        {
            static_cast<KernelInterface*>(this)->run(output);
        }
    };

#define KERNEL_IMPL(Kernel) \
    DISPATCHED struct Kernel ## _kernel : Kernel, allocatable<Kernel ## _kernel, arch>

#define REGISTER_KERNEL(Kernel) \
    extern "C" \
    { \
        zacc::system::entrypoint *Kernel ## _create_instance() \
        { \
            return new Kernel ## _kernel<zacc::dispatched_arch>(); \
        } \
        \
        void Kernel ## _delete_instance(zacc::system::entrypoint* instance) \
        { \
            delete instance; \
        } \
    }
}}