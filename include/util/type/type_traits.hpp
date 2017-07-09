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
#include <type_traits>

namespace zacc {
//    template<template<class> class T, class U>
//    struct is_derived_from
//    {
//    private:
//        template<class V>
//        static decltype(static_cast<const T<V>&>(std::declval<U>()), std::true_type{}) test(const T<V>&);
//        static std::false_type test(...);
//    public:
//        static constexpr bool value = decltype(is_derived_from::test(std::declval<U>()))::value;
//    };


    template<typename from_t, typename to_t>
    using enable_if_convertible = std::enable_if_t<std::is_convertible<from_t, to_t>::value, from_t>;

    template<typename base_t, typename derived_t>
    using enable_if_is_base_of = std::enable_if_t<std::is_base_of<base_t, derived_t>::value, derived_t>;

    template<typename one_t, typename other_t>
    using enable_if_not_same = std::enable_if_t<!std::is_same<one_t, other_t>::value, one_t>;


    template<bool...> struct bool_pack;
    template<bool... bs>
    using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;

    template<typename base_t, typename required_t>
    struct requires {
        static_assert(std::is_base_of<required_t, base_t>::value, "Required feature not implemented.");

        using type = enable_if_is_base_of<required_t, base_t>;
    };

    template<typename base_t, typename required_t>
    using requires_t = typename requires<base_t, required_t>::type;


    template<typename T>
    struct identity {
        typedef T type;
    };

    template<typename T>
    bool is_any_set(T ref_value) {
        return false;
    }

    template<typename T, typename... Args>
    bool is_any_set(T ref_value, T head, Args... tail) {
        return ((ref_value & head) != 0) || is_any_set(ref_value, tail...);
    };

    template<typename val_t, typename enable_t = void>
    struct is_zval
            : public std::false_type
    {};

    template<typename val_t>
    struct is_zval<val_t, std::enable_if_t<std::is_arithmetic<typename val_t::scalar_t>::value>>
            : public std::true_type
    {};


    template<typename val_t, typename enable_t = void>
    struct is_bval : public std::false_type
    {};

    template<typename val_t>
    struct is_bval<val_t, std::enable_if_t<std::is_same<typename val_t::scalar_t, bool>::value>>
            : public std::true_type
    {};

    template<typename val_t, typename enable_t = void>
    struct is_floating_point
            : public std::false_type
    {};

    template<typename val_t>
    struct is_floating_point<val_t, std::enable_if_t<std::is_floating_point<typename val_t::scalar_t>::value>>
            : public std::true_type
    {};


    template<typename val_t, typename enable_t = void>
    struct is_float
            : public std::false_type
    {};

    template<typename val_t>
    struct is_float<val_t, std::enable_if_t<std::is_same<typename val_t::scalar_t, float>::value>>
            : public std::true_type
    {};


    template<typename val_t, typename enable_t = void>
    struct is_double
            : public std::false_type
    {};

    template<typename val_t>
    struct is_double<val_t, std::enable_if_t<std::is_same<typename val_t::scalar_t, double>::value>>
            : public std::true_type
    {};

    template<typename val_t, typename enable_t = void>
    struct is_integral
            : public std::false_type
    {};

    template<typename val_t>
    struct is_integral<val_t, std::enable_if_t<std::is_integral<typename val_t::scalar_t>::value>>
            : public std::true_type
    {};
}