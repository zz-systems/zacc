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

/**
 * @file collections.h
 *
 * @brief auxiliary collections
 */

#include <map>
#include <vector>
#include "util/type/type_casts.hpp"
#include "util/memory.hpp"


namespace zacc {
    /// std::map with aligned_allocator
    template<typename key, typename value, typename comparator = std::less<key>>
    using aligned_map = std::map<key, value, comparator, aligned_allocator<std::pair<const key, value>, alignof(value)>>;

    /// std::vector with aligned allocator
    template<typename value>
    using aligned_vector = std::vector<value, aligned_allocator<value, alignof(value)>>;

    // Aligned array: not working.

//    template <class _Tp, size_t _Size, size_t _Align = alignof(_Tp)>
//    struct alignas( _Align ) aligned_array
//            : public std::array<_Tp, _Size> {
//
//        using std::array<_Tp, _Size>::__elems_;
//
//        template<typename ...Args> \
//        aligned_array(Args&&... args) : __elems_({ std::forward<Args>(args)... })
//        {}
//    };
//    struct alignas(_Align) aligned_array
//    {
//        // types:
//        typedef aligned_array __self;
//        typedef _Tp                                   value_type;
//        typedef value_type&                           reference;
//        typedef const value_type&                     const_reference;
//        typedef value_type*                           iterator;
//        typedef const value_type*                     const_iterator;
//        typedef value_type*                           pointer;
//        typedef const value_type*                     const_pointer;
//        typedef size_t                                size_type;
//        typedef ptrdiff_t                             difference_type;
//        typedef std::reverse_iterator<iterator>       reverse_iterator;
//        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
//
//        alignas(_Align) std::array<_Tp, _Size> array;
//
//        // No explicit construct/copy/destroy for aggregate type
//        void fill(const value_type& __u)
//        {array.fill(__u);}
//
//        void swap(aligned_array& __a) noexcept(std::__is_nothrow_swappable<_Tp>::value)
//        {array.swap(__a);}
//
//        // iterators:
//
//        iterator begin() noexcept { return array.begin(); }
//
//        const_iterator begin() const noexcept {return array.begin(); }
//
//        iterator end() noexcept {return array.end();}
//
//        const_iterator end() const noexcept {return array.end(); }
//
//
//        reverse_iterator rbegin() noexcept {return array.rbegin(); }
//
//        const_reverse_iterator rbegin() const noexcept {return array.rbegin(); }
//
//        reverse_iterator rend() noexcept {return array.rend(); }
//
//        const_reverse_iterator rend() const noexcept {return array.rend();}
//
//
//        const_iterator cbegin() const noexcept {return array.cbegin();}
//
//        const_iterator cend() const noexcept {return array.cend();}
//
//        const_reverse_iterator crbegin() const noexcept {return array.crbegin();}
//
//        const_reverse_iterator crend() const noexcept {return array.crend();}
//
//        // capacity:
//
//        constexpr size_type size() const noexcept {return _Size;}
//
//        constexpr size_type max_size() const noexcept {return _Size;}
//
//        constexpr bool empty() const noexcept {return _Size == 0;}
//
//        // element access:
//        reference operator[](size_type __n)             {return array[__n];}
//        constexpr const_reference operator[](size_type __n) const {return array[__n];}
//        reference at(size_type __n) { return array.at(__n); }
//        constexpr const_reference at(size_type __n) const { return array.at(__n); }
//
//        reference front()             {return array.front();}
//        constexpr const_reference front() const {return array.front();}
//        reference back()              {return array.back();}
//        constexpr const_reference back() const  {return array.back();}
//
//
//        value_type* data() noexcept {return array.data();}
//
//        const value_type* data() const noexcept {return array.data();}
//    };
//
//
//    /**
//      * Array casting functionality @ Compiletime.
//      * @origin: http://stackoverflow.com/a/14280396
//      * http://loungecpp.wikidot.com/tips-and-tricks%3aindices
//      */
//
//
//    template<typename T, typename U, size_t i, size_t al, size_t... Is>
//    constexpr auto array_cast_helper(
//            const aligned_array <U, i, al> &a, detail::indices<Is...>) noexcept -> aligned_array <T, i, al>  {
//        return {{static_cast<T>(std::get<Is>(a.array))...}};
//    }
//
//    template<typename T, typename U, size_t i, size_t al>
//    constexpr auto array_cast(
//            const aligned_array<U, i, al> &a) noexcept -> aligned_array<T, i, al>  {
//        // tag dispatch to helper with array indices
//        return array_cast_helper<T>(a, detail::build_indices<i>());
//    }
}