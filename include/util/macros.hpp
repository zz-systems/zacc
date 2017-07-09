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

/**
 * @brief compile- and runtime type dispatching
 */
#define DISPATCHED template<typename branch, \
    typename zint8      = typename branch::zint8, \
    typename zint16     = typename branch::zint16, \
    typename zint32     = typename branch::zint32, \
    typename zfloat32   = typename branch::zfloat32, \
    typename zfloat64   = typename branch::zfloat64, \
    typename zbyte      = typename branch::zint8, \
    typename zshort     = typename branch::zint16, \
    typename zint       = typename branch::zint32, \
    typename zfloat     = typename branch::zfloat32, \
    typename zdouble    = typename branch::zfloat64, \
    typename bint8      = typename branch::bint8, \
    typename bint16     = typename branch::bint16, \
    typename bint32     = typename branch::bint32, \
    typename bfloat32   = typename branch::bfloat32, \
    typename bfloat64   = typename branch::bfloat64, \
    typename bbyte      = typename branch::bint8, \
    typename bshort     = typename branch::bint16, \
    typename bint       = typename branch::bint32, \
    typename bfloat     = typename branch::bfloat32, \
    typename bdouble    = typename branch::bfloat64>

#define ALIGNED alignas(branch::alignment)
