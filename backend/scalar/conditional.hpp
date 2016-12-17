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


#ifndef ZACC_CONDITIONAL_POLICIES_HPP
#define ZACC_CONDITIONAL_POLICIES_HPP

namespace zacc {
    namespace scalar {
        template<typename aggregate_t>
        struct conditional_policies {
            template<typename base_t>
            struct if_policy;

            template<typename base_t, typename never_compose = void>
            struct else_policy {
                aggregate_t otherwise(const aggregate_t else_value) const {
                    return _condition
                           ? _if_value
                           : else_value;
                }

            private:
                else_policy(bool condition, const aggregate_t if_value)
                        : _condition(condition), _if_value(if_value) {}

                aggregate_t _if_value;
                bool _condition = false;

                friend struct if_policy<base_t>;
            };

            template<typename base_t>
            struct if_policy
                    : public base_t {
                FORWARD(if_policy);

                else_policy<base_t> when(bool condition) {
                    return else_policy<base_t>(condition, *this);
                }
            };
        };
    }
}
#endif //ZACC_CONDITIONAL_POLICIES_HPP
