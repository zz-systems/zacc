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
#include "math/complex.hpp"
#include "system/branch_entrypoint.hpp"
#include "system/remote_activator.hpp"
#include "system/runtime_dispatcher.hpp"
#include "kernel.hpp"

namespace zacc { namespace examples {

    template<typename _InputContainer = _Kernel::input_container_t,
            typename _OutputContainer = _Kernel::output_container_t>
    class dispatcher : system::runtime_dispatcher<dispatcher>

    {
    public:
        dispatcher() noexcept
        {
            _activator = std::make_unique<system::remote_activator>(ZACC_DYLIBNAME, "zacc_create_instance", "zacc_delete_instance");
        }
    private:
        template<typename feature, typename... Args> void dispatch_impl(Args&&... arg)
        {
            if(_kernels.count(feature::value) == 0)
                _kernels[feature::value] = _activator->create_instance<feature, _Kernel>(std::forward<Args>(arg)...);
        }

        template<typename feature, typename... Args> void dispatch_impl(Args&&... arg)
        {
            log_has_kernel<feature>();
            _kernels[feature::value]->configure(std::forward<Args>(arg)...);
        }

        template<typename feature, typename... Args> void dispatch_impl(_InputContainer input, _OutputContainer output, Args&&... arg)
        {
            log_has_kernel<feature>();
            _kernels[feature::value]->run(input, output, std::forward<Args>(arg)...);
        }

        template<typename feature, typename... Args> void dispatch_impl(_OutputContainer output, Args&&... arg)
        {
            log_has_kernel<feature>();
            _kernels[feature::value]->run(output, std::forward<Args>(arg)...);
        }

    private:
        aligned_map<int, std::shared_ptr<_Kernel>> _kernels;
        std::shared_ptr<system::remote_activator> _activator;

        template<typename feature> void log_has_kernel()
        {
            std::cout << "Has kernel: " << std::boolalpha
                      << (_kernels.count(feature::value) != 0)
                      << std::endl;
        }
    };

    template<typename _KernelImpl, typename _InputContainer, typename _OutputContainer>
    auto make_dispatcher()
    {
        return dispatcher<kernel<_KernelImpl, _InputContainer, _OutputContainer>>();
    };

}}