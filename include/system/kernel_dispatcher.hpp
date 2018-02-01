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



#include "zacc.hpp"
#include "branch_entrypoint.hpp"
#include "remote_activator.hpp"
#include "runtime_dispatcher.hpp"
#include "kernel.hpp"

namespace zacc { namespace system {

    template<typename _Kernel, typename _KernelTraits = system::kernel_traits<_Kernel>>
    class kernel_dispatcher
    {
    public:
        kernel_dispatcher() noexcept
        {
            std::cerr << "loading: " << ZACC_DYLIBNAME << std::endl;
            _activator = std::make_unique<system::remote_activator>(ZACC_DYLIBNAME,
                                                                    std::string(_KernelTraits::kernel_name()) + "_create_instance",
                                                                    std::string(_KernelTraits::kernel_name()) + "_delete_instance");
        }
    protected:
        template<typename feature, typename... Args>
        void dispatch_impl(Args&&... arg)
        {
            log_has_kernel<feature>();
            if(_kernels.count(feature::value) == 0)
                _kernels[feature::value] = _activator->create_instance<feature, _Kernel, system::kernel>(std::forward<Args>(arg)...);

            log_has_kernel<feature>();
            _kernels[feature::value]->operator()(std::forward<Args>(arg)...);
        }

    private:
        aligned_map<int, std::shared_ptr<_Kernel>> _kernels;
        std::unique_ptr<system::remote_activator> _activator;

        template<typename feature> void log_has_kernel()
        {
            std::cout << "Has kernel: " << std::boolalpha
                      << (_kernels.count(feature::value) != 0)
                      << std::endl;
        }
    };

    template<typename _KernelImpl>
    auto make_dispatcher()
    {
        return system::runtime_dispatcher<kernel_dispatcher<_KernelImpl>>();
    };

}}