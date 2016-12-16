//
// Created by Sergej Zuyev on 12/16/2016.
//

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
