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

    template<typename base_t>
    struct extractable : public base_t {
        FORWARD(extractable);
        typedef typename base_t::extracted_type extracted_t;

        const extracted_t data() const {
            extracted_t result;

            base_t::store(result);

            return result;
        }

        extracted_t
        data() {
            extracted_t result;

            base_t::store(result);

            return result;
        }
    };

    template<typename base_t>
    struct iteratable : base_t {

        TRAIT(traits::Iteratable);

        FORWARD(iteratable);

        using iterator      = typename base_t::extracted_type::iterator;

        iterator begin() {
            _snapshot = base_t::data();
            return _snapshot.begin();
        }

        iterator end() { return _snapshot.end(); }

    private:
        typename base_t::extracted_type _snapshot;
    };

    template<typename base_t>
    struct printable : base_t {
        TRAIT(traits::Printable);
//        REQUIRE(traits::Iteratable);

        FORWARD(printable);

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

        friend std::ostream &operator<<(std::ostream &os, const printable data) {
            os << data.to_string();
        }
    };
}