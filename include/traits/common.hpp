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

#include "common.hpp"
#include <sstream>

namespace zacc {

    enum class traits : long long {
        Arithmetic = 1 << 0,
        Fused_Multiplication = 1 << 1,
        Bitwise = 1 << 2,
        Bitwise_Shift = 1 << 3,
        Logical = 1 << 4,
        Comparison = 1 << 5,
        Conditional = 1 << 6,

        IO = 1 << 7,
        Iteratable = 1 << 8,
        Printable = 1 << 9,
        Indexable = 1 << 10,
        Convertable = 1 << 11,
        Numeric = 1 << 12
    };

    /**
     * @brief provides begin(), end() iterators to attached type
     */
    struct iteratable {
        /**
         * @brief iteratable trait implementation
         * @tparam base_t base type (e.g previous trait)
         */
        template<typename base_t>
        struct impl : public base_t {
            FORWARD(impl);

            REQUIRE(traits::IO);
            TRAIT(traits::Iteratable);

            using iterator = typename base_t::extracted_t::iterator;

            /**
             * @brief create a snapshot of current value
             * @return snapshot's begin iterator
             */
            iterator begin() {
                _snapshot = base_t::data();
                return _snapshot.begin();
            }

            /**
             * @return snapshot's end iterator
             */
            iterator end() { return _snapshot.end(); }

        private:
            typename base_t::extracted_t _snapshot;
        };
    };


    /**
     * @brief provides pretty-print functionality for zacc types
     */
    struct printable {
        /**
         * @brief printable trait implementation
         * @tparam base_t base type (e.g previous trait)
         */
        template<typename base_t>
        struct impl : public base_t {
            FORWARD(impl);

            REQUIRE(traits::Iteratable);
            TRAIT(traits::Printable);

            /**
             * @brief converts current data to string representation
             * @return string, e.g [4, 5, 6, 7] for a 4x int vector
             */
            std::string to_string() const {
                std::stringstream ss;

                if (base_t::is_vector)
                    ss << "[ ";

                for (auto entry : base_t::data())
                    ss << entry << " ";

                if (base_t::is_vector)
                    ss << "]";

                return ss.str();
            }

            /**
             * @brief prints current value to target stream
             * @param os target stream
             * @param data printable trait
             * @return target stream
             */
            friend std::ostream &operator<<(std::ostream &os, const impl data) {
                os << data.to_string();

                return os;
            }
        };
    };


    /**
     * @brief provides basic conversion functionality
     */
    struct convertable {
        /**
         * @brief convertable trait implementation
         * @tparam base_t base type (e.g previous trait)
         */
        template<typename base_t>
        struct impl : public base_t {
            FORWARD(impl);

            TRAIT(traits::Convertable);

            auto as_bool() const noexcept
            {
                return bval<impl, typename base_t::mask_t>(*this);
            }
        };
    };
}