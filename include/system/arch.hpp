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
#include "util/io.hpp"
#include "util/type/type_casts.hpp"
#include "util/bithacks.hpp"
#include "util/algorithm.hpp"
#include "system/feature.hpp"
#include <functional>
#include <algorithm>

namespace zacc {
    struct arch {
        feature mask;
        std::string name;

        arch()
                : mask{}, name{} {}

        template<typename T>
        arch(T)
                : mask{T::value}, name{T::name()} {}

        arch(const arch &other) = default;

        arch(arch &&other) noexcept
                : arch() {
            swap(*this, other);
        }

        arch &operator=(arch other) {
            swap(*this, other);
            return *this;
        }

        friend void swap(arch &one, arch &other) {
            std::swap(one.mask, other.mask);
            std::swap(one.name, other.name);
        }

        constexpr bool is_none() const { return mask.mask() == 0 && name.empty(); }

        friend std::ostream &operator<<(std::ostream &os, const arch &data) {
            using namespace std;

            os << data.mask;

            return os;
        }


        struct scalar : public std::integral_constant<uint64_t, feature::scalar()>
        {
            static const std::string name() { return "scalar"; }
        };

        struct sse2 : public std::integral_constant<uint64_t, feature::sse2()>
        {
            static const std::string name() { return "sse.sse2"; }
        };

        struct sse3 : public std::integral_constant<uint64_t, feature(feature::sse2(), feature::sse3(),
                                                                      feature::ssse3())>
        {
            static const std::string name() { return "sse.sse3"; }
        };

        struct sse41 : public std::integral_constant<uint64_t, feature(feature::sse2(), feature::sse3(),
                                                                       feature::ssse3(), feature::sse41())>
        {
            static const std::string name() { return "sse.sse41"; }
        };

        struct sse41_fma3 : public std::integral_constant<uint64_t, feature(feature::sse2(), feature::sse3(),
                                                                            feature::ssse3(), feature::sse41(),
                                                                            feature::fma3())>
        {
            static const std::string name() { return "sse.sse41.fma3"; }
        };

        struct sse41_fma4 : public std::integral_constant<uint64_t, feature(feature::sse2(), feature::sse3(),
                                                                            feature::ssse3(), feature::sse41(),
                                                                            feature::fma4())>
        {
            static const std::string name() { return "sse.sse41.fma4"; }
        };

        struct avx1 : public std::integral_constant<uint64_t, feature::avx1()>
        {
            static const std::string name() { return "avx.avx1"; }
        };

        struct avx1_fma3 : public std::integral_constant<uint64_t, feature(feature::avx1(), feature::fma3())>
        {
            static const std::string name() { return "avx.avx1.fma3"; }
        };

        struct avx2 : public std::integral_constant<uint64_t, feature(feature::avx1(), feature::fma3(),
                                                                      feature::avx2())>
        {
            static const std::string name() { return "avx.avx2"; }
        };

        struct avx512 : public std::integral_constant<uint64_t, feature::avx512()>
        {
            static const std::string name() { return "avx.avx512"; }
        };

        struct opencl : public std::integral_constant<uint64_t, feature::opencl()>
        {
            static const std::string name() { return "gpgpu.opencl"; }
        };
    };
}