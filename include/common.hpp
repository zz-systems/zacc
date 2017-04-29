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

#include <x86intrin.h>


#if defined(__clang__)
#elif defined(__GNUC__) || defined(__GNUG__)
inline __m256 _mm256_set_m128(__m128 hi, __m128 lo)
{
    return _mm256_insertf128_ps(_mm256_castps128_ps256(hi),(lo),1);
}
#elif defined(_MSC_VER)
#endif

#ifdef _MSC_VER
#else
    inline bool _mm256_test_all_ones(__m256 val)
    {
        auto ival = _mm256_castps_si256(val);
        return _mm256_testc_si256(ival, _mm256_cmpeq_epi32(ival,ival));
    }

    inline bool _mm256_test_all_ones(__m256i val)
    {
        return _mm256_testc_si256(val, _mm256_cmpeq_epi32(val,val));
    }
#endif


template<typename T>
std::enable_if_t<!zacc::is_zval<T>::value, bool> is_set(T value)
{
    return value != 0;
};

/**
 * @brief shortcut to write forwarding constructors
 * @param name current type (constructor)
 * @param base base type (constructor)
 */
#define FORWARD2(name, base) \
    /** \
     * @brief forwarding constructor \
     */ \
    template<typename ...Args> \
    name(Args&&... args) : base(std::forward<Args>(args)...) {}


/**
 * @brief shortcut to write forwarding constructors with default base name 'base_t'
 * @param name current type (constructor)
 */
#define FORWARD(name) FORWARD2(name, base_t)

/**
 * @brief shortcut for trait definition. Aggregated from base traits and provided traits
 * @param provides which trait is set
 * @param base_t base type
 */
#define TRAIT2(provides, base_t) \
    static const long long traits =  base_t::traits | static_cast<long long>(provides)

/**
 * @brief shortcut for trait definition. Aggregated from base traits and provided traits. 'base_t' as default base type
 * @param provides which trait is set
 */
#define TRAIT(provides) //\
    //TRAIT2(provides, base_t)

#define REQUIRE(requirement) //\
    //static_assert((base_t::traits & static_cast<long long>(requirement)) != 0, "Requirement not met: feature '" #requirement "' required.")

//#define BASE() \
//    base_t* base() { return static_cast<base_t*>(this); }

/**
 * @brief provides converting binary operators, where one argument is of another type and has to be casted appropriately.
 * @param op operator
 * @param composed_t final composed type
 */
#define CONVERSION2(op, composed_t) \
    /** \
    * @brief converting op operator \
    */ \
    template<typename other_t> \
    friend composed_t operator op(const composed_t one, const enable_if_not_same<other_t, composed_t> other) { \
        return one op static_cast<composed_t>(other); \
    }; \
    /** \
    * @brief converting op operator \
    */ \
    template<typename other_t> \
    friend composed_t operator op (const enable_if_not_same<other_t, composed_t> one, const composed_t other) { \
        return static_cast<composed_t>(one) op other; \
    }

/**
 * @brief provides converting binary operators, where one argument is of another type and has to be casted appropriately.
 * 'composed_t' used as default final composed type
 * @param op operator
 */
#define CONVERSION(op) CONVERSION2(op, composed_t)

/**
 * @brief provides assignment operators in form of +=, <<=, etc...
 * @param op operator
 * @param composed_t final composed type
 */
#define ASSIGNMENT2(op, composed_t) \
    /** \
    * @brief merged op - assignment operator \
    */ \
    friend composed_t &operator op##=(composed_t &one, const composed_t other) { \
        return one = one op other; \
    }

/**
 * @brief provides assignment operators in form of +=, <<=, etc...
 * 'composed_t' used as default final composed type
 * @param op operator
 */
#define ASSIGNMENT(op) ASSIGNMENT2(op, composed_t)


#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)