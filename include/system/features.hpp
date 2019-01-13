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
#include <bitset>
#include <functional>
#include <algorithm>

namespace zacc {

//    /// @enum capabilities
//    /// @brief relevant system capabilities
//    enum class features : uint64_t {
//        SCALAR      = 0,         ///< simply x87 FPU
//        SSE2        = 1 << 0,    ///< SSE 2 support
//        SSE3        = 1 << 1,    ///< SSE 3 support
//        SSSE3       = 1 << 2,    ///< SSSE 3 support
//
//        SSE41       = 1 << 3,    ///< SSE 4.1 support
//        SSE42       = 1 << 4,    ///< SSE 4.2 support
//
//        FMA3        = 1 << 5,    ///< FMA 3 support
//        FMA4        = 1 << 6,    ///< FMA 4 support
//
//        AVX1        = 1 << 7,    ///< AVX support
//        AVX2        = 1 << 8,    ///< AVX 2 support
//        AVX512      = 1 << 9,    ///< AVX 512 support
//
//        OPENCL      = 1 << 10,   ///< OPENCL support
//        FPGA        = 1 << 11,    ///< FPGA synthesis support?
//
////======================================================================================================================
//        FASTFLOAT   = 1 << 30,   ///< use faster float computations ( lower precision )
////======================================================================================================================
//    };


    template <typename T, typename... Args>
    constexpr uint64_t or_reduce(T&& feature, Args&& ...args) noexcept
    {
        return feature | or_reduce(std::forward<Args>(args)...);
    }

    template <typename T>
    constexpr uint64_t or_reduce(T&& feature) noexcept
    {
        return feature;
    }

//    struct feature
//    {
//        size_t id;
//        const char* name;
//
//        std::string to_string() const { return name; }
//
//
////        constexpr feature() noexcept
////            : id(0), name(nullptr)
////        {}
////
////        constexpr feature(size_t id, const char* name) noexcept
////                : id(id), name(name)
////        {}
////
////        constexpr feature(const feature& other) = delete;
////        //    : id(other.id), name(other.to_string().c_str())
////        //{}
////
////        constexpr feature(feature&& other) = delete;// noexcept
////        //    : id(other.id), name(other.name)
////        //{}
//    };



    struct feature;

    struct feature
    {
        static constexpr size_t size = 13;

        //size_t id;
        //const char* name;

        constexpr operator uint64_t() { return _mask; }
        operator std::string() { return _name; }

        std::string to_string() const { return _name; }

        constexpr feature() noexcept
            : _mask {0}, _name {""}
        {}

        constexpr explicit feature(uint64_t mask) noexcept
            : _mask(mask), _name {""}
        {}

        constexpr explicit feature(uint64_t mask, const char* name) noexcept
                : _mask(mask), _name(name)
        {}

        template <typename... Args>
        constexpr explicit feature(feature f, Args&& ...args ) noexcept
            : _mask{or_reduce(f, std::forward<Args>(args)...)}, _name(f._name)
        {}

        constexpr feature(const feature&) = default;

        constexpr feature(feature&& other) noexcept
            : _mask {other._mask}, _name {other._name}
        {
            //swap(*this, other);
        }

        feature& operator=(const feature& other) = default;

//        friend constexpr void swap(feature& one, feature& other) noexcept
//        {
//            std::swap(one._mask, other._mask);
//        }

        static constexpr feature scalar()       { return feature { 0,       "scalar" }; }
        static constexpr feature sse2()         { return feature { 1 << 1,  "sse2"   }; }
        static constexpr feature sse3()         { return feature { 1 << 2,  "sse3"   }; }
        static constexpr feature ssse3()        { return feature { 1 << 3,  "ssse3"  }; }
        static constexpr feature sse41()        { return feature { 1 << 4,  "sse41"  }; }
        static constexpr feature sse42()        { return feature { 1 << 5,  "sse42"  }; }
        static constexpr feature fma3()         { return feature { 1 << 6,  "fma3"   }; }
        static constexpr feature fma4()         { return feature { 1 << 7,  "fma4"   }; }
        static constexpr feature avx1()         { return feature { 1 << 8,  "avx1"   }; }
        static constexpr feature avx2()         { return feature { 1 << 9,  "avx2"   }; }
        static constexpr feature avx512()       { return feature { 1 << 10, "avx512" }; }
        static constexpr feature opencl()       { return feature { 1 << 11, "opencl" }; }
        static constexpr feature fpga()         { return feature { 1 << 12, "fpga"   }; }
        static constexpr feature fastfloat()    { return feature { 1 << 13, "fastfloat" }; }

//        struct scalar_t : std::integral_constant<uint64_t, 0>
//        {
//            static constexpr const char* name = "scalar";
//            static const std::string to_string() { return name; }
//        };
//
//        struct sse2_t : std::integral_constant<uint64_t, 1 << 1>
//        {
//            static constexpr const char* name = "sse2";
//            static const std::string to_string() { return name; }
//        };
//
//        struct sse3_t : std::integral_constant<uint64_t, 1 << 2>
//        {
//            static constexpr const char* name = "sse3";
//            static const std::string to_string() { return name; }
//        };
//
//        struct ssse3_t : std::integral_constant<uint64_t, 1 << 3>
//        {
//            static constexpr const char* name = "scalar";
//            static const std::string to_string() { return name; }
//        };
//
//        struct sse41_t : std::integral_constant<uint64_t, 1 << 4>
//        {
//            static constexpr const char* name = "sse4.1";
//            static const std::string to_string() { return name; }
//        };
//
//        struct sse42_t : std::integral_constant<uint64_t, 1 << 5>
//        {
//            static constexpr const char* name = "sse4.2";
//            static const std::string to_string() { return name; }
//        };
//
//        struct fma3_t : std::integral_constant<uint64_t, 1 << 6>
//        {
//            static constexpr const char* name = "fma3";
//            static const std::string to_string() { return name; }
//        };
//
//        struct fma4_t : std::integral_constant<uint64_t, 1 << 7>
//        {
//            static constexpr const char* name = "fma4";
//            static const std::string to_string() { return name; }
//        };
//
//        struct avx1_t : std::integral_constant<uint64_t, 1 << 8>
//        {
//            static constexpr const char* name = "avx1";
//            static const std::string to_string() { return name; }
//        };
//
//        struct avx2_t : std::integral_constant<uint64_t, 1 << 9>
//        {
//            static constexpr const char* name = "avx2";
//            static const std::string to_string() { return name; }
//        };
//
//        struct avx512_t : std::integral_constant<uint64_t, 1 << 10>
//        {
//            static constexpr const char* name = "avx512";
//            static const std::string to_string() { return name; }
//        };
//
//        struct opencl_t : std::integral_constant<uint64_t, 1 << 11>
//        {
//            static constexpr const char* name = "opencl";
//            static const std::string to_string() { return name; }
//        };
//
//        struct fpga_t : std::integral_constant<uint64_t, 1 << 12>
//        {
//            static constexpr const char* name = "fpga";
//            static const std::string to_string() { return name; }
//        };
//
//        struct fastfloat_t : std::integral_constant<uint64_t, 1 << 13>
//        {
//            static constexpr const char* name = "fastfloat";
//            static const std::string to_string() { return name; }
//        };

        constexpr feature& set() noexcept
        {
            _mask = ~0ul;

            return *this;
        }

        constexpr feature& set( feature feature, bool value = true ) noexcept
        {
            if(value)
                _mask |= feature.mask();
            else
                _mask &= ~feature.mask();

            return *this;
        }

        feature& set( std::initializer_list<feature> features, bool value = true ) noexcept
        {
            std::for_each(std::begin(features), std::end(features), [this, value](auto feature) {
                this->set(feature, value);
            });

            return *this;
        }

        constexpr feature& reset() noexcept
        {
            _mask = 0;

            return *this;
        }

        constexpr feature& reset( feature feature ) noexcept
        {
            set(feature, false);

            return *this;
        }

        feature& reset( std::initializer_list<feature> features ) noexcept
        {
            std::for_each(std::begin(features), std::end(features), [this](auto feature) {
                this->reset(feature);
            });

            return *this;
        }

        constexpr bool test( feature feature ) const
        {
            return (_mask & feature.mask()) != 0;
        }

        bool test( std::initializer_list<feature> features ) const
        {
            return std::accumulate(std::begin(features), std::end(features), false, [this](bool acc, auto feature) {
                return acc && this->test(feature);
            });
        }

        constexpr uint64_t mask() const
        {
            return _mask;
        }

        auto active() const
        {
            std::vector<feature> result;
            auto features = available();

            transform_if(std::begin(features), std::end(features),
                    std::back_inserter(result),
                    [](auto i) { return i; },
                    [this](auto i) { return this->test(i); });

            return result;
        }

        auto match(feature required) const
        {
            feature diff { (this->_mask ^ required._mask) & required._mask };

            return diff.active();
        }

        static constexpr std::array<feature, size> available()
        {
            return {{
                            scalar(), sse2(), sse3(),
                            ssse3(), sse41(), sse42(),
                            fma3(), fma4(), avx1(),
                            avx2(), avx512(), opencl(), fpga()
                    }};
        }

        friend std::ostream &operator<<(std::ostream &os, const feature& data) {
            using namespace std;

            for(auto feature : available())
                os << left << setw(15) << zacc::toupper(feature.to_string()) << boolcolor(data.test(feature)) << endl;

            os << endl;

            return os;
        }
    private:
        uint64_t _mask;
        const char* _name;
    };

//    struct arch
//    {
//        //const char* name;
//        feature mask;
//
//        unsigned long long value() const { return mask.mask(); }
//        std::string to_string() const { return name; }
//
//        constexpr bool is_none() const { return mask.mask() == 0 && to_string().empty(); }
//
//        static constexpr arch scalar()        { return { "scalar",         feature { feature::scalar() } }; }
//        static constexpr arch sse2()          { return { "sse.sse2",       feature { feature::sse2() } }; }
//        static constexpr arch sse3()          { return { "sse.sse3",       feature { feature::sse2(), feature::sse3(), feature::ssse3() } }; }
//        static constexpr arch sse41()         { return { "sse.sse41" ,     feature { feature::sse2(), feature::sse3(), feature::ssse3(), feature::sse41() } }; }
//        static constexpr arch sse41_fma3()    { return { "sse.sse41.fma3", feature { feature::sse2(), feature::sse3(), feature::ssse3(), feature::sse41(), feature::fma3() } }; }
//        static constexpr arch sse41_fma4()    { return { "sse.sse41.fma4", feature { feature::sse2(), feature::sse3(), feature::ssse3(), feature::sse41(), feature::fma4() } }; }
//
//        static constexpr arch avx1()          { return { "avx.avx1",       feature { feature::avx1() } }; }
//        static constexpr arch avx1_fma3()     { return { "avx.avx1.fma3",  feature { feature::avx1(), feature::fma3() } }; }
//        static constexpr arch avx2()          { return { "avx.avx2",       feature { feature::avx1(), feature::avx2(), feature::fma3() } }; }
//        static constexpr arch avx512()        { return { "avx.avx512",     feature { feature::avx1() } }; }
//
//        static constexpr arch opencl()        { return { "gpgpu.opencl",   feature { feature::opencl() } }; }
//        static constexpr arch fpga()          { return { "fpga",           feature { feature::fpga() } }; }
//    };

//    struct architectures
//    {
//        struct scalar_t       : public std::integral_constant<uint64_t, make_flag(features::SCALAR)>
//        {
//            static const std::string name() { return "scalar"; }
//        };
//
//        struct sse2_t         : public std::integral_constant<uint64_t, make_flag(features::SSE2)>
//        {
//            static const std::string name() { return "sse.sse2"; }
//        };
//
//        struct sse3_t         : public std::integral_constant<uint64_t, sse2::value | make_flag(features::SSE3, features::SSSE3)>
//        {
//            static const std::string name() { return "sse.sse3"; }
//        };
//
//        struct sse41_t        : public std::integral_constant<uint64_t, sse3::value | make_flag(features::SSE41)>
//        {
//            static const std::string name() { return "sse.sse41"; }
//        };
//
//        struct sse41_fma3_t   : public std::integral_constant<uint64_t, sse41::value | make_flag(features::FMA3)>
//        {
//            static const std::string name() { return "sse.sse41.fma3"; }
//        };
//
//        struct sse41_fma4_t   : public std::integral_constant<uint64_t, sse41::value | make_flag(features::FMA4)>
//        {
//            static const std::string name() { return "sse.sse41.fma4"; }
//        };
//
//        struct avx1_t         : public std::integral_constant<uint64_t, make_flag(features::AVX1)>
//        {
//            static const std::string name() { return "avx.avx1"; }
//        };
//
//        struct avx1_fma3_t     : public std::integral_constant<uint64_t, make_flag(features::FMA3, features::AVX1)>
//        {
//            static const std::string name() { return "avx.avx1.fma3"; }
//        };
//
//        struct avx2_t         : public std::integral_constant<uint64_t, avx1_fma3::value | make_flag(features::AVX2)>
//        {
//            static const std::string name() { return "avx.avx2"; }
//        };
//
//        struct avx512_t       : public std::integral_constant<uint64_t, make_flag(features::AVX512)>
//        {
//            static const std::string name() { return "avx.avx512"; }
//        };
//
//        struct opencl_t       : public std::integral_constant<uint64_t, make_flag(features::OPENCL)>
//        {
//            static const std::string name() { return "gpgpu.opencl"; }
//        };
//    };


//    /**
//     * @brief Provides metadata and typecasts to capabilities enum
//     */
//    class feature
//    {
//        typedef const char* c_str_t;
//
//    public:
//
//        using flag_t = std::underlying_type_t<features>;
//
//        /**
//         * @brief constructs metadata with arch and string representation
//         * @param arch arch
//         * @param str string representation
//         * @param is_set availability flag
//         */
//        constexpr feature(const features arch, const char* str, bool is_set = false)
//                : _mask(arch), _c_str(str), _is_set(is_set)
//        {}
//
//        /**
//         * @brief set the availability flag
//         * @param is_set availability flag
//         */
//        void set(bool is_set)
//        {
//            _is_set = is_set;
//        }
//
//        /**
//         * @brief returns arch's string representation
//         * @return C-string representation
//         */
//        constexpr const char* c_str() const { return _c_str; }
//
//        /**
//         * @brief implicit cast to arch's string representation
//         * @return C-string representation
//         */
//        constexpr operator const char*() const { return c_str(); };
//
//        /**
//         * @brief returns arch enum value
//         * @return arch enum value
//         */
//        constexpr features value() const { return _mask; }
//
//        /**
//         * @brief implicit cast to arch enum value
//         * @return raw arch enum value
//         */
//        constexpr operator features() const { return value(); };
//
//        /**
//         * @brief returns raw underlying value
//         * @return raw underlying value
//         */
//        constexpr flag_t mask() const { return static_cast<flag_t>(_mask); }
//
//        /**
//         * @brief implicit cast to raw underlying value
//         * @return raw underlying value
//         */
//        constexpr operator flag_t() const { return mask(); };
//
//        /**
//         * @brief implicit cast to arch's string representation
//         * @return std::string representation
//         */
//        std::string str() const { return _c_str; }
//
//        /**
//         * @brief provides bitwise-or functionality
//         * @param other other arch
//         * @return result of bitwise-or as raw underlying value
//         */
//        constexpr flag_t operator |(const feature &other) const { return mask() | other.mask(); }
//
//        /**
//         * @brief provides bitwise-and functionality
//         * @param other other arch
//         * @return result of bitwise-and as raw underlying value
//         */
//        constexpr flag_t operator &(const feature &other) const { return mask() & other.mask(); }
//
//        /**
//         * @brief returns true if this arch is available
//         * @return true if arch set, otherwise false
//         */
//        bool is_set() { return _is_set; }
//
//        /**
//         * @brief pretty-prints the current arch
//         * @param os target output stream
//         * @param cap arch object
//         * @return modified target output stream
//         */
//        friend inline std::ostream& operator<<(std::ostream& os, const feature& cap) {
//            using namespace std;
//
//            const int w = 15;
//
//            os << left << setw(w) << cap.c_str() << boolcolor(cap._is_set) << endl;
//
//            return os;
//        }
//
//
//    private:
//        const features _mask;
//        const char* _c_str;
//        bool _is_set;
//    };


    /**
     * @brief arch dispatcher. from aggregated integer representation one can extract specific features
     * @tparam arch aggregated integer representation
     */
    template<uint64_t Arch = 0>
    struct dispatcher {

        static constexpr feature features { Arch };

        /**
         * @brief checks if a particular arch is set
         * @param flag arch to check
         * @return true if arch is set
         */
        static constexpr bool is_set(feature feature) noexcept
        {
            return features.test(feature);// 0 != (flags & static_cast<flag_t>(flag));
        }

        /// current capabilities
        //static constexpr flag_t flags = arch;

        /// usually all branches provide floating types
        static constexpr bool has_floating_types = true;

        /// AVX 1 does not provide operations on integer types
        static constexpr bool has_integer_types = !is_set(feature::avx1()) || is_set(feature::avx2());

        /// fast (lower precision) float enabled?
        static constexpr bool use_fast_float = is_set(feature::fastfloat());
    };

    template<typename T>//, typename Feature>
    constexpr bool has_feature_v(feature feature) { return dispatcher<T::feature_mask>::is_set(feature); }

    template<typename T>
    constexpr bool has_integer_types_v = dispatcher<T::feature_mask>::has_integer_types;

    template<typename T>
    constexpr bool has_floating_types_v = dispatcher<T::feature_mask>::has_floating_types;

//    template <typename T, typename... TList>
//    static constexpr std::enable_if_t<std::is_same<T, features>::value, feature::flag_t>
//    make_flag(T && arch, TList &&... list) noexcept {
//        return static_cast<std::underlying_type_t<features>>(arch) | make_flag(std::forward<TList>(list)...);
//    }
//
//    template <typename T>
//    static constexpr std::enable_if_t<std::is_same<T, features>::value, feature::flag_t>
//    make_flag(T arch) noexcept {
//        return static_cast<std::underlying_type_t<features>>(arch);
//    }

    struct arch
    {
        feature mask;
        std::string name;

        arch()
            : mask {}, name {}
        {}

        template<typename T>
        arch(T)
            : mask {T::value}, name {T::name()}
        {}

        arch(const arch& other) = default;

        arch(arch&& other) noexcept
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
            std::swap(one.mask, other.mask);
            std::swap(one.name, other.name);
        }

        constexpr bool is_none() const { return mask.mask() == 0 && name.empty(); }

        friend std::ostream &operator<<(std::ostream &os, const arch& data) {
            using namespace std;

            os << data.mask;

            return os;
        }


        struct scalar       : public std::integral_constant<uint64_t, feature::scalar()>
        {
            static const std::string name() { return "scalar"; }
        };

        struct sse2         : public std::integral_constant<uint64_t, feature::sse2()>
        {
            static const std::string name() { return "sse.sse2"; }
        };

        struct sse3         : public std::integral_constant<uint64_t, feature(feature::sse2(), feature::sse3(), feature::ssse3())>
        {
            static const std::string name() { return "sse.sse3"; }
        };

        struct sse41        : public std::integral_constant<uint64_t, feature(feature::sse2(), feature::sse3(), feature::ssse3(), feature::sse41())>
        {
            static const std::string name() { return "sse.sse41"; }
        };

        struct sse41_fma3   : public std::integral_constant<uint64_t, feature(feature::sse2(), feature::sse3(), feature::ssse3(), feature::sse41(), feature::fma3())>
        {
            static const std::string name() { return "sse.sse41.fma3"; }
        };

        struct sse41_fma4   : public std::integral_constant<uint64_t, feature(feature::sse2(), feature::sse3(), feature::ssse3(), feature::sse41(), feature::fma4())>
        {
            static const std::string name() { return "sse.sse41.fma4"; }
        };

        struct avx1         : public std::integral_constant<uint64_t, feature::avx1()>
        {
            static const std::string name() { return "avx.avx1"; }
        };

        struct avx1_fma3     : public std::integral_constant<uint64_t, feature(feature::avx1(), feature::fma3())>
        {
            static const std::string name() { return "avx.avx1.fma3"; }
        };

        struct avx2         : public std::integral_constant<uint64_t, feature(feature::avx1(), feature::fma3(), feature::avx2())>
        {
            static const std::string name() { return "avx.avx2"; }
        };

        struct avx512       : public std::integral_constant<uint64_t, feature::avx512()>
        {
            static const std::string name() { return "avx.avx512"; }
        };

        struct opencl       : public std::integral_constant<uint64_t, feature::opencl()>
        {
            static const std::string name() { return "gpgpu.opencl"; }
        };
    };

}