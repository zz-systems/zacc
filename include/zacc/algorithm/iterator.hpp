//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2019 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

namespace zacc
{
    //==================================================================================================================

    /**
     *
     * @tparam Container
     */
    template<typename Container>
    struct reverse_adapter
    {
        Container& _container;

        reverse_adapter(Container& container)
            : _container(container)
        {}


        auto begin()
        {
            return _container.rbegin();
        }

        auto end()
        {
            return _container.rend();
        }
    };

    /**
     *
     * @tparam Container
     * @param container
     * @return
     */
    template<typename Container>
    auto reverse(Container&& container)
    {
        return reverse_adapter<Container>(std::forward<Container>(container));
    }

    //==================================================================================================================

    template<typename Container>
    struct enumerate_adapter
    {
        struct item
        {
            size_t index;
            typename Container::value_type &item;
        };

        using value_type = item;

        struct iterator
        {
            constexpr explicit iterator(typename Container::iterator iter, size_t counter = 0) noexcept
                : _iter(iter), _counter(counter)
            {}

            iterator operator++()
            {
                return iterator(++_iter, ++_counter);
            }

            bool operator!=(iterator other)
            {
                return _iter != other._iter;
            }

            typename Container::iterator::value_type item()
            {
                return *_iter;
            }

            value_type operator*()
            {
                return {_counter, *_iter};
            }

            size_t index()
            {
                return _counter;
            }

        private:
            typename Container::iterator _iter;
            size_t _counter;
        };

        constexpr  explicit enumerate_adapter(Container &container) noexcept
            : _container(container)
        {}

        iterator begin()
        {
            return iterator(_container.begin());
        }

        iterator begin() const
        {
            return iterator(_container.begin());
        }

        iterator end()
        {
            return iterator(_container.end());
        }

        iterator end() const
        {
            return iterator(_container.end());
        }

    private:
        Container &_container;
    };

    template<typename Container>
    constexpr auto enumerate(Container&& container) noexcept
    {
        return enumerate_adapter<std::remove_reference_t<Container>> { std::forward<Container>(container) };
    }
}