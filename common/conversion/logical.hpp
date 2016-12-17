//
// Created by Sergej Zuyev on 12/12/2016.
//

#pragma once

namespace zacc {
    template<typename T, typename U = bool>
    struct can_negate_logical : public T {
        T operator!() const;
    };

    template<typename T, typename U = bool>
    struct can_or_logical : public T {
        T operator||(const T other) const;
    };

    template<typename T, typename U = bool>
    struct can_and_logical : public T {
        T operator&&(const T other) const;
    };

    template<typename T, typename U = bool>
    struct can_compare_eq : public T {
        U operator==(const T other) const;
    };

    template<typename T, typename U = bool>
    struct can_compare_neq : public T {
        U operator!=(const T other) const;
    };

    template<typename T, typename U = bool>
    struct can_compare_gt : public T {
        U operator>(const T other) const;
    };

    template<typename T, typename U = bool>
    struct can_compare_lt : public T {
        U operator<(const T other) const;
    };

    template<typename T, typename U = bool>
    struct can_compare_ge : public T {
        U operator>=(const T other) const;
    };

    template<typename T, typename U = bool>
    struct can_compare_le : public T {
        U operator<=(const T other) const;
    };
}