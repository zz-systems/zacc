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
#include "../../common/common_traits.hpp"

#include "generated/float32.gen.hpp"

namespace zacc {
    //namespace {

//        template<typename type_t, typename aggregate_t>
//        using integral_type_policies = compose<
//
//                printable,
//                iteratable,
//                extractable,
//
//                scalar::int_arithmetic<aggregate_t>::template impl,
//                scalar::int_io<aggregate_t>::template impl,
//                scalar::int_conditional<aggregate_t>::template impl,
//                scalar::int_logical<aggregate_t>::template impl,
//                scalar::int_comparison<aggregate_t>::template impl,
//                scalar::int_bitwise<aggregate_t>::template impl,
//
//                composable<zval<type_t>>::template type
//        >;
//
//        template<typename type_t, typename aggregate_t>
//        using float_type_policies =  compose<
//
//                printable,
//                iteratable,
//                extractable,
//
//                scalar::float_arithmetic<aggregate_t>::template impl,
//                scalar::float_io<aggregate_t>::template impl,
//                scalar::float_conditional<aggregate_t>::template impl,
//                scalar::float_logical<aggregate_t>::template impl,
//                scalar::float_comparison<aggregate_t>::template impl,
//                scalar::float_bitwise<aggregate_t>::template impl,
//
//                composable<zval<type_t>>::template type
//        >;
//    //}
//
//
//    template<typename type_t>
//    struct integral_type : public integral_type_policies<type_t, integral_type<type_t>> {
//        using base_t = float_type_policies<type_t, integral_type>;
//
//        FORWARD(integral_type);
//    };
//
//    template<typename type_t>
//    struct float_type : public float_type_policies<type_t, float_type<type_t>> {
//        using base_t = float_type_policies<type_t, float_type>;
//
//        FORWARD(float_type);
//    };


//    using zfloat    = scalar::zfloat<float>;
//    using zdouble   = float_type<double>;
//
//    using zint8     = integral_type<char>;
//    using zuint8    = integral_type<unsigned char>;
//
//    using zint16    = integral_type<short>;
//    using zuint16   = integral_type<unsigned short>;
//
//    using zint32    = integral_type<int>;
//    using zuint32   = integral_type<unsigned int>;
//
//    using zint64    = integral_type<long long>;
//    using zuint64   = integral_type<unsigned long long>;
//
//    using zbyte     = zint8;
//    using zubyte    = zuint8;
//
//    using zshort    = zint16;
//    using zushort   = zuint16;
//
//    using zint      = zint32;
//    using zuint     = zuint32;
//
//    using zlong     = zint64;
//    using zulong    = zuint64;
}
#endif //ZACC_SCALAR_TYPES_HPP
