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


#pragma once

#include <type_traits>

namespace zacc {
    template<typename T>
    struct is_float32 : std::false_type {
    };
    template<>
    struct is_float32<float> : std::true_type {
    };

    using is_float  = is_float32;

    template<typename T>
    struct is_float64 : std::false_type {
    };
    template<>
    struct is_float64<double> : std::true_type {
    };

    using is_double = is_float64;

    template<typename T>
    struct is_int8 : std::false_type {
    };
    template<>
    struct is_int8<char> : std::true_type {
    };

    using is_byte   = is_int8;

    template<typename T>
    struct is_uint8 : std::false_type {
    };
    template<>
    struct is_uint8<unsigned char> : std::true_type {
    };

    using is_ubyte  = is_uint8;

    template<typename T>
    struct is_int16 : std::false_type {
    };
    template<>
    struct is_int16<short> : std::true_type {
    };

    using is_short  = is_int16;

    template<typename T>
    struct is_uint16 : std::false_type {
    };
    template<>
    struct is_uint16<unsigned short> : std::true_type {
    };

    using is_ushort = is_uint16;

    template<typename T>
    struct is_int32 : std::false_type {
    };
    template<>
    struct is_int32<int> : std::true_type {
    };

    using is_int    = is_int32;

    template<typename T>
    struct is_uint32 : std::false_type {
    };
    template<>
    struct is_uint32<unsigned int> : std::true_type {
    };

    using is_uint   = is_uint32;

    template<typename T>
    struct is_int64 : std::false_type {
    };
    template<>
    struct is_int64<long long> : std::true_type {
    };

    using is_long   = is_int64;

    template<typename T>
    struct is_uint64 : std::false_type {
    };
    template<>
    struct is_uint64<unsigned long long> : std::true_type {
    };

    using is_ulong  = is_uint64;
}