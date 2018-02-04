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


#include <sstream>
#include "util/macros.hpp"

namespace zacc {

//    enum class traits : long long {
//        Arithmetic = 1 << 0,
//        Fused_Multiplication = 1 << 1,
//        Bitwise = 1 << 2,
//        Bitwise_Shift = 1 << 3,
//        Logical = 1 << 4,
//        Comparison = 1 << 5,
//        Conditional = 1 << 6,
//
//        IO = 1 << 7,
//        Iteratable = 1 << 8,
//        Printable = 1 << 9,
//        Indexable = 1 << 10,
//        Convertable = 1 << 11,
//        Numeric = 1 << 12
//    };

    /**
     * @brief provides begin(), end() iterators to attached type
     */
    struct iteratable {
        /**
         * @brief iteratable trait implementation
         * @tparam Base base type (e.g previous trait)
         */
        template<typename Base>
        struct impl : public Base
        {
            using zval_t = typename Base::zval_t;
            using bval_t = typename Base::bval_t;


            FORWARD(impl);

#ifdef EXPERIMENTAL_SNAPSHOT_COPY
            impl(const zval_t& other) : Base(other), _has_snapshot(other._has_snapshot)
            {
                if(other._has_snapshot)
                {
                    _snapshot = other._snapshot;
                }
            }

            impl(zval_t&& other) : Base(std::move(other)), _snapshot(std::move(other._snapshot)), _has_snapshot(other._has_snapshot)
            {
            }
#endif
            /**
             * @brief create a snapshot of current value
             * @return snapshot's begin iterator
             */
            auto begin() const
            {
#ifdef EXPERIMENTAL_SNAPSHOT_COPY
                if(!_has_snapshot)
                {
#endif
                    _snapshot = Base::data();

#ifdef EXPERIMENTAL_SNAPSHOT_COPY
                    _has_snapshot = true;
                }
#endif

                return _snapshot.begin();
            }

            /**
             * @return snapshot's end iterator
             */
            auto end() const { return _snapshot.end(); }

        private:
            mutable typename Base::extracted_t _snapshot;
#ifdef EXPERIMENTAL_SNAPSHOT_COPY
            mutable bool _has_snapshot;
#endif
        };
    };

    template<typename _Data>
    struct enumerable //: std::decay_t<_Data>
    {
        using iterator          = decltype(std::begin(std::declval<_Data>().data()));
        using const_iterator    = decltype(std::begin(std::declval<const _Data&>().data()));

        /**
         *
         * @param rhs
         */
        constexpr enumerable(_Data&& rhs)
                : _snapshot(std::move(rhs.data()))
        {}

        /**
         * @brief create a snapshot of current value
         * @return snapshot's begin iterator
         */
        constexpr auto begin() const {
            return _snapshot.begin();
        }

        /**
         * @return snapshot's end iterator
         */
        constexpr auto end() const {
            return _snapshot.end();
        }

    private:
        const decltype(std::declval<_Data>().data()) _snapshot;
    };

    template<typename T>
    constexpr auto make_iterable(T&& source)
    {
        return enumerable<T>(std::forward<T>(source));
    };


    /**
     * @brief provides pretty-print functionality for zacc types
     */
    struct printable {
        /**
         * @brief printable trait implementation
         * @tparam Base base type (e.g previous trait)
         */
        template<typename Base>
        struct impl : public Base {
            FORWARD(impl);

            using zval_t = typename Base::zval_t;
            using bval_t = typename Base::bval_t;

            /**
             * @brief converts current data to string representation
             * @return string, e.g [4, 5, 6, 7] for a 4x int vector
             */
            std::string to_string() const {
                std::stringstream ss;

                if (Base::is_vector)
                    ss << "[ ";

                for (auto entry : Base::data())
                    ss << entry << " ";

                if (Base::is_vector)
                    ss << "]";

                return ss.str();
            }

            /**
             * @brief prints current value to target stream
             * @param os target stream
             * @param data printable trait
             * @return target stream
             */
            friend std::ostream &operator<<(std::ostream &os, const impl &data) {
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
         * @tparam Base base type (e.g previous trait)
         */
        template<typename Base>
        struct impl : public Base {
            FORWARD(impl);

            using zval_t = typename Base::zval_t;
            using bval_t = typename Base::bval_t;

            auto as_bool() const noexcept
            {
                //return make_bval(*this, last_operation::undefined);
                //return *this != 0;
                return make_boolean(*this);
            }
        };
    };
}