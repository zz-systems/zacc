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

#include <numeric>

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
        return std::accumulate(first + 1, last, first->str(),
                        [separator](std::string &acc, auto &part) {
                            return acc + separator + part.str();
            });
    }

}