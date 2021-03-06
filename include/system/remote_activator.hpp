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

#include <memory>
#include <string>
#include <map>
#include <cassert>

#include "system/capabilities.hpp"
#include "system/managed_library.hpp"
#include "system/entrypoint.hpp"

namespace zacc { namespace system {

        
    /**
     * Instantiates and destroys a kernel remotely.
     */
    struct remote_activator
    {
        /**
         * Constructor.
         * @param library_name
         * @param create_instance
         * @param delete_instance
         */
        remote_activator(const std::string& library_name, const std::string& create_instance, const std::string& delete_instance)
            : _library_name(library_name), _create_instance(create_instance), _delete_instance(delete_instance)
        {
        }

        /**
         * Instantiate a kernel
         * @tparam Arch selected architecture
         * @tparam KernelImpl kernel implementation
         * @tparam Kernel kernel
         * @tparam Args
         * @param args
         * @return pointer to kernel instance
         */
        template<typename Arch, typename KernelImpl, template<class> class Kernel, typename ...Args>
        std::shared_ptr<KernelImpl> create_instance(Args&&... args)
        {
            auto loader  = this->select_implementation<Arch>();

            assert(loader != nullptr);
            // Pitfall. loader->template ... is required
            auto creator = loader->template resolve_symbol<entrypoint*(Args...)>(this->_create_instance);
            auto deleter = loader->template resolve_symbol<void(entrypoint*)>(this->_delete_instance);

            assert(creator != nullptr);
            assert(deleter != nullptr);

            auto ptr = std::shared_ptr<entrypoint>(creator(std::forward<Args>(args)...), deleter);

            return std::static_pointer_cast<KernelImpl>(std::static_pointer_cast<Kernel<KernelImpl>>(ptr));
        }

        /**
        * Instantiate a kernel
        * @tparam Arch selected architecture
        * @tparam KernelImpl kernel implementation
        * @tparam Args
        * @param args
        * @return pointer to kernel instance
        */
        template<typename Arch, typename KernelImpl, typename ...Args>
        std::shared_ptr<KernelImpl> create_instance(Args&&... args)
        {
            auto loader  = this->select_implementation<Arch>();

            assert(loader != nullptr);
            // Pitfall. loader->template ... is required
            auto creator = loader->template resolve_symbol<entrypoint*(Args...)>(this->_create_instance);
            auto deleter = loader->template resolve_symbol<void(entrypoint*)>(this->_delete_instance);

            assert(creator != nullptr);
            assert(deleter != nullptr);

            auto ptr = std::shared_ptr<entrypoint>(creator(std::forward<Args>(args)...), deleter);

            return std::static_pointer_cast<KernelImpl>(ptr);
        }

    protected:
        /**
         *
         * @tparam Arch
         * @return
         */
        template<typename Arch>
        std::shared_ptr<managed_library> select_implementation()
        {
            auto path = this->_library_name;
            size_t dot = path.find_last_of('.');

            if(dot != std::string::npos)
            {
                auto filename   = path.substr(0, dot);
                auto extension  = path.substr().substr(dot + 1);

                path = filename + "." + Arch::name() + "." + extension;
            }

            if(this->_loaded_libraries.count(Arch::value) == 0)
                this->_loaded_libraries[Arch::value] = std::make_shared<managed_library>(path);

            return this->_loaded_libraries[Arch::value];
        }


        std::string _library_name;
        std::string _create_instance;
        std::string _delete_instance;

        std::map<int, std::shared_ptr<managed_library>> _loaded_libraries;
    };
}}