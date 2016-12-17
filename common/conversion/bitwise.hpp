//
// Created by Sergej Zuyev on 12/12/2016.
//

#pragma once

namespace zacc {
    template<typename T>
    struct can_negate_bitwise : public T {
        T operator~() const;
    };

    template<typename T>
    struct can_or_bitwise : public T {
        T operator|(const T other) const;
    };

    template<typename T>
    struct can_and_bitwise : public T {
        T operator&(const T other) const;
    };

    template<typename T>
    struct can_xor_bitwise : public T {
        T operator^(const T other) const;
    };

    template<typename T, typename U = size_t>
    struct can_shift_left_bitwise : public T {
        T operator<<(const U shift_amount) const;
    };

    template<typename T, typename U = size_t>
    struct can_shift_right_bitwise : public T {
        T operator>>(const U shift_amount) const;
    };
}
