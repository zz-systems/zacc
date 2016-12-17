//
// Created by Sergej Zuyev on 12/17/2016.
//

#pragma once

#include <iterator>
#include <sstream>
#include "type_traits.hpp"

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
        data() { return const_cast<extracted_t>(static_cast<const extractable *>(this)->data()); }
    };

    template<typename base_t>
    struct iteratable : base_t {
        FORWARD(iteratable);

        using iterator      = typename base_t::extracted_type::iterator;

        iterator begin() { return base_t::data().begin(); }

        iterator end() { return base_t::data().end(); }
    };

    template<typename base_t>
    struct printable : base_t {
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