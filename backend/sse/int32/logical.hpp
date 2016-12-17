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
#include "../../../common/compose.hpp"

namespace zacc {
    namespace sse {
        namespace int32_policies {

            template<typename aggregate_t>
            struct logical {
                template<typename base_t>
                struct negate_policy : public base_t {
                    FORWARD(negate_policy);

                    friend
                    aggregate_t
                    operator!(const aggregate_t one) {
                        auto zero = _mm_setzero_si128();
                        auto ones = _mm_cmpeq_epi32(zero, zero);

                        return _mm_xor_si128(one.get_value(), ones);
                    }
                };

                template<typename base_t>
                struct or_policy : public base_t {
                    FORWARD(or_policy);

                    friend
                    aggregate_t
                    operator||(const aggregate_t one, const aggregate_t other) {
                        return _mm_or_epi32(one.get_value(), other._value);
                    }
                };

                template<typename base_t>
                struct and_policy : public base_t {
                    FORWARD(and_policy);

                    friend
                    aggregate_t
                    operator&&(const aggregate_t one, const aggregate_t other) {
                        return _mm_and_epi32(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct compare_eq_policy : public base_t {
                    FORWARD(compare_eq_policy);

                    friend
                    aggregate_t
                    operator==(const aggregate_t one, const aggregate_t other) {
                        return _mm_cmpeq_epi32(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct compare_neq_policy : public base_t {
                    FORWARD(compare_neq_policy);

                    friend
                    aggregate_t
                    operator!=(const aggregate_t one, const aggregate_t other) {
                        return _mm_cmpneq_epi32(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct compare_gt_policy : public base_t {
                    FORWARD(compare_gt_policy);

                    friend
                    aggregate_t
                    operator>(const aggregate_t one, const aggregate_t other) {
                        return _mm_cmpgt_epi32(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct compare_lt_policy : public base_t {
                    FORWARD(compare_lt_policy);

                    friend
                    aggregate_t
                    operator<(const aggregate_t one, const aggregate_t other) {
                        return _mm_cmplt_epi32(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct compare_ge_policy : public base_t {
                    FORWARD(compare_ge_policy);

                    friend
                    aggregate_t
                    operator>=(const aggregate_t one, const aggregate_t other) {
                        return _mm_cmpge_epi32(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct compare_le_policy : public base_t {
                    FORWARD(compare_le_policy);

                    friend
                    aggregate_t
                    operator<=(const aggregate_t one, const aggregate_t other) {
                        return _mm_cmple_epi32(one.get_value(), other.get_value());
                    }
                };
            };
        }
    }
}