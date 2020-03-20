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

#include <iostream>
#include <zacc/util/io.hpp>
#include <zacc/util/type/cast.hpp>
#include <zacc/util/bithacks.hpp>
#include <zacc/util/algorithm.hpp>
#include <zacc/system/feature.hpp>
#include <zacc/util/string_view.hpp>
#include <functional>
#include <algorithm>

namespace zacc {

    struct arch {
        feature mask;
        string_view name;

        constexpr arch()
            : mask{}, name{}
        {}

        template<typename T>
        constexpr arch(T)
            : mask{T::value}, name{T::name()} {}

        constexpr arch(const arch&) = default;

        constexpr arch(arch&& other) noexcept
        : mask {std::move(other.mask)}, name {other.name}
        {
        }

        arch& operator=(const arch& other) = default;

        constexpr bool is_none() const { return mask.mask() == 0 && to_string().empty(); }

        std::string to_string() const { return name; }

        friend std::ostream &operator<<(std::ostream &os, const arch &data) {
            using namespace std;

            os << data.mask;

            return os;
        }

        static constexpr size_t size = 11;

        struct scalar : public std::integral_constant<uint64_t, feature::scalar()>
        {
            static constexpr string_view name() { return "scalar"; }
        };

        struct sse2 : public std::integral_constant<uint64_t, feature::sse2()>
        {
            static constexpr string_view name() { return "sse2"; }
        };

        struct sse3 : public std::integral_constant<uint64_t, feature(feature::sse2(), feature::sse3(),
                                                                      feature::ssse3())>
        {
            static constexpr string_view name() { return "sse3"; }
        };

        struct sse41 : public std::integral_constant<uint64_t, feature(feature::sse2(), feature::sse3(),
                                                                       feature::ssse3(), feature::sse41())>
        {
            static constexpr string_view name() { return "sse41"; }
        };

        struct sse41_fma3 : public std::integral_constant<uint64_t, feature(feature::sse2(), feature::sse3(),
                                                                            feature::ssse3(), feature::sse41(),
                                                                            feature::fma3())>
        {
            static constexpr string_view name() { return "sse41.fma3"; }
        };

        struct sse41_fma4 : public std::integral_constant<uint64_t, feature(feature::sse2(), feature::sse3(),
                                                                            feature::ssse3(), feature::sse41(),
                                                                            feature::fma4())>
        {
            static constexpr string_view name() { return "sse41.fma4"; }
        };

        struct avx1 : public std::integral_constant<uint64_t, feature::avx1()>
        {
            static constexpr string_view name() { return "avx1"; }
        };

        struct avx1_fma3 : public std::integral_constant<uint64_t, feature(feature::avx1(), feature::fma3())>
        {
            static constexpr string_view name() { return "fma3"; }
        };

        struct avx2 : public std::integral_constant<uint64_t, feature(feature::avx1(), feature::fma3(),
                                                                      feature::avx2())>
        {
            static constexpr string_view name() { return "avx2"; }
        };

        struct avx512 : public std::integral_constant<uint64_t, feature::avx512()>
        {
            static constexpr string_view name() { return "avx512"; }
        };

        struct opencl : public std::integral_constant<uint64_t, feature::opencl()>
        {
            static constexpr string_view name() { return "opencl"; }
        };

        static constexpr std::array<arch, size> available()
        {
            return {{
                        opencl(),
                        avx512(), avx2(), avx1_fma3(), avx1(),
                        sse41_fma4(), sse41_fma3(), sse41(), sse3(), sse2(),
                        scalar()
                    }};
        }

        static constexpr arch select(feature mask)
        {
            arch result = arch::scalar();

            for(auto a : arch::available())
            {
                if(a.mask.test(mask))
                {
                    result = a;
                    break;
                }
            }

            std::clog << "[ARCH][SELECT][" << join(result.mask.active(), ", ") << "] ->"
                      << " [" << result.name << "]"
                      << std::endl;

            return result;
        }
    };



//    template<typename T>
//    struct arch_of
//    {
//    };
//
//    template<template<typename> class X, typename T>
//    struct arch_of<X<T>> : arch
//    {
//        constexpr arch_of()
//            : arch(T())
//        {}
//    };

    struct arch_of : arch
    {
        template<template<typename> class X, typename T>
        constexpr arch_of()
            : arch(T())
        {}

        template<template<typename> class X, typename T>
        constexpr arch_of(T)
            : arch(T())
        {}

//        template<typename T>
//        constexpr arch_of()
//            : arch(arch_of<T>())
//        {}
    };
}