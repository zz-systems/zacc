//
// Created by Sergej Zuyev on 12/13/2016.
//

#ifndef ZACC_TYPE_TRAITS_HPP
#define ZACC_TYPE_TRAITS_HPP

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
        return (ref_value & head != 0) || is_any_set(ref_value, tail...);
    };
}

#endif //ZACC_TYPE_TRAITS_HPP
