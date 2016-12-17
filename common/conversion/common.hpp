//
// Created by Sergej Zuyev on 12/12/2016.
//

#pragma once

#include <string>

namespace zacc {
    template<typename T, typename U>
    struct can_extract : public T {
        U extract() const;

        const U extract() { return const_cast<U>(static_cast<const can_extract *>((this)->extract())); }

        void extract_to(rettype &target) const;
    };

    template<typename T>
    struct can_print {
    public:
        virtual std::string to_string() const = 0;

        friend std::ostream &operator<<(std::ostream &os, const T &data) { os << to_string(); }
    };
}
