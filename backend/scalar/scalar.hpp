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



#ifndef ZACC_SCALAR_TYPES_HPP
#define ZACC_SCALAR_TYPES_HPP

#include "../../common/zval.hpp"
#include "../../common/compose.hpp"
#include "../../common/conversion/arithmetic.hpp"

#include "arithmetic.hpp"
#include "bitwise.hpp"
#include "logical.hpp"
#include "common.hpp"
#include "conditional.hpp"

namespace zacc {
    using namespace scalar;


    namespace {

        template<typename type_t, typename aggregate_t>
        using integral_type_policies = compose<
                arithmetic_policies<aggregate_t>::template negate_policy,
                arithmetic_policies<aggregate_t>::template add_policy,
                arithmetic_policies<aggregate_t>::template sub_policy,
                arithmetic_policies<aggregate_t>::template mul_policy,
                arithmetic_policies<aggregate_t>::template div_policy,

                bitwise_policies<aggregate_t>::template negate_bitwise_policy,
                bitwise_policies<aggregate_t>::template or_bitwise_policy,
                bitwise_policies<aggregate_t>::template and_bitwise_policy,
                bitwise_policies<aggregate_t>::template xor_bitwise_policy,
                bitwise_policies<aggregate_t>::template shift_left_bitwise_policy,
                bitwise_policies<aggregate_t>::template shift_right_bitwise_policy,

                common_policies<aggregate_t>::template extract_policy,
                common_policies<aggregate_t>::template print_policy,

                logical_policies<aggregate_t>::template negate_logical_policy,
                logical_policies<aggregate_t>::template or_logical_policy,
                logical_policies<aggregate_t>::template and_logical_policy,

                logical_policies<aggregate_t>::template compare_eq_policy,
                logical_policies<aggregate_t>::template compare_neq_policy,

                logical_policies<aggregate_t>::template compare_gt_policy,
                logical_policies<aggregate_t>::template compare_lt_policy,
                logical_policies<aggregate_t>::template compare_ge_policy,
                logical_policies<aggregate_t>::template compare_le_policy,

                conditional_policies<aggregate_t>::template if_policy,

                converting_arithmetic<type_t>::template inject,
                composable<zval<type_t>>::template type
        >;

        template<typename type_t, typename aggregate_t>
        using float_type_policies =  compose<
                arithmetic_policies<aggregate_t>::template negate_policy,
                arithmetic_policies<aggregate_t>::template add_policy,
                arithmetic_policies<aggregate_t>::template sub_policy,
                arithmetic_policies<aggregate_t>::template mul_policy,
                arithmetic_policies<aggregate_t>::template div_policy,

                common_policies<aggregate_t>::template extract_policy,
                common_policies<aggregate_t>::template print_policy,

                logical_policies<aggregate_t>::template negate_policy,
                logical_policies<aggregate_t>::template or_policy,
                logical_policies<aggregate_t>::template and_policy,
                logical_policies<aggregate_t>::template compare_eq_policy,
                logical_policies<aggregate_t>::template compare_neq_policy,
                logical_policies<aggregate_t>::template compare_gt_policy,
                logical_policies<aggregate_t>::template compare_lt_policy,
                logical_policies<aggregate_t>::template compare_ge_policy,
                logical_policies<aggregate_t>::template compare_le_policy,

                converting_arithmetic<type_t>::template inject,
                composable<zval<type_t>>::template type
        >;
    }


    template<typename type_t>
    struct integral_type : public integral_type_policies<type_t, integral_type<type_t>> {
        using base_t = float_type_policies<type_t, integral_type>;

        FORWARD(integral_type);
    };

    template<typename type_t>
    struct float_type : public float_type_policies<type_t, float_type<type_t>> {
        using base_t = float_type_policies<type_t, float_type>;

        FORWARD(float_type);
    };


    using zfloat    = float_type<float>;
    using zdouble   = float_type<double>;

    using zint8     = integral_type<char>;
    using zuint8    = integral_type<unsigned char>;

    using zint16    = integral_type<short>;
    using zuint16   = integral_type<unsigned short>;

    using zint32    = integral_type<int>;
    using zuint32   = integral_type<unsigned int>;

    using zint64    = integral_type<long long>;
    using zuint64   = integral_type<unsigned long long>;

    using zbyte     = zint8;
    using zubyte    = zuint8;

    using zshort    = zint16;
    using zushort   = zuint16;

    using zint      = zint32;
    using zuint     = zuint32;

    using zlong     = zint64;
    using zulong    = zuint64;
}
#endif //ZACC_SCALAR_TYPES_HPP
