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
#include <type_traits>
#include <array>

namespace zacc {
    struct zval_base
    {};

    struct bval_base
    {};

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

    struct zval_tag {};
    struct bval_tag : zval_tag {};
    struct cval_tag : zval_tag {};


    template<typename From, typename To>
    using enable_if_convertible = std::enable_if_t<std::is_convertible<From, To>::value, From>;

    template<typename Base, typename Derived>
    using enable_if_is_base_of = std::enable_if_t<std::is_base_of<Base, Derived>::value, Derived>;

    template<typename One, typename Other>
    using enable_if_not_same = std::enable_if_t<!std::is_same<One, Other>::value, One>;


    template<bool...> struct bool_pack;
    template<bool... bs>
    using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;

    template<bool Condition, typename T>
    struct when
    {
        static constexpr bool value = Condition;
        using type = T;
    };


    template<typename Head, typename... Tail>
    struct select
    {
        using type = typename std::conditional_t<Head::value, Head, select<Tail...>>::type;
    };

    template<typename Head>
    struct select<Head>
    {
        using type = typename std::conditional_t<Head::value, Head, void>::type;
    };


    template<typename Head, typename... Tail>
    using select_t = typename select<Head, Tail...>::type;

    template<typename Base, typename required_t>
    struct requires {
        static_assert(std::is_base_of<required_t, Base>::value, "Required feature not implemented.");

        using type = enable_if_is_base_of<required_t, Base>;
    };

    template<typename Base, typename required_t>
    using requires_t = typename requires<Base, required_t>::type;


    template<typename T>
    struct identity {
        typedef T type;
    };

    template<typename T>
    bool is_any_set(T) {
        return false;
    }

    template<typename T, typename... Args>
    bool is_any_set(T ref_value, T head, Args... tail) {
        return ((ref_value & head) != 0) || is_any_set(ref_value, tail...);
    };

    template<typename T, typename enable = void>
    struct ztraits;

//    template<typename T, typename enable = void>
//    struct zval_is_base_of : std::false_type
//    {};
//
//    template<typename T, typename enable = void>
//    struct bval_is_base_of : std::false_type
//    {};

//    template<typename T>
//    using enable_if_zval_is_base_of_t = std::enable_if_t<zval_is_base_of<T>::value, T>;
//
//    template<typename T>
//    using enable_if_bval_is_base_of_t = std::enable_if_t<bval_is_base_of<T>::value, T>;

    template<typename val_t, typename enable_t = void>
    struct is_zval
            : public std::false_type
    {};

    template<typename val_t>
    struct is_zval<val_t, std::enable_if_t<std::is_same<typename ztraits<val_t>::tag, zval_tag>::value
                                           && std::is_arithmetic<typename ztraits<val_t>::element_t>::value>>
            : public std::true_type
    {};

//    template<typename val_t>
//    struct is_zval<val_t, std::enable_if_t<std::is_same<typename val_t::tag, zval_tag>::value
//                                           && std::is_arithmetic<typename val_t::element_t>::value>>
//            : public std::true_type
//    {};


    template<typename val_t, typename enable_t = void>
    struct is_bval : public std::false_type
    {};

    template<typename val_t>
    struct is_bval<val_t, std::enable_if_t<std::is_same<typename ztraits<val_t>::tag, bval_tag>::value
                                           && std::is_same<typename ztraits<val_t>::element_t, bool>::value>>
            : public std::true_type
    {};

    template<typename val_t>
    struct is_bval<val_t, std::enable_if_t<std::is_same<typename val_t::tag, bval_tag>::value>>
            : public std::true_type
    {};



    template<typename val_t, typename enable_t = void>
    struct is_cval
            : public std::false_type
    {};

    /// @cond
    /// @struct is_cval<val_t, std::enable_if_t<is cval_tag && (zval || is_bval)>
    template<typename val_t>
    struct is_cval<val_t, std::enable_if_t<std::is_same<typename ztraits<val_t>::tag, cval_tag>::value
                                           && (is_zval<typename ztraits<val_t>::element_t>::value || is_bval<typename val_t::element_t>::value)>>
            : public std::true_type
    {};
    /// @endcond

    template<typename val_t>
    struct is_bval<val_t, std::enable_if_t<is_cval<val_t>::value && is_bval<typename ztraits<val_t>::element_t>::value>>
            : public std::true_type
    {};

    template<typename val_t, typename enable_t = void>
    struct is_floating_point
            : public std::false_type
    {};

    template<typename val_t>
    struct is_floating_point<val_t, std::enable_if_t<std::is_floating_point<typename ztraits<val_t>::element_t>::value>>
            : public std::true_type
    {};


    template<typename val_t, typename enable_t = void>
    struct is_float
            : public std::false_type
    {};

    template<typename val_t>
    struct is_float<val_t, std::enable_if_t<std::is_same<typename ztraits<val_t>::element_t, float>::value>>
            : public std::true_type
    {};


    template<typename val_t, typename enable_t = void>
    struct is_double
            : public std::false_type
    {};

    template<typename val_t>
    struct is_double<val_t, std::enable_if_t<std::is_same<typename ztraits<val_t>::element_t, double>::value>>
            : public std::true_type
    {};

    template<typename val_t, typename enable_t = void>
    struct is_integral
            : public std::false_type
    {};

//    template<typename val_t>
//    struct is_integral<val_t, std::enable_if_t<std::is_integral<typename ztraits<val_t>::element_t>::value>>
//            : public std::true_type
//    {};

    template<typename val_t>
    struct is_integral<val_t, std::enable_if_t<std::is_integral<typename val_t::element_t>::value>>
            : public std::true_type
    {};

    template<typename val_t, typename enable_t = void>
    struct is_scalar
            : public std::false_type
    {};

    template<typename val_t>
    struct is_scalar<val_t, std::enable_if_t<!ztraits<val_t>::is_vector>>
            : public std::true_type
    {};

    template<typename val_t, typename enable_t = void>
    struct is_vector
            : public std::false_type
    {};

//    template<typename val_t>
//    struct is_vector<val_t, std::enable_if_t<ztraits<val_t>::is_vector>>
//            : public std::true_type
//    {};

    template<typename val_t>
    struct is_vector<val_t, std::enable_if_t<val_t::is_vector>>
            : public std::true_type
    {};

    template<typename val_t>
    constexpr bool is_vector_v = is_vector<val_t>::value;

    template<typename T>
    using resolve_uint_t = std::conditional_t<
            sizeof(T) == 8,
                uint64_t,
                std::conditional_t<
            sizeof(T) == 4,
                uint32_t,
                std::conditional_t<
            sizeof(T) == 2,
                uint16_t,
                uint8_t>>>;




    /**
     * @see https://stackoverflow.com/a/19532607/1261537
     */
    struct sink { template<typename ...Args> sink(Args const & ... ) {} };

    template<class> struct type_sink { using type = void; };
    template<class T> using type_sink_t = typename type_sink<T>::type;

}

namespace zacc
{


//    template<typename Vector, typename MaskVector, typename Element, typename Tag, size_t Size, size_t Alignment, uint64_t Features = 0xFFFF'FFFF'FFFF'FFFF>
//    struct zval_base
//    {
//        /// vector size (1 - scalar, 4, 8, 16, ...)
//        static constexpr size_t size() noexcept
//        {
//            return Size;
//        }
//
//        /// scalar type? vector type?
//        static constexpr bool is_vector = Size > 1;
//
//        /// capabilities
//        static constexpr uint64_t features = Features;
//
//        /// memory alignment
//        static constexpr size_t alignment = Alignment;
//
//
//        /// vector type, like __m128i for sse 4x integer vector
//        using vector_t = Vector;
//
//        /// scalar type, like int for sse 4x integer vector
//        using element_t = Element;
//
//        /// mask type for boolean operations
//        using mask_vector_t = MaskVector;
//
//        using tag = Tag;
//    };

//    template<typename T>
//    struct ztraits;

//    template<typename T, typename enable_t = void>
//    struct ztraits
//    {
//        /// vector size (1 - scalar, 4, 8, 16, ...)
//        static constexpr size_t size = 1;
//
//        /// capabilities
//        static constexpr uint64_t features = 0;
//
//        /// memory alignment
//        static constexpr size_t alignment = alignof(T);
//
//        /// scalar type? vector type?
//        static constexpr bool is_vector = false;
//
//        /// vector type, like __m128i for sse 4x integer vector
//        using vector_t = void;
//
//        /// scalar type, like int for sse 4x integer vector
//        using element_t = void;
//
//        /// mask type for boolean operations
//        using mask_vector_t = void;
//
//        /// extracted std::array of (dim) scalar values
//        using extracted_t = T;
//
//    };
//
//    template<typename T>
//    struct ztraits<T, std::enable_if_t<is_cval<T>::value || is_zval<T>::value || is_bval<T>::value>>
//    {
//        /// vector size (1 - scalar, 4, 8, 16, ...)
//        static constexpr size_t size = T::size();
//
//        /// capabilities
//        static constexpr uint64_t features = T::features;
//
//        /// memory alignment
//        static constexpr size_t alignment = T::alignment;
//
//        /// scalar type? vector type?
//        static constexpr bool is_vector = size > 1;
//
//
//
//        /// vector type, like __m128i for sse 4x integer vector
//        using vector_t = typename T::vector_t;
//
//        /// scalar type, like int for sse 4x integer vector
//        using element_t = typename T::element_t;
//
//        /// mask type for boolean operations
//        using mask_vector_t = typename T::mask_vector_t;
//
//        /// extracted std::array of (dim) scalar values
//        using extracted_t = std::array<element_t, size>; //aligned_array<scalar_t, dim, alignment>;
//
//
//
//        using zval_t = typename T::zval_t;//zval_base<vector_t, mask_vector_t , element_t , zval_tag, size, alignment, features>;
//        using bval_t = typename T::bval_t;//zval_base<vector_t, mask_vector_t , bool , bval_tag, size, alignment, features>;
//
//        //using tag = typename zval_t::tag;
//    };

//    template<typename T, typename enable = void>
//    struct is_iterable : std::false_type {};
//
//    template<typename T>
//    struct is_iterable <T, type_sink_t<decltype((std::declval<std::remove_pointer<T>>().begin()) - (std::declval<std::remove_pointer<T>>().end()))>>
//            : std::true_type
//    {};

    

    template<typename Rule>
    struct _is : Rule
    {
        using Rule::test;

        template<class>
        constexpr static auto test(...) -> std::false_type;
    };

    template<typename Rule, typename T>
    struct __is : decltype(_is<Rule>:: template test<T>(0)) {};


    template<typename Rule, typename... Ts>
    struct __all;

    template<typename Rule, typename T, typename... Ts>
    struct __all<Rule, T, Ts...> : std::integral_constant<bool, __is<Rule, T>::value && __all<Rule, Ts...>::value>
    {} ;

    template<typename Rule, typename T>
    struct __all<Rule, T> : std::integral_constant<bool, __is<Rule, T>::value>
    {};

    template<typename Rule, typename... Ts>
    struct __any;

    template<typename Rule, typename T, typename... Ts>
    struct __any<Rule, T, Ts...> : std::integral_constant<bool, __is<Rule, T>::value || __all<Rule, Ts...>::value>
    {};

    template<typename Rule, typename T>
    struct __any<Rule, T> : std::integral_constant<bool, __is<Rule, T>::value>
    {};


    template<typename Rule, typename T>
    constexpr bool is = __is<Rule, T>::value;

    template<typename Rule, typename... Ts>
    constexpr bool all = __all<Rule, Ts...>::value;

    template<typename Rule, typename... Ts>
    constexpr bool any = __any<Rule, Ts...>::value;




    struct measurable
    {
        template<class U>
        constexpr static auto test(U* p) -> decltype(p->size(), std::true_type());
    };

    struct iterable
    {
        template<class U>
        constexpr static auto test(U* p) -> decltype(p->begin(), p->end(), std::true_type());
    };

    struct resizable
    {
        template<class U>
        constexpr static auto test(U* p) -> decltype(p->resize(1), p->shrink_to_fit(), std::true_type());
    };

    struct swappable
    {
        template<class U>
        constexpr static auto test(U* p) -> decltype(p->swap(*p), std::true_type());
    };


    /**
    * @see https://stackoverflow.com/a/44522730/1261537
    */

    template<typename T, typename enable = void>
    struct element_type
    {
        using type = std::remove_cv_t<std::remove_reference_t<decltype(std::declval<T>().data())>>;
    };

    template<typename T>
    struct element_type<T, std::enable_if_t<is_cval<T>::value || is_zval<T>::value || is_bval<T>::value>>
    {
        using type = std::remove_cv_t<std::remove_reference_t<typename ztraits<T>::element_t>>;
    };


    template<typename T>
    struct element_type<T, std::enable_if_t<is<iterable, T> && !is_cval<T>::value && !is_zval<T>::value && !is_bval<T>::value>>
    {
        using type =  std::remove_reference_t<decltype(*std::begin(std::declval<T&>()))>;
    };

    template<typename T>
    using element_type_t = typename element_type<T>::type;

    /// @brief trait system for function pointer-like objects
    /// @see https://functionalcpp.wordpress.com/2013/08/05/function-traits/
    template<class F>
    struct function_traits;

    template<class R, class... Args>
    struct function_traits<R(Args...)>
    {
        using return_type = R;

        static constexpr std::size_t arity = sizeof...(Args);

        template <std::size_t N>
        struct argument
        {
            static_assert(N < arity, "error: invalid parameter index.");
            using type = typename std::tuple_element<N,std::tuple<Args...>>::type;
        };
    };

    // function pointer
    template<class R, class... Args>
    struct function_traits<R(*)(Args...)> : public function_traits<R(Args...)>
    {};

    // member function pointer
    template<class C, class R, class... Args>
    struct function_traits<R(C::*)(Args...)> : public function_traits<R(C&,Args...)>
    {};

    // const member function pointer
    template<class C, class R, class... Args>
    struct function_traits<R(C::*)(Args...) const> : public function_traits<R(C&,Args...)>
    {};

    // member object pointer
    template<class C, class R>
    struct function_traits<R(C::*)> : public function_traits<R(C&)>
    {};

    // functor
    template<class F>
    struct function_traits
    {
    private:
        using call_type = function_traits<decltype(&F::type::operator())>;
    public:
        using return_type = typename call_type::return_type;

        static constexpr std::size_t arity = call_type::arity - 1;

        template <std::size_t N>
        struct argument
        {
            static_assert(N < arity, "error: invalid parameter index.");
            using type = typename call_type::template argument<N+1>::type;
        };
    };

    template<class F>
    struct function_traits<F&> : public function_traits<F>
    {};

    template<class F>
    struct function_traits<F&&> : public function_traits<F>
    {};
}