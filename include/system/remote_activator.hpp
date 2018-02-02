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

        template<typename F>
        struct S;

        template<typename R, typename... Args>
        struct S<R(Args...)> {
            using type = R(*)(Args...);
        };


        /**
     *
     */
    class remote_activator
    {
        std::string _library_name;
        std::string _create_instance;
        std::string _delete_instance;

        std::map<int, std::shared_ptr<managed_library>> _loaded_libraries;

    public:
        /**
         *
         * @param library_name
         * @param create_instance
         * @param delete_instance
         */
        remote_activator(const std::string& library_name, const std::string& create_instance, const std::string& delete_instance)
            : _library_name(library_name), _create_instance(create_instance), _delete_instance(delete_instance)
        {

        }

        /**
         *
         * @tparam branch
         * @return
         */
        template<typename branch>
        std::shared_ptr<managed_library> branch_library()
        {
            auto path = this->_library_name;
            size_t dot = path.find_last_of(".");

            if(dot != std::string::npos)
            {
                auto filename   = path.substr(0, dot);
                auto extension  = path.substr().substr(dot + 1);

                path = filename + "." + branch::branch_name() + "." + extension;
            }

            if(this->_loaded_libraries.count(branch::value) == 0)
                this->_loaded_libraries[branch::value] = std::make_shared<managed_library>(path);

            return this->_loaded_libraries[branch::value];
        }

        /**
         *
         * @tparam branch
         * @tparam concrete_type
         * @tparam Args
         * @param args
         * @return
         */
        template<typename branch, typename concrete_type, template<class> class kernel, typename ...Args>
        std::shared_ptr<concrete_type> create_instance(Args&&... args)
        {
            auto loader  = this->branch_library<branch>();

            assert(loader != nullptr);
            // Pitfall. loader->template ... is required
            auto creator = loader->template resolve_symbol<entrypoint*(Args...)>(this->_create_instance);
            auto deleter = loader->template resolve_symbol<void(entrypoint*)>(this->_delete_instance);

            assert(creator != nullptr);
            assert(deleter != nullptr);


            //std:: cerr << creator(std::forward<Args>(args)...) << std::endl;
            auto ptr = std::shared_ptr<entrypoint>(creator(std::forward<Args>(args)...), deleter);

            return std::static_pointer_cast<concrete_type>(std::static_pointer_cast<kernel<concrete_type>>(ptr));
        }

        /**
        *
        * @tparam branch
        * @tparam concrete_type
        * @tparam Args
        * @param args
        * @return
        */
        template<typename branch, typename concrete_type, typename ...Args>
        std::shared_ptr<concrete_type> create_instance(Args&&... args)
        {
            auto loader  = this->branch_library<branch>();

            assert(loader != nullptr);
            // Pitfall. loader->template ... is required
            auto creator = loader->template resolve_symbol<entrypoint*(Args...)>(this->_create_instance);
            auto deleter = loader->template resolve_symbol<void(entrypoint*)>(this->_delete_instance);

            assert(creator != nullptr);
            assert(deleter != nullptr);

            auto ptr = std::shared_ptr<entrypoint>(creator(std::forward<Args>(args)...), deleter);

            return std::static_pointer_cast<concrete_type>(ptr);
        }
    };
}}