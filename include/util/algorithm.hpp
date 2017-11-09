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
    template< class Container >
    std::string join(const Container &container, const std::string& separator) {
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
        auto dim        = ztype::dim;
        auto real_size  = std::distance(first, last);
        auto remainder  = real_size % dim;
        auto fake_size  = real_size + remainder;

        for (auto i = 0; i < fake_size; i += dim)
        {
            auto result = g(i);

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
    template<class Container, class Generator>
    void generate(const Container &container, Generator g)
    {
        generate<Container::value_type>(std::begin(container),
                                        std::end(container),
                                        g);
    };

    template<typename Tuple>
    using tuple_size = std::tuple_size<std::remove_reference_t<Tuple>>;

    template<typename Tuple>
    using make_tuple_index = std::make_integer_sequence<size_t, tuple_size<Tuple>::value>;

    namespace
    {
        template<class InputTuple, class UnaryOperation, size_t... index>
        void for_each_impl(InputTuple&& input, UnaryOperation&& func, std::index_sequence<index...>)
        {
            auto dummy = { true, (func(std::get<index>(std::forward<InputTuple>(input))),
                    void(), true)... };
        };

        template<class InputTuple1, class InputTuple2, class BinaryOperation, size_t... index>
        void for_each_impl(InputTuple1&& input1, InputTuple2&& input2, BinaryOperation&& func, std::index_sequence<index...>)
        {
            auto dummy = { true, (func(std::get<index>(std::forward<InputTuple1>(input1)),
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
            auto dummy = { true, ((accumulator = func(accumulator, std::get<index>(std::forward<InputTuple>(input)))),
                    void(), true)... };

            return accumulator;
        };

        template<class InputTuple1, class InputTuple2, class Acc, class TernaryOperation, size_t... index>
        auto accumulate_impl(InputTuple1&& input1, InputTuple2&& input2, Acc accumulator, TernaryOperation&& func, std::index_sequence<index...>)
        {
            auto dummy = { true, ((accumulator = func(accumulator,
                                                      std::get<index>(std::forward<InputTuple1>(input1)),
                                                      std::get<index>(std::forward<InputTuple2>(input2)))),
                    void(), true)... };

            return accumulator;
        };
    }



    template<class InputTuple, class UnaryOperation>
    void for_each(InputTuple&& input, UnaryOperation&& func)
    {
        for_each_impl(std::forward<InputTuple>(input), std::forward<UnaryOperation>(func),
                      make_tuple_index<InputTuple>());
    };

    template<class InputTuple1, class InputTuple2, class BinaryOperation>
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

    template<class InputTuple, class UnaryOperation>
    auto transform(InputTuple&& input, UnaryOperation&& func)
    {
        return transform_impl(std::forward<InputTuple>(input), std::forward<UnaryOperation>(func),
                              make_tuple_index<InputTuple>());
    };

    template<class InputTuple1, class InputTuple2, class BinaryOperation>
    auto transform(InputTuple1&& input1, InputTuple2&& input2, BinaryOperation&& func)
    {
        return transform_impl(std::forward<InputTuple1>(input1), std::forward<InputTuple2>(input2),
                              std::forward<BinaryOperation>(func), make_tuple_index<InputTuple1>());
    };

    template<class InputTuple, class Acc, class BinaryOperation>
    auto accumulate(InputTuple&& input, Acc accumulator, BinaryOperation&& func)
    {
        return accumulate_impl(std::forward<InputTuple>(input), std::forward<Acc>(accumulator),
                              std::forward<BinaryOperation>(func), make_tuple_index<InputTuple>());
    };

    template<class InputTuple1, class InputTuple2, class Acc, class TernaryOperation>
    auto accumulate(InputTuple1&& input1, InputTuple2&& input2, Acc accumulator, TernaryOperation&& func)
    {
        return accumulate_impl(std::forward<InputTuple1>(input1), std::forward<InputTuple2>(input2),
                          std::forward<Acc>(accumulator), std::forward<TernaryOperation>(func),
                          make_tuple_index<InputTuple1>());
    };

    template <typename Container>
    struct resolve_iterator
    {
        using type = typename std::conditional<
                std::is_const<Container>::value,
                typename std::remove_reference<Container>::type::const_iterator,
                typename std::remove_reference<Container>::type::iterator
        >::type;
    };

    template<typename... Iterator>
    using tuple_iterator = std::iterator<std::random_access_iterator_tag,
            std::tuple<typename std::iterator_traits<Iterator>::value_type...>,
            ptrdiff_t,
            std::tuple<typename std::iterator_traits<Iterator>::pointer...>,
            std::tuple<typename std::iterator_traits<Iterator>::reference...>>;

    template<class... Iterator>
    class zip_iterator : public tuple_iterator<Iterator...>
    {
        using base_t = tuple_iterator<Iterator...>;
        using trait_t = typename std::iterator_traits<zip_iterator>;

        using value_type        = typename trait_t::value_type;
        using difference_type   = typename trait_t::difference_type;
        using pointer           = typename trait_t::pointer;
        using reference         = typename trait_t::reference;

        std::tuple<Iterator...> _iterators;
    public:
        constexpr zip_iterator(Iterator &&... args)
                : _iterators(std::forward_as_tuple(args...))
        {}

        constexpr zip_iterator(const std::tuple<Iterator...>& tuple)
                : _iterators(tuple)
        {}

        constexpr zip_iterator(const zip_iterator& other)
                : _iterators(other._iterators)
        {}

        constexpr zip_iterator& operator=(const zip_iterator& other)
        {
            _iterators = other._iterators;

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
            auto temp = *this;

            ++(*this);

            return temp;
        }

        constexpr friend bool operator==  (const zip_iterator& one, const zip_iterator& other)
        {
            return zacc::accumulate(one._iterators, other._iterators, true, [](auto acc, auto iterator1, auto iterator2)
            {
                return acc && iterator1 == iterator2;
            });
        }

        constexpr friend bool operator!=  (const zip_iterator& one, const zip_iterator& other)
        {
            return !(one == other);
        }

        constexpr reference operator*() const
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
            auto temp = *this;

            --(*this);

            return temp;
        }

        constexpr zip_iterator& operator+= (const difference_type& offset)
        {
            for_each(_iterators, [&offset](auto& iterator)
            {
                iterator += offset;
            });

            return *this;
        }

        constexpr zip_iterator& operator-= (const difference_type& offset)
        {
            for_each(_iterators, [&offset](auto& iterator)
            {
                iterator -= offset;
            });

            return *this;
        }

        constexpr zip_iterator operator+ (const difference_type& offset) const
        {
            return transform(_iterators, [&offset](auto &iterator)
            {
                return iterator + offset;
            });
        }

        constexpr zip_iterator operator- (const difference_type& offset) const
        {
            return transform(_iterators, [&offset](auto &iterator)
            {
                return iterator - offset;
            });
        }

        friend bool operator<  (const zip_iterator& one, const zip_iterator& other)
        {
            return accumulate(one._iterators, other._iterators, true, [](auto acc, auto iterator1, auto iterator2)
            {
                return acc && iterator1 < iterator2;
            });
        }

        friend bool operator>  (const zip_iterator& one, const zip_iterator& other)
        {
            return accumulate(one._iterators, other._iterators, true, [](auto acc, auto iterator1, auto iterator2)
            {
                return acc && iterator1 > iterator2;
            });
        }

        friend bool operator<= (const zip_iterator& one, const zip_iterator& other)
        {
            return !(one > other);
        }

        friend bool operator>= (const zip_iterator& one, const zip_iterator& other)
        {
            return !(one < other);
        }
    };


    template<typename... Iterator>
    class zip_container
    {
        using iterators_t = std::tuple<Iterator...>;
    public:
        constexpr zip_container(iterators_t&& begin, iterators_t&& end) :
                _begin(std::forward<iterators_t>(begin)),
                _end(std::forward<iterators_t>(end))
        {}

        constexpr zip_iterator<Iterator...> begin()
        {
            return zip_iterator<Iterator...>(_begin);
        }

        constexpr zip_iterator<Iterator...> end()
        {
            return zip_iterator<Iterator...>(_end);
        }
    private:
        iterators_t _begin, _end;
    };


    template<class... Container>
    auto zip(Container &&... args)
    {
        return zip_container<typename resolve_iterator<Container>::type...>(
                std::forward_as_tuple(std::begin(args)...),
                std::forward_as_tuple(std::end(args)...));
                //std::make_tuple(std::begin(std::forward<Container>(args))...),
                //std::make_tuple(std::end(std::forward<Container>(args))...));
    }
}