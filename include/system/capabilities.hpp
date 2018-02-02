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
    enum class capabilities : uint64_t {
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
    class capability
    {
        typedef const char* c_str_t;

    public:

        using flag_t = std::underlying_type_t<capabilities>;

        /**
         * @brief constructs metadata with capability and string representation
         * @param capability capability
         * @param str string representation
         * @param is_set availability flag
         */
        constexpr capability(const capabilities capability, const char* str, bool is_set = false)
                : _capability(capability), _c_str(str), _is_set(is_set)
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
         * @brief returns capability's string representation
         * @return C-string representation
         */
        constexpr const char* c_str() const { return _c_str; }

        /**
         * @brief implicit cast to capability's string representation
         * @return C-string representation
         */
        constexpr operator const char*() const { return c_str(); };

        /**
         * @brief returns capability enum value
         * @return capability enum value
         */
        constexpr capabilities value() const { return _capability; }

        /**
         * @brief implicit cast to capability enum value
         * @return raw capability enum value
         */
        constexpr operator capabilities() const { return value(); };

        /**
         * @brief returns raw underlying value
         * @return raw underlying value
         */
        constexpr flag_t raw_value() const { return static_cast<flag_t>(_capability); }

        /**
         * @brief implicit cast to raw underlying value
         * @return raw underlying value
         */
        constexpr operator flag_t() const { return raw_value(); };

        /**
         * @brief implicit cast to capability's string representation
         * @return std::string representation
         */
        std::string str() const { return _c_str; }

        /**
         * @brief provides bitwise-or functionality
         * @param other other capability
         * @return result of bitwise-or as raw underlying value
         */
        constexpr flag_t operator |(const capability &other) { return raw_value() | other.raw_value(); }

        /**
         * @brief provides bitwise-and functionality
         * @param other other capability
         * @return result of bitwise-and as raw underlying value
         */
        constexpr flag_t operator &(const capability &other) { return raw_value() & other.raw_value(); }

        /**
         * @brief returns true if this capability is available
         * @return true if capability set, otherwise false
         */
        bool is_set() { return _is_set; }

        /**
         * @brief pretty-prints the current capability
         * @param os target output stream
         * @param cap capability object
         * @return modified target output stream
         */
        friend inline std::ostream& operator<<(std::ostream& os, const capability& cap) {
            using namespace std;

            const int w = 15;

            os << left << setw(w) << cap.c_str() << boolcolor(cap._is_set) << endl;

            return os;
        }

        /**
         * @brief sets all capabilities to enabled until the given one and returns the raw value
         * @param capability highest capability (inclusive)
         * @return raw value
         */
        static constexpr flag_t fill_up_to(const capabilities capability)
        {
            auto value = to_underlying(capability);
            uint64_t result = 0;

            for(size_t i = 0; i < ntz(value); i++)
            {
                result |= 1;
                result <<= 1;
            }

            return result;
        }

        /**
         * @brief capability dispatcher. from aggregated integer representation one can extract specific features
         * @tparam capability aggregated integer representation
         */
        template<uint64_t capability = 0>
        struct dispatcher {

            using flag_t = std::make_unsigned_t<capabilities>;

            /**
             * @brief checks if a particular capability is set
             * @param flag capability to check
             * @return true if capability is set
             */
            static constexpr bool is_set(capabilities flag)
            {
                return 0 != (flags & static_cast<flag_t>(flag));
            }

            /// current capabilities
            static constexpr flag_t flags = capability;

            /// usually all branches provide floating types
            static constexpr bool has_floating_types = true;

            /// AVX 1 does not provide operations on integer types
            static constexpr bool has_integer_types = !is_set(capabilities::AVX1) || is_set(capabilities::AVX2);

            /// fast (lower precision) float enabled?
            static constexpr bool use_fast_float = is_set(capabilities::FASTFLOAT);
        };
    private:
        const capabilities _capability;
        const char* _c_str;
        bool _is_set;
    };


    template<typename T, capabilities feature>
    constexpr bool has_feature_v = capability::dispatcher<zval_traits<T>::features>::is_set(feature);

    template<typename T>
    constexpr bool has_integer_types_v = capability::dispatcher<zval_traits<T>::features>::has_integer_types;

    template<typename T>
    constexpr bool has_floating_types_v = capability::dispatcher<zval_traits<T>::features>::has_floating_types;

    template <typename T, typename... TList>
    static constexpr std::enable_if_t<std::is_same<T, capabilities>::value, capability::flag_t>
    make_flag(T && capability, TList &&... list) noexcept {
        return static_cast<std::underlying_type_t<capabilities>>(capability) | make_flag(std::forward<TList>(list)...);
    }

    template <typename T>
    static constexpr std::enable_if_t<std::is_same<T, capabilities>::value, capability::flag_t>
    make_flag(T capability) noexcept {
        return static_cast<std::underlying_type_t<capabilities>>(capability);
    }

    struct branches {
        using flag_t        = std::underlying_type_t<capabilities>;

        struct scalar       : public std::integral_constant<flag_t, make_flag(capabilities::SCALAR)>
        {
            static const std::string branch_name() { return "scalar"; }
        };

        struct sse2         : public std::integral_constant<flag_t, make_flag(capabilities::SSE2)>
        {
            static const std::string branch_name() { return "sse.sse2"; }
        };

        struct sse3         : public std::integral_constant<flag_t, sse2::value | make_flag(capabilities::SSE3, capabilities::SSSE3)>
        {
            static const std::string branch_name() { return "sse.sse3"; }
        };

        struct sse41        : public std::integral_constant<flag_t, sse3::value | make_flag(capabilities::SSE41)>
        {
            static const std::string branch_name() { return "sse.sse41"; }
        };

        struct sse41_fma3   : public std::integral_constant<flag_t, sse41::value | make_flag(capabilities::FMA3)>
        {
            static const std::string branch_name() { return "sse.sse41.fma3"; }
        };

        struct sse41_fma4   : public std::integral_constant<flag_t, sse41::value | make_flag(capabilities::FMA4)>
        {
            static const std::string branch_name() { return "sse.sse41.fma4"; }
        };

        struct avx1         : public std::integral_constant<flag_t, make_flag(capabilities::AVX1)>
        {
            static const std::string branch_name() { return "avx.avx1"; }
        };

        struct avx1_fma3     : public std::integral_constant<flag_t, make_flag(capabilities::FMA3, capabilities::AVX1)>
        {
            static const std::string branch_name() { return "avx.avx1.fma3"; }
        };

        struct avx2         : public std::integral_constant<flag_t, avx1_fma3::value | make_flag(capabilities::AVX2)>
        {
            static const std::string branch_name() { return "avx.avx2"; }
        };

        struct avx512       : public std::integral_constant<flag_t, make_flag(capabilities::AVX512)>
        {
            static const std::string branch_name() { return "avx.avx512"; }
        };

        struct opencl       : public std::integral_constant<flag_t, make_flag(capabilities::OPENCL)>
        {
            static const std::string branch_name() { return "gpgpu.opencl"; }
        };
    };


}