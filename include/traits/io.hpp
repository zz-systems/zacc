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

#include "memory.h"

#include "util/operators.hpp"

namespace zacc { namespace traits {

    /**
     * @brief provides vector load/store definitions
     * @tparam Base base type (e.g previous trait)
     * @tparam Composed final composed type (e.g zfloat32)
     */
    template<typename Interface, typename Composed, typename Boolean>
    struct io
    {

//        template<typename OutputIt>
//        void store (OutputIt result, bval_tag) const
//        {
//            std::array<bool, Interface::size> data;
//
//            vstore(std::begin(data), *static_cast<const Composed*>(this));
//
//            std::transform(std::begin(data), std::end(data), result, [](auto i) { return i != 0;});
//
////            for(auto i : data)
////                *(result++) = i != 0;
//        }

        template<typename OutputIt>
        void store (OutputIt result) const
        {
            vstore(result, *static_cast<const Composed*>(this));
        }

//        template<typename OutputIt>
//        void stream (OutputIt result, bval_tag) const
//        {
//            std::array<bool, Interface::size> data;
//
//            vstore(std::begin(data), *static_cast<const Composed*>(this));
//
//            std::transform(std::begin(data), std::end(data), result, [](auto i) { return i != 0;});
////            for(auto i : data)
////                *(result++) = i != 0;
//        }

        template<typename OutputIt>
        void stream (OutputIt result) const
        {
            vstream(result, *static_cast<const Composed*>(this));
        }

        template <bool Cond = is_zval<Interface>::value, typename std::enable_if<Cond, void**>::type = nullptr>
        const typename Interface::extracted_type data() const {
            alignas(Interface::alignment) typename Interface::extracted_type result;

            store(std::begin(result));

            return result;
        }

        template <bool Cond = is_bval<Interface>::value, typename std::enable_if<Cond, void**>::type = nullptr>
        const std::array<bool, Interface::size> data() const {

            alignas(Interface::alignment) typename Interface::extracted_type data;
            std::array<bool, Interface::size> result;

            store(std::begin(data));

            std::transform(std::begin(data), std::end(data), std::begin(result), [](auto i) { return static_cast<bool>(i);});

            return result;
        }

        template<typename RandomIt, typename index_t>
        static Composed gather(RandomIt input, index_t index)
        {
            return vgather(input, index, Composed());
        }
    };

}}