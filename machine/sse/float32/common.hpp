//
// Created by Sergej Zuyev on 12/13/2016.
//

#pragma once

#include <tmmintrin.h>
#include <sstream>
#include "../../../common/compose.hpp"

namespace zacc {
    namespace sse {
        namespace float32_policies {

            template<typename aggregate_t>
            struct common {
                template<typename base_t>
                struct extract_policy : public base_t {
                    FORWARD(extract_policy);

                    typedef typename base_t::extracted_type extracted_t;

                    const extracted_t extract() const {
                        extracted_t result;

                        extract_to(result);

                        return result;
                    }

                    extracted_t
                    extract() { return const_cast<extracted_t>(static_cast<const extract_policy *>((this)->extract())); }

                    void extract_to(extracted_t &target) const {
                        _mm_store_ps(target.data(), base_t::_value);
                    }
                };
            };
        }
    }
}