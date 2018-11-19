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



#include "zacc.hpp"
#include "entrypoint.hpp"
#include "kernel_activator.hpp"
#include "dispatcher.hpp"
#include "kernel.hpp"

namespace zacc { namespace system {

    /**
     * Kernel dispatcher. Activates and dispatches a kernel
     * @todo Activation policy / strategy
     * @tparam Kernel
     */
    template<typename Kernel>
    class kernel_dispatcher
    {
    public:
        /**
         * Constructor
         */
        constexpr kernel_dispatcher() noexcept
        {
            std::cerr << "loading: " << ZACC_DYLIBNAME << std::endl;
            _activator = std::make_unique<system::kernel_activator>(ZACC_DYLIBNAME,
                                                                    //"create_kernel",
                                                                    //"destroy_kernel");
                                                                    std::string(kernel_traits<Kernel>::kernel_name()) + "_create_instance",
                                                                    std::string(kernel_traits<Kernel>::kernel_name()) + "_delete_instance");
        }
    protected:
        /**
         * Instantiate a kernel if necessary and execute
         * @tparam Arch Selected architecture
         * @tparam Args any
         * @param arg any
         */
        template<typename Arch, typename... Args>
        void dispatch_impl(Args&&... arg)
        {
            log_has_kernel<Arch>();

            if(_kernels.count(Arch::value) == 0) {
                //auto name = std::string(kernel_traits<Kernel>::kernel_name()) + "_" + Arch::name();
                //std::cerr << "creating kernel: " << name << std::endl;
                _kernels[Arch::value] = _activator->create_instance<Arch, Kernel, system::kernel>(/*name.c_str(),*/ std::forward<Args>(arg)...);
            }
            log_has_kernel<Arch>();
            _kernels[Arch::value]->operator()(std::forward<Args>(arg)...);
        }

    private:
        aligned_map<int, std::shared_ptr<Kernel>> _kernels;
        std::unique_ptr<system::kernel_activator> _activator;

        template<typename Arch> void log_has_kernel()
        {
            std::cout << "Has kernel for arch " << Arch::name() << ": " << std::boolalpha
                      << (_kernels.count(Arch::value) != 0)
                      << std::endl;
        }
    };

    template<typename KernelImpl>
    auto make_dispatcher()
    {
        return system::dispatcher<kernel_dispatcher<KernelImpl>>();
    };

}}