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
#include <vector>
#include <map>
#include <ostream>
#include <any>

namespace zacc::compute {

    // =================================================================================================================
    template<typename...>
    class expression;
    // =================================================================================================================

    class recorder
    {

    public:

        unsigned _scope;

        explicit recorder(unsigned scope = 0)
            : _scope { scope  }
        {}

        ~recorder() = default;

        template<typename U>
        std::size_t symbol(U const* var)
        {
            auto id = reinterpret_cast<std::size_t>(var);
            auto it = _symbols.find(id);

            if(it != _symbols.end())
            {
                return it->second;
            }
            else
            {
                auto [rit, suc] = _symbols.insert({id, _symbol_id++});
                return rit->second;
            }
        }

        template<typename U>
        std::size_t add_symbol(U const* var)
        {
            return symbol(var);
        }

        template<typename Var, typename T>
        recorder& add_initializer(Var const* target, std::initializer_list<T> initializer_list)
        {
            _data.emplace(std::next(std::begin(_data), target->id()), std::make_any<std::vector<T>>(initializer_list));

            return *this;
        }

        template<typename Var>
        recorder& add_initializer(Var const* target, expression<> const& source)
        {
            _initializers.emplace(std::next(std::begin(_initializers), target->id()), source);

            return *this;
        }

        template<typename Var>
        recorder& add_initializer(Var const* target, expression<>&& source)
        {
            _initializers.emplace(std::next(std::begin(_initializers), target->id()), std::forward<expression<>>(source));

            return *this;
        }

        template<typename Var>
        recorder& add_assignment(Var const* target, expression<> const& source)
        {
            _assignments.emplace(std::next(std::begin(_assignments), target->id()), source);

            return *this;
        }

        template<typename Var>
        recorder& add_assignment(Var const* target, expression<>&& source)
        {
            _assignments.emplace(std::next(std::begin(_assignments), target->id()), std::forward<expression<>>(source));

            return *this;
        }

        static recorder& current()
        {
            static recorder instance;

            return instance;
        }

        template<typename T, typename Var>
        auto data(Var const* source) const
        {
            return std::any_cast<std::vector<T>>(_data[source->id()]);
        }

        template<typename Expression, typename Var>
        auto initializer(Var const* source) const
        {
            return _initializers[source->id()];
        }

        template<typename Expression, typename Var>
        auto assignment(Var const* source) const
        {
            return _assignments[source->id()];
        }

    private:

        std::size_t _symbol_id;
        std::vector<std::any> _data;
        std::vector<expression<>> _initializers;
        std::vector<expression<>> _assignments;

        std::map<std::size_t, std::size_t> _symbols;
    };

    // =================================================================================================================

}