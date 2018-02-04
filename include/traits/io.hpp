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

#include "common.hpp"
#include "memory.h"

namespace zacc { namespace traits {

    /**
     * @brief provides vector load/store definitions
     * @tparam Base base type (e.g previous trait)
     * @tparam Composed final composed type (e.g zfloat32)
     */
    template<typename Base, typename Composed>
    struct io : public Base {

        using zval_t = typename Base::zval_t;
        using bval_t = typename Base::bval_t;

        typedef typename zval_traits<Base>::extracted_t extracted_t;

        FORWARD(io);

        template<typename OutputIt>
        void store (OutputIt result, bval_tag) const
        {
            typename zval_traits<typename Composed::zval_t>::extracted_t data;

            vstore(std::begin(data), static_cast<Composed>(Base::value()));

            for(auto i : data)
                *(result++) = i != 0;
        }

        template<typename OutputIt>
        void store (OutputIt result, zval_tag) const
        {
            vstore(result, static_cast<Composed>(Base::value()));
        }

        template<typename OutputIt>
        void stream (OutputIt result, bval_tag) const
        {
            typename zval_traits<typename Composed::zval_t>::extracted_t data;

            vstore(std::begin(data), static_cast<Composed>(Base::value()));

            for(auto i : data)
                *(result++) = i != 0;
        }

        template<typename OutputIt>
        void stream (OutputIt result, zval_tag) const
        {
            vstream(result, static_cast<Composed>(Base::value()));
        }

        const extracted_t data() const {
            alignas(Base::alignment) extracted_t result;

            store(std::begin(result), typename Base::tag());

            return result;
        }

        template<typename RandomIt, typename index_t>
        static Composed gather(RandomIt input, index_t index)
        {
            return vgather(input, index, Composed());
        }
    };

}}