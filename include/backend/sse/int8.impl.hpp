//---------------------------------------------------------------------------------
//
//  This is an autogenerated file. Do not edit!
//
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
#include <type_traits>

#include "util/type_composition.hpp"

#include "zval.hpp"
#include "common.hpp"
#include "type_traits.hpp"

#include "traits/common.hpp"
#include "traits/construction.hpp"
#include "traits/io.hpp"
#include "traits/arithmetic.hpp"
#include "traits/bitwise.hpp"
#include "traits/logical.hpp"
#include "traits/comparison.hpp"
#include "traits/conditional.hpp"

/**
 * @brief int8 implementation for the sse branch
 * provides unified access to 16 'char' values
 */

namespace zacc { namespace sse {

    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates int8
     * @remark sse
     */
    template<typename composed_t>
    struct int8_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates int8
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {


            /**
             * @brief construction default branch
             * @relates int8
             * @remark sse - default
             */
            __impl(__m128i value) : base_t(value) {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "CONS(__m128i value)");

            }


            /**
             * @brief construction default branch
             * @relates int8
             * @remark sse - default
             */
            __impl(char value) : base_t(_mm_set1_epi8(value)) {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "CONS(char value)");

            }


            /**
             * @brief construction default branch
             * @relates int8
             * @remark sse - default
             */
            __impl(char *value) : base_t(_mm_load_si128((__m128i*)value)) {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "CONS(char *value)");

            }


            /**
             * @brief construction default branch
             * @relates int8
             * @remark sse - default
             */
            __impl(char arg15, char arg14, char arg13, char arg12, char arg11, char arg10, char arg9, char arg8, char arg7, char arg6, char arg5, char arg4, char arg3, char arg2, char arg1, char arg0) : base_t(_mm_set_epi8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15)) {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "CONS(char arg15, char arg14, char arg..)");

            }

        };

        /**
         * @brief construction public interface implementation
         * @relates int8
         * @remark sse
         */
        template<typename base_t>
        using impl = interface::construction<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name io operations
     */
    ///@{

    /**
     * @brief io
     * @relates int8
     * @remark sse
     */
    template<typename composed_t>
    struct int8_io
    {

        /**
         * @brief io basic interface implementation
         * @relates int8
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates int8
             * @remark sse - default
             */
            void io_store(typename base_t::extracted_t &target) const noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "store");

                _mm_store_si128((__m128i*)target.data(), base_t::_value);
            }


            /**
             * @brief io default branch
             * @relates int8
             * @remark sse - default
             */
            void io_stream(typename base_t::extracted_t &target) const noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "stream");

                _mm_stream_si128((__m128i*)target.data(), base_t::_value);
            }

        };

        /**
         * @brief io public interface implementation
         * @relates int8
         * @remark sse
         */
        template<typename base_t>
        using impl = interface::io<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name arithmetic operations
     */
    ///@{

    /**
     * @brief arithmetic
     * @relates int8
     * @remark sse
     */
    template<typename composed_t>
    struct int8_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates int8
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t arithmetic_negate(composed_t one)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "negate");

                return _mm_sub_epi8(_mm_setzero_si128(), one.get_value());
            }


            /**
             * @brief arithmetic default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t arithmetic_add(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "add");

                return _mm_add_epi8(one.get_value(), other.get_value());
            }


            /**
             * @brief arithmetic default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t arithmetic_sub(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "sub");

                return _mm_sub_epi8(one.get_value(), other.get_value());
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates int8
         * @remark sse
         */
        template<typename base_t>
        using impl = interface::arithmetic<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name bitwise operations
     */
    ///@{

    /**
     * @brief bitwise
     * @relates int8
     * @remark sse
     */
    template<typename composed_t>
    struct int8_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates int8
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t bitwise_negate(composed_t one)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "negate");

                __m128i junk;
                auto ones = _mm_cmpeq_epi8(junk, junk);
                return _mm_xor_si128(one.get_value(), ones);
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t bitwise_or(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "or");

                return _mm_or_si128(one.get_value(), other.get_value());
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t bitwise_and(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "and");

                return _mm_and_si128(one.get_value(), other.get_value());
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t bitwise_xor(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "xor");

                return _mm_xor_si128(one.get_value(), other.get_value());
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates int8
         * @remark sse
         */
        template<typename base_t>
        using impl = interface::bitwise<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name logical operations
     */
    ///@{

    /**
     * @brief logical
     * @relates int8
     * @remark sse
     */
    template<typename composed_t>
    struct int8_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates int8
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief logical default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t logical_negate(composed_t one)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "negate");

                return _mm_cmpeq_epi8(one.get_value(), _mm_setzero_si128());
            }


            /**
             * @brief logical default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t logical_or(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "or");

                return _mm_or_si128(one.get_value(), other.get_value());
            }


            /**
             * @brief logical default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t logical_and(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "and");

                return _mm_and_si128(one.get_value(), other.get_value());
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates int8
         * @remark sse
         */
        template<typename base_t>
        using impl = interface::logical<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name comparison operations
     */
    ///@{

    /**
     * @brief comparison
     * @relates int8
     * @remark sse
     */
    template<typename composed_t>
    struct int8_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates int8
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t comparison_eq(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "eq");

                return _mm_cmpeq_epi8(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t comparison_neq(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "neq");

                return !(one == other);
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t comparison_gt(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "gt");

                return _mm_cmpgt_epi8(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t comparison_lt(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "lt");

                return _mm_cmplt_epi8(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t comparison_ge(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "ge");

                return !(one < other);
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t comparison_le(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "le");

                return !(one > other);
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates int8
         * @remark sse
         */
        template<typename base_t>
        using impl = interface::comparison<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name conditional operations
     */
    ///@{

    /**
     * @brief conditional
     * @relates int8
     * @remark sse
     */
    template<typename composed_t>
    struct int8_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates int8
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates int8
             * @remark sse - default
             */
            friend composed_t vsel(composed_t condition, composed_t if_value, composed_t else_value)  noexcept {

                ZTRACE(std::left << std::setw(24) << "sse.int8.impl line " STRINGIZE(__LINE__) ":" << " zint8(char[16]) " << std::left << std::setw(10) << "default" << "vsel");

                return _mm_or_si128(_mm_andnot_si128(condition.get_value(), else_value.get_value()), _mm_and_si128(condition.get_value(), if_value.get_value()));
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates int8
         * @remark sse
         */
        template<typename base_t>
        using impl = interface::conditional<__impl<base_t>, composed_t>;
    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name int8 composition
     */
    ///@{

    /**
     * @brief zval parametrization using
     * - '__m128i' as underlying vector type
     * - 'char' as scalar type
     * - '16' as vector size
     * - '16' as alignment
     * @relates int8
     * @remark sse
     */
    template<uint64_t capability>
    struct __zval_int8
    {
        using zval_t = zval<__m128i, char, 16, 16, capability>;

        struct impl : public zval_t
        {
            FORWARD2(impl, zval_t);
        };
    };
    /**
     * @brief zval composition
     * @relates int8
     * @remark sse
     */
    template<uint64_t capability>
    struct __zint8
    {
        struct impl;

        using zval_t = typename __zval_int8<capability>::impl;
        using composition_t = compose
        <
            printable::impl,
            iteratable::impl,
            convertable::impl,
            int8_io<impl>::template impl,
            int8_arithmetic<impl>::template impl,
            int8_bitwise<impl>::template impl,
            int8_logical<impl>::template impl,
            int8_comparison<impl>::template impl,
            int8_conditional<impl>::template impl,
            int8_construction<impl>::template impl,

            composable<zval_t>::template type
        >;

        struct impl : public composition_t
        {
            FORWARD2(impl, composition_t);
        };
    };

    template<uint64_t capability = 0xFFFF'FFFF'FFFF'FFFF>
    using zint8 = typename __zint8<capability>::impl;

    ///@}
}}