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
#include <array>

#include "system/capabilities.hpp"

#include "util/type/type_traits.hpp"
#include "util/type/type_casts.hpp"

#include "util/macros.hpp"
#include "util/collections.hpp"


namespace zacc {


    template<typename zval_t, typename bval_t>
    struct bval;



    /**
     * @brief base type for all zacc computation types
     * @tparam _vector_t vector type, like __m128i for sse 4x integer vector
     * @tparam _mask_t mask type for boolean operations
     * @tparam _scalar_t scalar type, like int for sse 4x integer vector
     * @tparam _dim vector size (1 - scalar, 4, 8, 16, ...)
     * @tparam _alignment memory alignment
     * @tparam _capability capabilities
     */
    template<typename _Vector, typename _MaskVector, typename _Element, typename _Tag, size_t _Size, size_t _Alignment, uint64_t _Features = 0xFFFF'FFFF'FFFF'FFFF>
    struct zval : zval_base<_Vector, _MaskVector, _Element, _Tag, _Size, _Alignment, _Features>
    {
        constexpr zval() = default;

        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, _Vector>::value>>
        constexpr zval(const T& other)
                : _value (other)
        {}

        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, _Vector>::value>>
        constexpr zval& operator=(const T& other)
        {
            _value = other;
            return *this;
        }

        //template<typename T, typename enable = std::enable_if_t<!is_zval<T>::value && !is_bval<T>::value>>
        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, _Vector>::value>>
        constexpr zval(T&& value)
                : _value(std::forward<T>(value))
        {}

        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, _Vector>::value>>
        constexpr zval& operator=(T&& other) noexcept
        {
            _value = std::move(other);
            return *this;
        }

        constexpr zval(const zval& other)
                : _value (other._value)
        {}

        constexpr zval& operator=(const zval& other)
        {
            _value = other._value;
            return *this;
        }

        constexpr zval(zval&& other) noexcept
                : _value(std::move(other._value))
        {}

        constexpr zval& operator=(zval&& other) noexcept
        {
            _value = std::move(other._value);
            return *this;
        }

        void swap(zval& other) noexcept
        {
            std::swap(_value, other._value);
        }

//        /**
//             * @brief non-zval constructor
//             * @tparam T
//             * @tparam enable
//             * @param value
//             */
//        template<typename T, typename enable = std::enable_if_t<!is_zval<T>::value && !is_bval<T>::value>>
//        constexpr zval(T value) : _value(value) {}
//
//        /**
//         * @brief zval copy constructor
//         * @tparam T
//         * @tparam enable
//         * @param value
//         */
//        //template<typename T, typename enable = std::enable_if_t<is_zval<T>::value || is_bval<T>::value>>
//        constexpr zval(const zval& value) : _value(value._value) {}
//
//        /**
//         * @brief construct from mask
//         * @param value
//         */
//        constexpr zval(const _MaskVector value) : _value(value) {}
//        /**
//         * @brief cast to underlying vector type
//         * @return raw value
//         */

        template <typename size = std::integral_constant<size_t, _Size>, typename enable = typename std::enable_if<(size::value > 1), _Vector>::type>
        constexpr operator _Vector() const {
            return value();
        }

        /**
         * @brief cast to underlying vector type
         * @return raw value
         */
        constexpr _Vector value() const {
            return _value;
        }
    private:
        alignas(_Alignment) _Vector _value;
    };

    template<typename... Args>
    void swap(zval<Args...>& one, zval<Args...>& other)
    {
        one.swap(other);
    }

    template<typename zval_t>
    using __bval = zval_base
            <
                    typename zval_traits<zval_t>::vector_t,
                    typename zval_traits<zval_t>::mask_vector_t,
                    bool,
                    bval_tag,
                    zval_traits<zval_t>::size,
                    zval_traits<zval_t>::alignment,
                    zval_traits<zval_t>::features
            >;

    /// TODO: separate file, impl traits.
    template<typename zval_t, typename bval_t>
    struct bval : public __bval<zval_t>
    {
        using base_t = __bval<zval_t>;
        using base_t::size;
    public:

        using extracted_t = typename zval_traits<bval>::extracted_t;
        using iterator    = typename extracted_t::iterator;

        /**
         * @brief Converting constructor
         * @see C++11 4.12/1: A zero value, null pointer value,
         * or null member pointer value is converted to false; any other value is converted to true.
         * @param value
         */
        constexpr bval(const zval_t& value) :
                _value(value.value())
        {
            ZTRACE_RAW("bval(zval_t)");
        }


        constexpr bval(const bval_t& value) :
                _value(value)
        {
            ZTRACE_RAW("bval(bval_t)");
        }

        /**
         * @brief
         * @return
         */
        constexpr operator zval_t() const {
            return get_value();
        }

        /**
         * @brief
         * @return
         */
        constexpr operator bval_t() const {
            return get_value();
        }

        constexpr const bval_t get_value() const {
            return _value;
        }

        const extracted_t data() const {
            return array_cast<bool>(_value.data());
        }

        extracted_t data() {
            return array_cast<bool>(_value.data());
        }

        /**
         * @brief create a snapshot of current value
         * @return snapshot's begin iterator
         */
        iterator begin() {
            _snapshot = data();
            return _snapshot.begin();
        }

        /**
         * @return snapshot's end iterator
         */
        iterator end() { return _snapshot.end(); }

        /**
         * @brief converts current data to string representation
         * @return string, e.g [4, 5, 6, 7] for a 4x int vector
         */
        std::string to_string() const {
            std::stringstream ss;

            auto is_vector = size() > 1;

            if (is_vector)
                ss << "[ ";

            for (auto entry : data())
                ss << entry << " ";

            if (is_vector)
                ss << "]";

            return ss.str();
        }

        /**
         * @brief prints current value to target stream
         * @param os target stream
         * @param data printable trait
         * @return target stream
         */
        friend std::ostream &operator<<(std::ostream &os, const bval data) {
            os << data.to_string();

            return os;
        }

    private:
        alignas(zval_traits<bval>::alignment) zval_t _value;
        alignas(zval_traits<bval>::alignment) extracted_t _snapshot;
    };


    template<typename base_t>
    struct composable {
        template<typename terminator>
        struct type :
                public base_t,
                public terminator
        {
            FORWARD(type);
        };
    };

    template<typename T>
    constexpr size_t dim() { return T::dim; }

}