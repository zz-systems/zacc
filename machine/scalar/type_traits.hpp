//
// Created by Sergej Zuyev on 12/12/2016.
//

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