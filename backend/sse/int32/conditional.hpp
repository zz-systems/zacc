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

#include <immintrin.h>
#include "../../../dispatch/dispatcher.hpp"

namespace zacc {
    namespace sse {
        namespace int32_policies {

            template<typename aggregate_t>
            struct conditional {
                template<typename base_t>
                struct if_policy;

                template<typename base_t, typename never_compose = void>
                struct else_policy {
                    //accept_if<aggregate_t, capabilities::SSE41, capabilities::SSE42>
                    aggregate_t
                    otherwise(const aggregate_t else_value) const {
                        return _mm_blendv_epi8(_if_value.get_value(), else_value.get_value(),
                                               _mm_cmpeq_epi32(_mm_setzero_si128(), _condition.get_value()));
                    }

                    //reject_if<aggregate_t, capabilities::SSE41, capabilities::SSE42>
                    //aggregate_t
                    //otherwise(const aggregate_t else_value) const
                    //{
                    //    return (_condition & _if_value) | (~_condition & else_value);
                    //}

                private:
                    else_policy(const aggregate_t mask, const aggregate_t if_value)
                            : _condition(mask), _if_value(if_value) {}

                    aggregate_t _if_value;
                    aggregate_t _condition;

                    friend struct if_policy<base_t>;
                };

                template<typename base_t>
                struct if_policy
                        : public base_t {
                    FORWARD(if_policy);

                    else_policy<base_t> when(const aggregate_t mask) const {
                        return else_policy<base_t>(mask, *this);
                    }
                };
            };
        }
    }
}