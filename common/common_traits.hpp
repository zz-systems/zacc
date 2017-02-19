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

#include "common.hpp"
#include "traits.hpp"

#include <sstream>

namespace zacc {

    struct iteratable {
        template<typename base_t>
        struct impl : public base_t {
            FORWARD(impl);

            REQUIRE(traits::IO);
            TRAIT(traits::Iteratable);

            using iterator          = typename base_t::extracted_t::iterator;

            iterator begin() {
                _snapshot = base_t::data();
                return _snapshot.begin();
            }

            iterator end() { return _snapshot.end(); }

        private:
            typename base_t::extracted_t _snapshot;
        };
    };


    struct printable {
        template<typename base_t>
        struct impl : public base_t {
            FORWARD(impl);

            REQUIRE(traits::Iteratable);
            TRAIT(traits::Printable);

            std::string to_string() const {
                std::stringstream ss;

                if (base_t::is_vector)
                    ss << "[ ";

                for (auto entry : base_t::data())
                    ss << entry << " ";

                if (base_t::is_vector)
                    ss << "]";

                return ss.str();
            }

            friend std::ostream &operator<<(std::ostream &os, const impl data) {
                os << data.to_string();
            }
        };
    };


    struct convertable {
        template<typename base_t>
        struct impl : public base_t {
            FORWARD(impl);

            TRAIT(traits::Convertable);

            auto as_bool()
            {
                return bval<impl>(*this);
            }
        };
    };

    struct boolvec
    {
        template<typename base_t>
        struct impl : public base_t {
            using extracted_t = std::array<bool, base_t::dim>;

            FORWARD(impl);

            REQUIRE(traits::IO);
            TRAIT(traits::IO);

            const extracted_t data() const {
                alignas(base_t::alignment) typename base_t::extracted_t raw;
                extracted_t result;

                base_t::store(raw);

                for (auto i = 0; i < base_t::dim; i++)
                    result[i] = raw[i] != 0;

                return result;
            }

            extracted_t
            data() {
                alignas(base_t::alignment) typename base_t::extracted_t raw;
                extracted_t result;


                base_t::store(raw);

                for (auto i = 0; i < base_t::dim; i++)
                    result[i] = raw[i] != 0;

                return result;
            }
        };
    };
}