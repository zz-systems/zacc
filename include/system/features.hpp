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

namespace zacc {

    /// @enum capabilities
    /// @brief relevant system capabilities
    enum class features : uint64_t {
        SCALAR      = 0,         ///< simply x87 FPU
        SSE2        = 1 << 0,    ///< SSE 2 support
        SSE3        = 1 << 1,    ///< SSE 3 support
        SSSE3       = 1 << 2,    ///< SSSE 3 support

        SSE41       = 1 << 3,    ///< SSE 4.1 support
        SSE42       = 1 << 4,    ///< SSE 4.2 support

        FMA3        = 1 << 5,    ///< FMA 3 support
        FMA4        = 1 << 6,    ///< FMA 4 support

        AVX1        = 1 << 7,    ///< AVX support
        AVX2        = 1 << 8,    ///< AVX 2 support
        AVX512      = 1 << 9,    ///< AVX 512 support

        OPENCL      = 1 << 10,   ///< OPENCL support
        FPGA        = 1 << 11,    ///< FPGA synthesis support?

//======================================================================================================================
        FASTFLOAT   = 1 << 30,   ///< use faster float computations ( lower precision )
//======================================================================================================================
    };

    /**
     * @brief Provides metadata and typecasts to capabilities enum
     */
    class feature
    {
        typedef const char* c_str_t;

    public:

        using flag_t = std::underlying_type_t<features>;

        /**
         * @brief constructs metadata with arch and string representation
         * @param arch arch
         * @param str string representation
         * @param is_set availability flag
         */
        constexpr feature(const features arch, const char* str, bool is_set = false)
                : _mask(arch), _c_str(str), _is_set(is_set)
        {}

        /**
         * @brief set the availability flag
         * @param is_set availability flag
         */
        void set(bool is_set)
        {
            _is_set = is_set;
        }

        /**
         * @brief returns arch's string representation
         * @return C-string representation
         */
        constexpr const char* c_str() const { return _c_str; }

        /**
         * @brief implicit cast to arch's string representation
         * @return C-string representation
         */
        constexpr operator const char*() const { return c_str(); };

        /**
         * @brief returns arch enum value
         * @return arch enum value
         */
        constexpr features value() const { return _mask; }

        /**
         * @brief implicit cast to arch enum value
         * @return raw arch enum value
         */
        constexpr operator features() const { return value(); };

        /**
         * @brief returns raw underlying value
         * @return raw underlying value
         */
        constexpr flag_t mask() const { return static_cast<flag_t>(_mask); }

        /**
         * @brief implicit cast to raw underlying value
         * @return raw underlying value
         */
        constexpr operator flag_t() const { return mask(); };

        /**
         * @brief implicit cast to arch's string representation
         * @return std::string representation
         */
        std::string str() const { return _c_str; }

        /**
         * @brief provides bitwise-or functionality
         * @param other other arch
         * @return result of bitwise-or as raw underlying value
         */
        constexpr flag_t operator |(const feature &other) const { return mask() | other.mask(); }

        /**
         * @brief provides bitwise-and functionality
         * @param other other arch
         * @return result of bitwise-and as raw underlying value
         */
        constexpr flag_t operator &(const feature &other) const { return mask() & other.mask(); }

        /**
         * @brief returns true if this arch is available
         * @return true if arch set, otherwise false
         */
        bool is_set() { return _is_set; }

        /**
         * @brief pretty-prints the current arch
         * @param os target output stream
         * @param cap arch object
         * @return modified target output stream
         */
        friend inline std::ostream& operator<<(std::ostream& os, const feature& cap) {
            using namespace std;

            const int w = 15;

            os << left << setw(w) << cap.c_str() << boolcolor(cap._is_set) << endl;

            return os;
        }

//        /**
//         * @brief sets all features to enabled until the given one and returns the raw value
//         * @param arch highest arch (inclusive)
//         * @return raw value
//         */
//        static constexpr flag_t fill_up_to(const features arch)
//        {
//            auto value = to_underlying(arch);
//            uint64_t result = 0;
//
//            for(size_t i = 0; i < ntz(value); i++)
//            {
//                result |= 1;
//                result <<= 1;
//            }
//
//            return result;
//        }


    private:
        const features _mask;
        const char* _c_str;
        bool _is_set;
    };


    /**
     * @brief arch dispatcher. from aggregated integer representation one can extract specific features
     * @tparam arch aggregated integer representation
     */
    template<uint64_t arch = 0>
    struct dispatcher {

        using flag_t = std::make_unsigned_t<features>;

        /**
         * @brief checks if a particular arch is set
         * @param flag arch to check
         * @return true if arch is set
         */
        static constexpr bool is_set(features flag)
        {
            return 0 != (flags & static_cast<flag_t>(flag));
        }

        /// current capabilities
        static constexpr flag_t flags = arch;

        /// usually all branches provide floating types
        static constexpr bool has_floating_types = true;

        /// AVX 1 does not provide operations on integer types
        static constexpr bool has_integer_types = !is_set(features::AVX1) || is_set(features::AVX2);

        /// fast (lower precision) float enabled?
        static constexpr bool use_fast_float = is_set(features::FASTFLOAT);
    };

    template<typename T, features feature>
    constexpr bool has_feature_v = dispatcher<T::feature_mask>::is_set(feature);

    template<typename T>
    constexpr bool has_integer_types_v = dispatcher<T::feature_mask>::has_integer_types;

    template<typename T>
    constexpr bool has_floating_types_v = dispatcher<T::feature_mask>::has_floating_types;

    template <typename T, typename... TList>
    static constexpr std::enable_if_t<std::is_same<T, features>::value, feature::flag_t>
    make_flag(T && arch, TList &&... list) noexcept {
        return static_cast<std::underlying_type_t<features>>(arch) | make_flag(std::forward<TList>(list)...);
    }

    template <typename T>
    static constexpr std::enable_if_t<std::is_same<T, features>::value, feature::flag_t>
    make_flag(T arch) noexcept {
        return static_cast<std::underlying_type_t<features>>(arch);
    }

    struct arch
    {
        using flag_t        = std::underlying_type_t<features>;

        flag_t features;
        std::string name;

        arch()
            : features(0), name()
        {}

        template<typename T>
        arch(T)
            : features(T::value), name(T::name())
        {}

        arch(const arch& other)
            : features(other.features), name(other.name)
        {}

        arch(arch&& other)
            : arch()
        {
            swap(*this, other);
        }

        arch& operator=(arch other)
        {
            swap(*this, other);
            return *this;
        }

        friend void swap(arch& one, arch& other)
        {
            std::swap(one.features, other.features);
            std::swap(one.name, other.name);
        }

        constexpr bool is_none() const { return features == 0 && name.empty(); }
        
        struct scalar       : public std::integral_constant<flag_t, make_flag(features::SCALAR)>
        {
            static const std::string name() { return "scalar"; }
        };

        struct sse2         : public std::integral_constant<flag_t, make_flag(features::SSE2)>
        {
            static const std::string name() { return "sse.sse2"; }
        };

        struct sse3         : public std::integral_constant<flag_t, sse2::value | make_flag(features::SSE3, features::SSSE3)>
        {
            static const std::string name() { return "sse.sse3"; }
        };

        struct sse41        : public std::integral_constant<flag_t, sse3::value | make_flag(features::SSE41)>
        {
            static const std::string name() { return "sse.sse41"; }
        };

        struct sse41_fma3   : public std::integral_constant<flag_t, sse41::value | make_flag(features::FMA3)>
        {
            static const std::string name() { return "sse.sse41.fma3"; }
        };

        struct sse41_fma4   : public std::integral_constant<flag_t, sse41::value | make_flag(features::FMA4)>
        {
            static const std::string name() { return "sse.sse41.fma4"; }
        };

        struct avx1         : public std::integral_constant<flag_t, make_flag(features::AVX1)>
        {
            static const std::string name() { return "avx.avx1"; }
        };

        struct avx1_fma3     : public std::integral_constant<flag_t, make_flag(features::FMA3, features::AVX1)>
        {
            static const std::string name() { return "avx.avx1.fma3"; }
        };

        struct avx2         : public std::integral_constant<flag_t, avx1_fma3::value | make_flag(features::AVX2)>
        {
            static const std::string name() { return "avx.avx2"; }
        };

        struct avx512       : public std::integral_constant<flag_t, make_flag(features::AVX512)>
        {
            static const std::string name() { return "avx.avx512"; }
        };

        struct opencl       : public std::integral_constant<flag_t, make_flag(features::OPENCL)>
        {
            static const std::string name() { return "gpgpu.opencl"; }
        };
    };

}