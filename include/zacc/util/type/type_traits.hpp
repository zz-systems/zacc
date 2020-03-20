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
#include <zacc/backend/ztype.hpp>

namespace zacc {

    template<typename... Ts> struct make_void { typedef void type;};
    template<typename... Ts> using void_t = typename make_void<Ts...>::type;


    template<typename T, typename HasCallOp = void>
    struct is_functor : std::false_type
    {};

    template<typename T>
    struct is_functor<T, void_t<decltype(T::operator())>> : std::false_type
    {};

    template<typename From, typename To>
    using enable_if_convertible = std::enable_if_t<std::is_convertible<From, To>::value, From>;

    template<typename Base, typename Derived>
    using enable_if_is_base_of = std::enable_if_t<std::is_base_of<Base, Derived>::value, Derived>;

    template<typename One, typename Other>
    using enable_if_not_same = std::enable_if_t<!std::is_same<One, Other>::value, One>;


    template<typename...>
    struct disjunction : std::false_type {};

    template<typename Head>
    struct disjunction<Head> : Head {};

    template<typename Head, typename... Tail>
    struct disjunction< Head, Tail...>
        : std::conditional_t<bool(Head::value), Head, disjunction<Tail...>>
    {};

    template<typename... Ts>
    constexpr bool disjunction_v = disjunction<Ts...>::value;

    template<typename...>
    struct conjunction : std::false_type {};

    template<typename Head>
    struct conjunction<Head> : Head {};

    template<typename Head, typename... Tail>
    struct conjunction< Head, Tail...>
        : std::conditional_t<bool(Head::value), conjunction<Tail...>, Head>
    {};

    template<typename... Ts>
    constexpr bool conjunction_v = disjunction<Ts...>::value;

    template<bool...> struct bool_pack;

    template<bool... bs>
    using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;



    template<bool... bs>
    using all_false = std::is_same<bool_pack<bs..., false>, bool_pack<false, bs...>>;

    // =============================================================================================================

    template<bool Condition, typename T>
    struct when
    {
        static constexpr bool value = Condition;
        using type = T;
    };

    template<typename... Cases>
    struct select;

    template<bool Bs, typename Head, typename... Tail>
    struct select_impl
    {
        using type = typename std::conditional_t<Head::value, Head, select<Tail...>>::type;
    };

    template<typename Head, typename... Tail>
    struct select_impl<true, Head, Tail...>
    {};

    template<typename... Cases>
    struct select : select_impl<all_false<Cases::value...>::value, Cases...>
    {
    };

    template<typename Head>
    struct select<Head> : std::enable_if<Head::value, typename Head::type>
    {
        //using type = typename std::conditional_t<Head::value, Head, void>::type;
    };

//    template<typename Head>
//    struct select<Head>
//    {
//        template<typename T, typename enable = void>
//        struct terminator : when<true, T>
//        {};
//
//        template<typename T>
//        struct terminator<T, std::enable_if_t<T::value || true, T>> : T
//        {};
//
//        using type = typename std::conditional_t<terminator<Head>::value, terminator<Head>, void>::type;
//    };

    template<typename... Cases>
    using select_t = typename select<Cases...>::type;

    namespace
    {
        using select1 = select_t<
                when<true, int>,
                when<false, float>,
                when<false, bool>>;

        static_assert(std::is_same<select1, int>::value, "is_same<select1> != int");

        using select2 = select_t<
                when<false, int>,
                when<true, float>,
                when<false, bool>>;

        static_assert(std::is_same<select2, float>::value, "is_same<select2> != float");

        using select3 = select_t<
                when<false, int>,
                when<false, float>,
                when<true, bool>>;

        static_assert(std::is_same<select3, bool>::value, "is_same<select3> != bool");

        using select4 = select_t<
                when<false, int>,
                when<false, float>,
                when<true, double>>;

        static_assert(std::is_same<select4, double>::value, "is_same<select4> != double");
    }

    // =============================================================================================================

//    template <typename T, typename enable = void>
//    struct is_small_type
//        : std::false_type
//    {};
//
//    template <typename T>
//    struct is_small_type<T, std::enable_if_t<std::is_pointer<T>::value
//                                             || std::is_arithmetic<T>::value
//                                             || std::is_enum<T>::value
//                                             || sizeof(T) < sizeof(void*)>>
//        : std::true_type
//    {};
//
////    template<typename T>
////    using param_t = std::conditional_t<is_small_type<T>::value, T const, T const&>;
//
//    template<typename T>
//    using param_t = std::conditional_t<is_small_type<T>::value, T, const T&>;

    template<typename T>
    using param_t = const std::decay_t<T>&;

    template<typename T, typename U>
    using enable_if_convertible2 = std::enable_if_t<std::is_convertible<T, U>::value, void**>;

    template<typename T, typename U>
    using enable_if_not_same2 = std::enable_if_t<!std::is_same<T, U>::value, void**>;

    template<bool Cond>
    using enable_if_t = std::enable_if_t<Cond, void**>;

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


    /**
     * @see https://stackoverflow.com/a/19532607/1261537
     */
    struct sink { template<typename ...Args> sink(Args const & ... ) {} };

    template<class> struct type_sink { using type = void; };
    template<class T> using type_sink_t = typename type_sink<T>::type;

    template<typename T>
    using resolve_uint_t = select_t<
            when<sizeof(T) == 8, uint64_t>,
            when<sizeof(T) == 4, uint32_t>,
            when<sizeof(T) == 2, uint16_t>,
            when<sizeof(T) == 1, uint8_t>>;

    template<typename T> struct tag
    {
        using type = T;
    };

    template<typename Tag>
    using type_t = typename Tag::type;

    template<template<class...> class>
    struct quote {};

    template<typename T>
    struct unquote {};

    template<template<class...> class T>
    struct unquote<quote<T>>
    {
        template<typename... Ts>
        using type = T<Ts...>;
    };

    template<typename T>
    using unquote_t = typename unquote<T>::type;

    //template<template<class...> class A, template<class...> class B>
    //struct promote<A<promote<B>> {};

    template<typename T, typename... Ts>
    struct apply {};

    template<template<class...> class T, typename... Ts>
    struct apply<quote<T>, Ts...>
        : tag<T<Ts...>>
    {};

    template<typename T, typename... Ts>
    using apply_t = type_t<apply<T, Ts...>>;

    template<typename N, typename n>
    using promote_num = std::integral_constant<N, n {}>;
    using promote_num_t = quote<promote_num>;

    template<typename T, typename... Ts>
    struct bind
    {
        template<typename... Tts>
        using wrap_t = apply_t<T, Ts..., Tts...>;

        using type = quote<wrap_t>;
    };

    template<typename T, typename... Ts>
    using bind_t = type_t<bind<T, Ts...>>;
    using promote_bind = quote<bind_t>;


    template<typename...>
    struct types { using type=types; };
    using promote_types=quote<types>;

    template<typename... Ts>
    using prefix = apply_t< promote_bind, promote_types, Ts... >;
    using promote_prefix = quote<prefix>;
}

namespace zacc
{

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


    template<typename T>
    constexpr std::enable_if_t<is<iterable, T>,T> make_iterable(const T& value)
    {
        return value;
    }

    template<typename T>
    constexpr std::enable_if_t<!is<iterable, T>, std::array<T, 1>> make_iterable(const T& value)
    {
        return std::array<T, 1> {{ value }};
    }


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