//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2018 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

#include <tuple>
#include "util/type/type_traits.hpp"

namespace zacc
{
    template<typename Composed, typename Interface, bool DisableOverloads = false>
    using ops_meta = std::tuple<Composed, Interface, std::integral_constant<bool, DisableOverloads>>;

     
    
    template<typename Meta, typename U>
    using op_enable = std::enable_if_t<!std::tuple_element_t<2, Meta>::value && !std::is_same<U, std::tuple_element_t<0, Meta>>::value>;
    


    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct plus {
        template<typename U, op_enable<Meta, U>>
        friend T operator+ (param_t<T> one, U other) {
            return one + static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend T operator+ (U one, param_t<T> other) {
            return static_cast<T>(one) + other;
        }

        template<typename U>
        friend T& operator+= (T& one, const U& other) {
            return one = one + other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct minus {
        template<typename U, op_enable<Meta, U>>
        friend T operator- (param_t<T> one, U other) {
            return one - static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend T operator- (U one, param_t<T> other) {
            return static_cast<T>(one) - other;
        }

        template<typename U>
        friend T& operator-= (T& one, const U& other) {
            return one = one - other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct multiplies {
        template<typename U, op_enable<Meta, U>>
        friend T operator* (param_t<T> one, U other) {
            return one * static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend T operator* (U one, param_t<T> other) {
            return static_cast<T>(one) * other;
        }

        template<typename U>
        friend T& operator*= (T& one, const U& other) {
            return one = one * other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct divides {
        template<typename U, op_enable<Meta, U>>
        friend T operator/ (param_t<T> one, U other) {
            return one / static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend T operator/ (U one, param_t<T> other) {
            return static_cast<T>(one) / other;
        }

        template<typename U>
        friend T& operator/= (T& one, const U& other) {
            return one = one / other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct modulus {
        template<typename U, op_enable<Meta, U>>
        friend T operator% (param_t<T> one, U other) {
            return one % static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend T operator% (U one, param_t<T> other) {
            return static_cast<T>(one) % other;
        }

        template<typename U>
        friend T& operator%= (T& one, const U& other) {
            return one = one % other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct increment {
        T operator++ (int) {
            auto temp = *static_cast<T*>(this);

            ++(*static_cast<T*>(this));

            return temp;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct decrement {
        T operator-- (int) {
            auto temp = *static_cast<T*>(this);

            --(*static_cast<T*>(this));

            return temp;
        }
    };

    // =================================================================================================================

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct equal_to {
        template<typename U, op_enable<Meta, U>>
        friend bval_t<Interface> operator== (param_t<T> one, U other) {
            return one == static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend bval_t<Interface> operator== (U one, param_t<T> other) {
            return static_cast<T>(one) == other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct not_equal_to {
        template<typename U, op_enable<Meta, U>>
        friend bval_t<Interface> operator!= (param_t<T> one, U other) {
            return one != static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend bval_t<Interface> operator!= (U one, param_t<T> other) {
            return static_cast<T>(one) != other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct greater {
        template<typename U, op_enable<Meta, U>>
        friend bval_t<Interface> operator> (param_t<T> one, U other) {
            return one > static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend bval_t<Interface> operator> (U one, param_t<T> other) {
            return static_cast<T>(one) > other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct less {
        template<typename U, op_enable<Meta, U>>
        friend bval_t<Interface> operator< (param_t<T> one, U other) {
            return one < static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend bval_t<Interface> operator< (U one, param_t<T> other) {
            return static_cast<T>(one) < other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct greater_equal {
        template<typename U, op_enable<Meta, U>>
        friend bval_t<Interface> operator>= (param_t<T> one, U other) {
            return one >= static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend T operator>= (U one, param_t<T> other) {
            return static_cast<T>(one) >= other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct less_equal {
        template<typename U, op_enable<Meta, U>>
        friend bval_t<Interface> operator<= (param_t<T> one, U other) {
            return one <= static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend bval_t<Interface> operator<= (U one, param_t<T> other) {
            return static_cast<T>(one) <= other;
        }
    };

    // =================================================================================================================

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct logical_and {
        template<typename U, op_enable<Meta, U>>
        friend T operator&& (param_t<T> one, U other) {
            return one && static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend T operator&& (U one, param_t<T> other) {
            return static_cast<T>(one) && other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct logical_or {
        template<typename U, op_enable<Meta, U>>
        friend T operator|| (param_t<T> one, U other) {
            return one || static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend T operator|| (U one, param_t<T> other) {
            return static_cast<T>(one) || other;
        }
    };

    // =================================================================================================================

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct bit_and {
        template<typename U, op_enable<Meta, U>>
        friend T operator& (param_t<T> one, U other) {
            return one & static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend T operator& (U one, param_t<T> other) {
            return static_cast<T>(one) & other;
        }

        template<typename U>
        friend T& operator&= (T& one, const U& other) {
            return one = one & other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct bit_or {
        template<typename U, op_enable<Meta, U>>
        friend T operator| (param_t<T> one, U other) {
            return one | static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend T operator| (U one, param_t<T> other) {
            return static_cast<T>(one) | other;
        }

        template<typename U>
        friend T& operator|= (T& one, const U& other) {
            return one = one | other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct bit_xor {
        template<typename U, op_enable<Meta, U>>
        friend T operator^ (param_t<T> one, U other) {
            return one ^ static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend T operator^ (U one, param_t<T> other) {
            return static_cast<T>(one) ^ other;
        }

        template<typename U>
        friend T& operator^= (T& one, const U& other) {
            return one = one ^ other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct bit_shl {
        template<typename U, op_enable<Meta, U>>
        friend T operator<< (param_t<T> one, U other) {
            return one << static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend T operator<< (U one, param_t<T> other) {
            return static_cast<T>(one) << other;
        }

        template<typename U>
        friend T& operator<<= (T& one, const U& other) {
            return one = one << other;
        }
    };

    template<typename Meta, typename T = std::tuple_element_t<0, Meta>, typename Interface = std::tuple_element_t<1, Meta>>
    struct bit_shr {
        template<typename U, op_enable<Meta, U>>
        friend T operator>> (param_t<T> one, U other) {
            return one >> static_cast<T>(other);
        }

        template<typename U, op_enable<Meta, U>>
        friend T operator>> (U one, param_t<T> other) {
            return static_cast<T>(one) >> other;
        }

        template<typename U>
        friend T& operator>>= (T& one, const U& other) {
            return one = one >> other;
        }
    };
}