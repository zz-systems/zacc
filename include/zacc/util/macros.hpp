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
#include <utility>

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
    constexpr name(Args&&... args) : base(std::forward<Args>(args)...) {}


/**
 * @brief shortcut to write forwarding constructors with default base name 'Base'
 * @param name current type (constructor)
 */
#define FORWARD(name) FORWARD2(name, Base)

/**
 * @brief shortcut for trait definition. Aggregated from base traits and provided traits
 * @param provides which trait is set
 * @param Base base type
 */
#define TRAIT2(provides, Base) \
    static const long long traits =  Base::traits | static_cast<long long>(provides)

/**
 * @brief shortcut for trait definition. Aggregated from base traits and provided traits. 'Base' as default base type
 * @param provides which trait is set
 */
#define TRAIT(provides) //\
    //TRAIT2(provides, Base)

#define REQUIRE(requirement) //\
    //static_assert((Base::traits & static_cast<long long>(requirement)) != 0, "Requirement not met: feature '" #requirement "' required.")

//#define BASE() \
//    Base* base() { return static_cast<Base*>(this); }

///**
// * @brief provides converting binary operators, where one argument is of another type and has to be casted appropriately.
// * @param op operator
// * @param Composed final composed type
// */
//#define CONVERSION2(op, Composed) \
//    /** \
//    * @brief converting op operator \
//    */ \
//    template<typename other_t> \
//    friend Composed operator op(const Composed one, const enable_if_not_same<other_t, Composed> other) { \
//        return one op static_cast<Composed>(other); \
//    }; \
//    /** \
//    * @brief converting op operator \
//    */ \
//    template<typename other_t> \
//    friend Composed operator op (const enable_if_not_same<other_t, Composed> one, const Composed other) { \
//        return static_cast<Composed>(one) op other; \
//    }
//
///**
// * @brief provides converting binary operators, where one argument is of another type and has to be casted appropriately.
// * 'Composed' used as default final composed type
// * @param op operator
// */
//#define CONVERSION(op) CONVERSION2(op, Composed)
//
///**
// * @brief provides assignment operators in form of +=, <<=, etc...
// * @param op operator
// * @param Composed final composed type
// */
//#define ASSIGNMENT2(op, Composed) \
//    /** \
//    * @brief merged op - assignment operator \
//    */ \
//    friend Composed &operator op##=(Composed &one, const Composed other) { \
//        return one = one op other; \
//    }

/**
 * @brief provides assignment operators in form of +=, <<=, etc...
 * 'Composed' used as default final composed type
 * @param op operator
 */
#define ASSIGNMENT(op) ASSIGNMENT2(op, Composed)


#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)

#define TYPES typename arch, \
    typename zint8      = typename arch::zint8, \
    typename zint16     = typename arch::zint16, \
    typename zint32     = typename arch::zint32, \
    typename zfloat32   = typename arch::zfloat32, \
    typename zfloat64   = typename arch::zfloat64, \
    typename zbyte      = typename arch::zint8, \
    typename zshort     = typename arch::zint16, \
    typename zint       = typename arch::zint32, \
    typename zfloat     = typename arch::zfloat32, \
    typename zdouble    = typename arch::zfloat64, \
    typename bint8      = typename arch::bint8, \
    typename bint16     = typename arch::bint16, \
    typename bint32     = typename arch::bint32, \
    typename bfloat32   = typename arch::bfloat32, \
    typename bfloat64   = typename arch::bfloat64, \
    typename bbyte      = typename arch::bint8, \
    typename bshort     = typename arch::bint16, \
    typename bint       = typename arch::bint32, \
    typename bfloat     = typename arch::bfloat32, \
    typename bdouble    = typename arch::bfloat64

#define TYPES2 typename arch, \
    typename zint8, \
    typename zint16, \
    typename zint32, \
    typename zfloat32, \
    typename zfloat64, \
    typename zbyte, \
    typename zshort, \
    typename zint, \
    typename zfloat, \
    typename zdouble, \
    typename bint8, \
    typename bint16, \
    typename bint32, \
    typename bfloat32, \
    typename bfloat64, \
    typename bbyte, \
    typename bshort6, \
    typename bint, \
    typename bfloat, \
    typename bdouble

//clash with POSIX....
//#define KERNEL template<typename _Input, typename _Output, TYPES>

/**
 * @brief compile- and runtime type dispatching
 */
#define DISPATCHED template<TYPES>

#define ALIGNED alignas(arch::alignment)