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
#include <functional>
#include <algorithm>

namespace zacc {

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

    struct feature
    {
        static constexpr size_t size = 13;

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
        }

        feature& operator=(const feature& other) = default;

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
}