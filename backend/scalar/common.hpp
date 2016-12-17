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


#ifndef ZACC_COMMON_IMPL_HPP
#define ZACC_COMMON_IMPL_HPP

#include <sstream>
#include "../../common/compose.hpp"

namespace zacc {
    namespace scalar {
        template<typename aggregate_t>
        struct common_policies {
            template<typename base_t>
            struct extract_policy : public base_t {
                FORWARD(extract_policy);

                typedef typename base_t::extracted_type extracted_t;

                const extracted_t extract() const {
                    extracted_t result;
                    extract_to(result);
                    return result;
                };

                extracted_t
                extract() { return const_cast<extracted_t>(static_cast<const extract_policy *>((this)->extract())); }

                void extract_to(extracted_t &target) const;
            };

            template<typename base_t>
            struct print_policy : public base_t {
                FORWARD(print_policy);

                std::string to_string() const {
                    std::ostringstream ss;
                    ss << base_t::get_value();
                    return ss.str();
                };

                friend std::ostream &operator<<(std::ostream &os, const print_policy &data) { os << data.to_string(); }
            };
        };
    }
}
#endif //ZACC_COMMON_IMPL_HPP
