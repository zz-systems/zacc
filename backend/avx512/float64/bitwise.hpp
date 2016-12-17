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
//#include "../../../dispatch/dispatcher.hpp"
//#include "../../common/compose.hpp"

namespace zacc {
    namespace avx {
        namespace float64_policies {

            template<typename aggregate_t>
            struct bitwise {

                template<typename base_t>
                struct negate_policy : public base_t {
                    FORWARD(negate_policy);

                    friend aggregate_t operator~(const aggregate_t one) {
                        auto zero = _mm512_setzero_ps();
                        auto ones = _mm512_cmpeq_ps(zero, zero);

                        return _mm512_xor_ps(one.get_value(), ones);
                    }
                };

                template<typename base_t>
                struct or_policy : public base_t {
                    FORWARD(or_policy);

                    friend aggregate_t operator|(const aggregate_t one, const aggregate_t other) {
                        return _mm512_or_ps(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct and_policy : public base_t {
                    FORWARD(and_policy);

                    friend aggregate_t operator&(const aggregate_t one, const aggregate_t other) {
                        return _mm512_and_ps(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct xor_policy : public base_t {
                    FORWARD(xor_policy);

                    friend aggregate_t operator^(const aggregate_t one, const aggregate_t other) {
                        return _mm512_xor_ps(one.get_value(), other.get_value());
                    }
                };
            };
        }
    }
}