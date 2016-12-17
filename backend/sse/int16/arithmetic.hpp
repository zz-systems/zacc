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
#include "../../../common/compose.hpp"

namespace zacc {
    namespace sse {
        namespace int16_policies {

            template<typename aggregate_t>
            struct arithmetic {

                template<typename base_t>
                struct negate_policy : public base_t {

                    FORWARD(negate_policy);

                    friend
                    aggregate_t
                    operator-(const aggregate_t one) {
                        return _mm_sub_epi32(_mm_setzero_si128(), one.get_value());
                    }
                };

                template<typename base_t>
                struct add_policy : public base_t {

                    FORWARD(add_policy);

                    friend
                    aggregate_t
                    operator+(const aggregate_t one, const aggregate_t other) {
                        return _mm_add_epi32(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct sub_policy : public base_t {

                    FORWARD(sub_policy);

                    friend
                    aggregate_t
                    operator-(const aggregate_t one, const aggregate_t other) {
                        return _mm_sub_epi32(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct mul_policy : public base_t {
                    FORWARD(mul_policy);

                    /**
                     * @brief integer multiplication (emulated). For machines without SSE4
                     * @see https://software.intel.com/en-us/forums/intel-c-compiler/topic/288768
                     * @param one left arg
                     * @param other right arg
                     * @return multiplication result
                     */
                    friend
                    reject_if_t <aggregate_t, CAPABILITY_SSE41, CAPABILITY_SSE42>
                    operator*(const aggregate_t one, const aggregate_t other) {
                        /* mul 2,0*/
                        auto tmp1 = _mm_castsi128_ps(_mm_mul_epu32(one.get_value(), other.get_value()));
                        /* mul 3,1 */
                        auto tmp2 = _mm_castsi128_ps(_mm_mul_epu32(_mm_srli_si128(one.get_value(), 4),
                                                                   _mm_srli_si128(other.get_value(), 4)));

                        return _mm_castps_si128(_mm_shuffle_ps(tmp1, tmp2, _MM_SHUFFLE(2, 0, 2, 0)));
                    }

                    /**
                     * @brief integer multiplication (native). For machines with SSE4
                     * @param one left arg
                     * @param other right arg
                     * @return multiplication result
                     */
                    friend
                    accept_if_t <aggregate_t, CAPABILITY_SSE41, CAPABILITY_SSE42>
                    operator*(const aggregate_t one, const aggregate_t other) {
                        return _mm_mullo_epi32(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct div_policy : public base_t {

                    FORWARD(div_policy);

                    friend
                    aggregate_t
                    operator/(const aggregate_t one, const aggregate_t other) {
                        return _mm_div_ps(_mm_cvtepi32_ps(one.get_value()), _mm_cvtepi32_ps(other.get_value()));
                    }
                };
            };
        }
    }
}