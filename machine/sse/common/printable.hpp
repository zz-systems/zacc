//
// Created by Sergej Zuyev on 12/12/2016.
//

#pragma once

#include <sstream>

namespace zacc {
    namespace sse {
        namespace common_policies {
            template<typename aggregate_t>
            struct common {
                template<typename base_t>
                struct print_policy : public base_t {
                    FORWARD(print_policy);

                    std::string to_string() const {
                        std::ostringstream ss;
                        ss << "[ ";

                        for (auto item : base_t::extract())
                            ss << item << " ";

                        ss << "]";

                        return ss.str();
                    };

                    friend std::ostream &operator<<(std::ostream &os, const aggregate_t &data) {
                        os << data.to_string();
                    }
                };
            };
        }
    }
}
