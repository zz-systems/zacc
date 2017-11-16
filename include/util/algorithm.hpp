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

#include <algorithm>
#include <string>
#include <numeric>
#include <type_traits>
#include <iterator>
#include <utility>
#include <iostream>
#include "type/type_traits.hpp"

namespace zacc {

    /**
     * @brief Conditionally transforms one collection to another
     * @tparam InputIt
     * @tparam OutputIt
     * @tparam UnaryOperation
     * @tparam UnaryPredicate
     * @param first
     * @param last
     * @param d_first
     * @param unary_op
     * @param pred
     * @return
     */
    template< class InputIt, class OutputIt, class UnaryOperation, class UnaryPredicate>
    OutputIt transform_if(InputIt first, InputIt last,
                        OutputIt d_first, UnaryOperation unary_op, UnaryPredicate pred)
    {
        for (; first != last; ++first)
            if (pred(*first))
                *d_first++ = unary_op(*first);

        return d_first;
    };

    /**
     * @brief Concatenates all the elements of a collection
     * using the specified separator between each element.
     * The collection value type must provide a str() method.
     * @tparam InputIt collection iterator type
     * @param first Begin
     * @param last End
     * @param separator The string to use as separator
     * @return A string that consists of the elements in provided collection delimited by the separator string
     */
    template< class InputIt >
    std::string join(InputIt first, InputIt last, const std::string& separator) {
        if(first == last)
            return "";

        return std::accumulate(first + 1, last, first->str(),
                        [separator](std::string &acc, auto &part) {
                            return acc + separator + part.str();
            });
    }

    /**
     * @brief Concatenates all the elements of a collection
     * using the specified separator between each element.
     * The collection value type must provide a str() method.
     * @tparam Container collection
     * @param collection collection
     * @param separator The string to use as separator
     * @return A string that consists of the elements in provided collection delimited by the separator string
     */
    template< class InputContainer, typename = std::enable_if_t<is<iterable, InputContainer>>>
    std::string join(const InputContainer &container, const std::string& separator) {
        return join(std::begin(container),
                    std::end(container),
                    separator);
    }


    /**
     * @brief
     * @tparam ztype
     * @tparam ForwardIt
     * @tparam UnaryOperation
     * @param first
     * @param last
     * @param unary_op
     */
    template<class ztype, class ForwardIt, class Generator>
    void generate(ForwardIt first, ForwardIt last, Generator g)
    {
        auto dim        = ztype::size();
        size_t real_size  = std::distance(first, last);
        auto remainder  = real_size % dim;
        auto fake_size  = real_size + remainder;

        for (size_t i = 0; i < fake_size; i += dim)
        {
            auto result = make_iterable(g(i));

            auto to_fetch = i < real_size - 1 ? dim : remainder;
            std::copy(std::begin(result), std::begin(result) + to_fetch, first + i);
        }
    };

    /**
     * @brief
     * @tparam Container
     * @tparam UnaryOperation
     * @param container
     * @param unary_op
     */
    template<class InputContainer, class Generator, typename = std::enable_if_t<is<iterable, InputContainer>>>
    void generate(const InputContainer &container, Generator g)
    {
        generate<InputContainer::value_type>(std::begin(container),
                                        std::end(container),
                                        g);
    };

    /**
     * @brief
     * @tparam Container
     * @tparam UnaryOperation
     * @param container
     * @param unary_op
     */
    template<class InputContainer, class OutputContainer = InputContainer, class UnaryOperation, typename = std::enable_if_t<all<iterable, InputContainer, OutputContainer>>>
    auto transform(const InputContainer& input, UnaryOperation func)
    {
        alignas(zval_traits<InputContainer>::alignment) OutputContainer output;

        std::transform(std::begin(input), std::end(input), std::begin(output), func);

        return output;
    };

    namespace
    {
        template<typename T, size_t... seq>
        constexpr T make_index_impl(T index, std::index_sequence<seq...>)
        {
            return index + T{ seq... };
        }
    }

    template<typename T>
    constexpr std::enable_if_t<zval_traits<T>::is_vector, T> make_index(T index)
    {
        return make_index_impl(index, std::make_integer_sequence<size_t, zval_traits<T>::size>());
    }

    template<typename T>
    constexpr std::enable_if_t<!zval_traits<T>::is_vector, T> make_index(T index)
    {
        return index;
    }



    template<typename Tuple>
    using tuple_size = std::tuple_size<std::remove_reference_t<Tuple>>;

    template<typename Tuple>
    using make_tuple_index = std::make_integer_sequence<size_t, tuple_size<Tuple>::value>;


    namespace
    {
        template<class InputTuple, class UnaryOperation, size_t... index>
        void for_each_impl(InputTuple&& input, UnaryOperation&& func, std::index_sequence<index...>)
        {
            sink { true, (func(std::get<index>(std::forward<InputTuple>(input))),
                    void(), true)... };
        };

        template<class InputTuple1, class InputTuple2, class BinaryOperation, size_t... index>
        void for_each_impl(InputTuple1&& input1, InputTuple2&& input2, BinaryOperation&& func, std::index_sequence<index...>)
        {
            sink { true, (func(std::get<index>(std::forward<InputTuple1>(input1)),
                               std::get<index>(std::forward<InputTuple2>(input2))),
                    void(), true)... };
        };

//        template<class InputTuple, class OutputTuple, class UnaryOperation, size_t... index>
//        auto transform_impl(InputTuple&& input, OutputTuple&& output, UnaryOperation&& func, std::index_sequence<index...>)
//            -> decltype(output)
//        {
//            auto dummy = { (std::get<index>(output) = func(std::get<index>(std::forward<InputTuple>(input))))... };
//
//            return output;
//        };
//
//        template<class InputTuple1, class InputTuple2, class OutputTuple, class BinaryOperation, size_t... index>
//        auto transform_impl(InputTuple1&& input1, InputTuple2&& input2, OutputTuple&& output, BinaryOperation&& func, std::index_sequence<index...>)
//            -> decltype(output)
//        {
//            auto dummy = { (std::get<index>(output) = func(std::get<index>(std::forward<InputTuple1>(input1)),
//                                                           std::get<index>(std::forward<InputTuple2>(input2))))... };
//
//            return output;
//        };

        template<class InputTuple, class UnaryOperation, size_t... index>
        auto transform_impl(InputTuple&& input, UnaryOperation&& func, std::index_sequence<index...>)
        {
            return std::make_tuple( func(std::get<index>(std::forward<InputTuple>(input)))... );
        };

        template<class InputTuple1, class InputTuple2, class BinaryOperation, size_t... index>
        auto transform_impl(InputTuple1&& input1, InputTuple2&& input2, BinaryOperation&& func, std::index_sequence<index...>)
        {
            return std::make_tuple( func(std::get<index>(std::forward<InputTuple1>(input1)),
                                         std::get<index>(std::forward<InputTuple2>(input2)))... );
        };

        template<class InputTuple, class Acc, class BinaryOperation, size_t... index>
        auto accumulate_impl(InputTuple&& input, Acc accumulator, BinaryOperation&& func, std::index_sequence<index...>)
        {
            sink { true, ((accumulator = func(accumulator, std::get<index>(std::forward<InputTuple>(input)))),
                    void(), true)... };

            return accumulator;
        };

        template<class InputTuple1, class InputTuple2, class Acc, class TernaryOperation, size_t... index>
        auto accumulate_impl(InputTuple1&& input1, InputTuple2&& input2, Acc accumulator, TernaryOperation&& func, std::index_sequence<index...>)
        {
            sink { true, ((accumulator = func(accumulator,
                                              std::get<index>(std::forward<InputTuple1>(input1)),
                                              std::get<index>(std::forward<InputTuple2>(input2)))),
                    void(), true)... };

            return accumulator;
        };
    }



    template<class InputTuple, class UnaryOperation, typename = std::enable_if_t<tuple_size<InputTuple>::value != 0>>
    void for_each(InputTuple&& input, UnaryOperation&& func)
    {
        for_each_impl(std::forward<InputTuple>(input), std::forward<UnaryOperation>(func),
                      make_tuple_index<InputTuple>());
    };

    template<class InputTuple1, class InputTuple2, class BinaryOperation, typename = std::enable_if_t<tuple_size<InputTuple1>::value != 0 && tuple_size<InputTuple2>::value != 0>>
    void for_each(InputTuple1&& input1, InputTuple2&& input2, BinaryOperation&& func)
    {
        for_each_impl(std::forward<InputTuple1>(input1), std::forward<InputTuple2>(input2),
                      std::forward<BinaryOperation>(func),  make_tuple_index<InputTuple1>());
    };

//    template<class InputTuple, class OutputTuple, class UnaryOperation>
//    auto transform(InputTuple&& input, OutputTuple&& output, UnaryOperation&& func)
//    {
//        return transform_impl(std::forward<InputTuple>(input), std::forward<OutputTuple>(output),
//                              std::forward<UnaryOperation>(func), make_tuple_index<InputTuple>());
//    };
//
//    template<class InputTuple1, class InputTuple2, class OutputTuple, class BinaryOperation>
//    auto transform(InputTuple1&& input1, InputTuple2&& input2, OutputTuple&& output, BinaryOperation&& func)
//    {
//        return transform_impl(std::forward<InputTuple1>(input1), std::forward<InputTuple2>(input2),
//                              std::forward<OutputTuple>(output), std::forward<BinaryOperation>(func),
//                              make_tuple_index<InputTuple1>());
//    };

    template<class InputTuple, class UnaryOperation, typename = std::enable_if_t<tuple_size<InputTuple>::value != 0>>
    auto transform(InputTuple&& input, UnaryOperation&& func)
    {
        return transform_impl(std::forward<InputTuple>(input), std::forward<UnaryOperation>(func),
                              make_tuple_index<InputTuple>());
    };

    template<class InputTuple1, class InputTuple2, class BinaryOperation, typename = std::enable_if_t<tuple_size<InputTuple1>::value != 0 && tuple_size<InputTuple2>::value != 0>>
    auto transform(InputTuple1&& input1, InputTuple2&& input2, BinaryOperation&& func)
    {
        return transform_impl(std::forward<InputTuple1>(input1), std::forward<InputTuple2>(input2),
                              std::forward<BinaryOperation>(func), make_tuple_index<InputTuple1>());
    };

    template<class InputTuple, class Acc, class BinaryOperation, typename = std::enable_if_t<tuple_size<InputTuple>::value != 0>>
    Acc accumulate(InputTuple&& input, Acc accumulator, BinaryOperation&& func)
    {
        return accumulate_impl(std::forward<InputTuple>(input), std::forward<Acc>(accumulator),
                               std::forward<BinaryOperation>(func), make_tuple_index<InputTuple>());
    };

    template<class InputTuple1, class InputTuple2, class Acc, class TernaryOperation, typename = std::enable_if_t<tuple_size<InputTuple1>::value != 0 && tuple_size<InputTuple2>::value != 0>>
    Acc accumulate(InputTuple1&& input1, InputTuple2&& input2, Acc accumulator, TernaryOperation&& func)
    {
        return accumulate_impl(std::forward<InputTuple1>(input1), std::forward<InputTuple2>(input2),
                               std::forward<Acc>(accumulator), std::forward<TernaryOperation>(func),
                               make_tuple_index<InputTuple1>());
    };


    template<typename... Iterator>
    using tuple_iterator = std::iterator<std::random_access_iterator_tag,
            std::tuple<typename std::iterator_traits<Iterator>::value_type...>,
            std::common_type_t<typename std::iterator_traits<Iterator>::difference_type...>,
            std::tuple<typename std::iterator_traits<Iterator>::pointer...>,
            std::tuple<typename std::iterator_traits<Iterator>::reference...>>;

    template<class... Iterator>
    class zip_iterator :
            public tuple_iterator<Iterator...>
    {
        using base_t = tuple_iterator<Iterator...>;
        using trait_t = typename std::iterator_traits<zip_iterator>;

        using value_type        = typename trait_t::value_type;
        using difference_type   = typename trait_t::difference_type;
        using pointer           = typename trait_t::pointer;
        using reference         = typename trait_t::reference;

        static const difference_type diff_max = std::numeric_limits<difference_type>::max();
        static const difference_type diff_min = std::numeric_limits<difference_type>::min();

        std::tuple<Iterator...> _iterators;

    public:

        constexpr zip_iterator(Iterator&& ...arg)
                : _iterators(std::forward<Iterator>(arg)...)
        {}

        constexpr zip_iterator(std::tuple<Iterator...>&& tuple) noexcept
                : _iterators(std::move(tuple))
        {}

        constexpr zip_iterator(const zip_iterator& other)
                : _iterators(other._iterators)
        {}

        constexpr zip_iterator(zip_iterator&& other) noexcept
                : _iterators(std::move(other._iterators))
        {}


        constexpr zip_iterator& operator=(const zip_iterator& other)
        {
            _iterators = other._iterators;

            return *this;
        }

        constexpr zip_iterator& operator=(zip_iterator&& other) noexcept
        {
            _iterators = std::move(other._iterators);

            return *this;
        }

        constexpr zip_iterator& operator++()
        {
            for_each(_iterators, [&](auto &iterator)
            {
                ++iterator;
            });

            return *this;
        }

        constexpr zip_iterator operator++(int)
        {
            auto result = *this;

            ++(*this);

            return result;
        }

        constexpr bool operator==(const zip_iterator& other)
        {
            return (*this - other) == 0;
        }

        constexpr bool operator!=  (const zip_iterator& other)
        {
            return (*this - other) != 0;
        }

        constexpr reference operator*()
        {
            return transform(_iterators, [](auto& iterator)
            {
                return std::ref(*iterator);
            });
        }

        constexpr const reference operator*() const
        {
            return transform(_iterators, [](auto& iterator)
            {
                return std::ref(*iterator);
            });
        }

        constexpr pointer operator->() const
        {
            return transform(_iterators, [](auto& iterator)
            {
                return std::addressof(*iterator);
            });
        }

        constexpr zip_iterator& operator-- ()
        {
            for_each(_iterators, [](auto& iterator)
            {
                --iterator;
            });

            return *this;
        }

        constexpr zip_iterator operator-- (int)
        {
            auto result = *this;

            --(*this);

            return result;
        }

        constexpr zip_iterator& operator+=(difference_type offset)
        {
            for_each(_iterators, [offset](auto& iterator)
            {
                iterator += offset;
            });

            return *this;
        }

        constexpr zip_iterator& operator-=(difference_type offset)
        {
            return operator+=(-offset);
        }

        constexpr difference_type operator-(const zip_iterator& other)
        {
            return zacc::accumulate(_iterators, other._iterators, diff_max, [](auto acc, auto iterator1, auto iterator2)
            {
                auto diff = iterator1 - iterator2;
                return diff < acc
                       ? diff
                       : acc;
            });
        }

        constexpr zip_iterator operator+(difference_type offset) const
        {
            auto result = *this;
            result += offset;
            return result;
        }

        constexpr zip_iterator operator-(difference_type offset) const
        {
            auto result = *this;
            result -= offset;
            return result;
        }

        constexpr bool operator<(const zip_iterator& other)
        {
            return (*this - other) < 0;
        }

        constexpr bool operator>  (const zip_iterator& other)
        {
            return (*this - other) > 0;
        }

        constexpr bool operator<= (const zip_iterator& other)
        {
            return (*this - other) <= 0;
        }

        constexpr bool operator>= (const zip_iterator& other)
        {
            return (*this - other) >= 0;
        }
    };

    template<typename... Args>
    constexpr auto make_zip_iter(Args&&... arg)
    {
        return zip_iterator<Args...>(std::forward<Args>(arg)...);
    }

    template <typename Container>
    struct resolve_iterator
    {
        using type = typename std::conditional<
                std::is_const<Container>::value || std::is_rvalue_reference<Container>::value,
                typename std::remove_reference<Container>::type::const_iterator,
                typename std::remove_reference<Container>::type::iterator
        >::type;
    };

    template<typename T>
    struct resolve_reference {
        using type = typename std::conditional<
                std::is_rvalue_reference<T>::value,
                std::remove_reference_t<T>,
                std::add_lvalue_reference_t<T>
        >::type;
    };

    template<typename T>
    using resolve_reference_t = typename resolve_reference<T>::type;

    template<typename... Container>
    class zip_container
    {
        using containers_t = std::tuple<resolve_reference_t<Container>...>;
        using indices_t = make_tuple_index<containers_t>;


        containers_t _containers;

        template<size_t... index>
        constexpr auto begins(std::index_sequence<index...>) const { return make_zip_iter(std::begin(std::get<index>(_containers))...);}

        template<size_t... index>
        constexpr auto ends(std::index_sequence<index...>) const { return make_zip_iter(std::end(std::get<index>(_containers))...);}

               //constexpr auto begins(std::index_sequence<index...>)
    public:
        using iterator          = zip_iterator<typename std::remove_reference_t<Container>::iterator...>;
        using const_iterator    = const zip_iterator<typename std::remove_reference_t<Container>::const_iterator...>;

        //template<template<class...> class Func>
        //using _iterator = zip_iterator<decltype(Func(std::declval<resolve_reference_t<Container>>()))...>;


        //using begin_iter_t = zip_iterator<decltype(std::begin(std::remove_reference_t<Container>()))...>;
        //using end_iter_t = zip_iterator<decltype(std::end(std::remove_reference_t<Container>()))...>;

        //using begin_iter_t = zip_iterator<decltype(begins(indices_t()))...>;
        //using end_iter_t = zip_iterator<decltype(std::end(std::remove_reference_t<Container>()))...>;


        //template<size_t... index>
        //using begin_iter_t = zip_iterator<decltype(std::begin(std::get<index>(_containers)))...>;
        //using end_iter_t = zip_iterator<decltype(std::end(std::remove_reference_t<Container>()))...>;

        //using _begin_iter_t = begin_iter_t<indices>

        //template<typename Func>
        //using iter_t = zip_iterator<decltype(Func(std::remove_reference_t<Container>()))...>;

        constexpr zip_container(Container&& ...arg)
                : _containers(std::forward<Container>(arg)...)
        {}

        constexpr zip_container(std::tuple<Container...>&& tuple) noexcept
                : _containers(std::move(tuple))
        {}

        constexpr zip_container(const zip_container& other)
                : _containers(other._containers)
        {}

        constexpr zip_container(zip_container&& other) noexcept
                : _containers(std::move(other._containers))
        {}

        constexpr zip_container& operator=(const zip_container& other)
        {
            _containers = other._containers;

            return *this;
        }

        constexpr zip_container& operator=(zip_container&& other) noexcept
        {
            _containers = std::move(other._containers);

            return *this;
        }

        constexpr auto begin() const
        {
            return begins(indices_t());
        }

        constexpr auto end() const
        {
            return ends(indices_t());
        }

        constexpr const_iterator cbegin() const
        {
            return begin();
        }

        constexpr const_iterator cend() const
        {
            return end();
        }

        constexpr auto begin() //-> decltype(begins(indices_t()))
        {
            return begins(indices_t());
        }

        constexpr auto end() //-> decltype(ends(indices_t()))
        {
            return ends(indices_t());
        }

        constexpr size_t size() const
        {
            return zacc::accumulate(_containers, std::numeric_limits<size_t>::max(), [](auto acc, auto container)
            {
                auto size = container.size();
                return size < acc
                       ? size
                       : acc;
            });
        }

    private:
        //containers_t _containers;
    };

    template<class... Containers>
    auto zip(Containers&&... arg)
    {
        return zip_container<Containers&&...>(std::forward<Containers>(arg)...);
    }
}