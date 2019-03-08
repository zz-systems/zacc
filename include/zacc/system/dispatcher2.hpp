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


#include <zacc/system/kernel_activator.hpp>

#include <zacc/backend/intrin.hpp>
#include <zacc/util/algorithm.hpp>
#include <zacc/system/feature.hpp>
#include <zacc/system/dl.hpp>

#include <tuple>

namespace zacc { namespace system {

        /**
         * @brief Provides functionality to select a arch to run during runtime
         * Inject your own logic via subclassing (crtp) or simply using a type alias
         * @code using engine_dispatcher = runtime_dispatcher<engine_dispatcher_impl>;
         * @tparam _Impl
         */
        template<typename Kernel>
        struct dispatcher2 {

            dispatcher2()
                : _activator(std::make_unique<system::kernel_activator>(ZACC_DYLIBNAME,
                                                                        kernel_name() + "_create_instance",
                                                                        kernel_name() + "_delete_instance"))
            {}

            dispatcher2(feature features)
                : dispatcher2(), _features(std::move(features))
            {
            }

            /// Kernel name
            static const std::string kernel_name() { return kernel_traits<Kernel>::kernel_name(); }

            template<typename... Args>
            std::shared_ptr<Kernel> create(Args&&... args) const
            {
                auto a = select_arch();
                return _activator->create_instance<Kernel, system::kernel>(a, std::forward<Args>(args)...);
            }

            std::shared_ptr<Kernel> operator->()
            {
                if(_kernel == nullptr)
                {
                    this->_kernel = create();
                }

                return this->_kernel;
            }

            arch select_arch() const
            {
                feature mask(_features.mask() & kernel_traits<Kernel>::compatible());

                for(auto a : arch::available())
                {
                    if(a.mask.test(mask))
                    {
                        return a;
                    }
                }

                return arch::scalar();
            }

            /**
             * @brief displays the selected arch with extended information
             */
            template<typename Arch> void log_branch() const
            {
                log_branch(Arch{});
            }

            void log_branch(arch a) const
            {
                std::clog << "[ARCH DISPATCHER][DISPATCH][" << a.name << "]"
                          << " [" << join(a.mask.active(), ", ") << "]"
                          << std::endl;
            }

            inline const feature& features() const
            {
                return this->_features;
            }

            inline struct feature& features()
            {
                this->_kernel = nullptr;
                return this->_features;
            }


        private:
            struct feature _features;
            std::shared_ptr<Kernel> _kernel;
            std::unique_ptr<system::kernel_activator> _activator;
        };

//        template<typename KernelInterface, typename... Args>
//        std::shared_ptr<KernelInterface> make_kernel(feature mask, Args&&... args)
//        {
//            auto kernel_name = std::string(kernel_traits<KernelInterface>::kernel_name());
//            auto arch = arch::select(mask);
//
//            kernel_activator activator(ZACC_DYLIBNAME,
//                                       kernel_name + "_create_instance",
//                                       kernel_name + "_delete_instance");
//
//            return activator.create_instance<KernelInterface, system::kernel>(arch, std::forward<Args>(args)...);
//        }

        template<typename KernelInterface, typename... Args>
        std::tuple<arch, std::shared_ptr<KernelInterface>> make_kernel(feature mask, Args&&... args)
        {
            auto kernel_name = std::string(kernel_traits<KernelInterface>::kernel_name());
            auto arch = arch::select(feature(mask & kernel_traits<KernelInterface>::compatible()));

            kernel_activator activator(ZACC_DYLIBNAME,
                                       kernel_name + "_create_instance",
                                       kernel_name + "_delete_instance");

            return { arch, activator.create_instance<KernelInterface, system::kernel>(arch, std::forward<Args>(args)...) };
        }

//        template<typename KernelInterface, typename... Args>
//        std::shared_ptr<KernelInterface> make_kernel(Args&&... args)
//        {
//            return make_kernel<KernelInterface>(sysinfo(), std::forward<Args>(args)...);
//        }
    }}
