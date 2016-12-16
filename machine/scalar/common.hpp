//
// Created by Sergej Zuyev on 12/13/2016.
//

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
