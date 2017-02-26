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

namespace zacc {

    //
    // Array casting functionality @ Compiletime.
    // @origin: http://stackoverflow.com/a/14280396

    // http://loungecpp.wikidot.com/tips-and-tricks%3aindices
    namespace detail {

        template<std::size_t... Is>
        struct indices {
        };
        template<std::size_t N, std::size_t... Is>
        struct build_indices : build_indices<N - 1, N - 1, Is...> {
        };
        template<std::size_t... Is>
        struct build_indices<0, Is...> : indices<Is...> {
        };

        template<typename T, typename U, size_t i, size_t... Is>
        constexpr auto array_cast_helper(
                const std::array <U, i> &a, indices<Is...>) -> std::array <T, i> {
            return {{static_cast<T>(std::get<Is>(a))...}};
        }
    }
    template<typename T, typename U, size_t i>
    constexpr auto array_cast(
            const std::array<U, i> &a) -> std::array<T, i> {
        // tag dispatch to helper with array indices
        return detail::array_cast_helper<T>(a, detail::build_indices<i>());
    }
}