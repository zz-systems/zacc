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

#include <algorithm>
#include <functional>
#include <zacc/system/feature.hpp>
#include <zacc/util/type/typeid.hpp>
#include <zacc/expressions/container.hpp>
#include <zacc/expressions/arithmetic.hpp>
#include <zacc/expressions/comparisons.hpp>
#include <zacc/expressions/logical_operations.hpp>
#include <zacc/expressions/bitwise_operations.hpp>
#include <zacc/expressions/conversions.hpp>
#include <zacc/expressions/repr.hpp>
#include <zacc/expressions/evaluator.hpp>
#include <zacc/expressions/recorder.hpp>

namespace zacc { namespace expressions {

    template<typename T, size_t Size>
    struct zvec : term<zvec<T, Size>>
    {
        using value_type = T;

        static constexpr size_t size() { return Size; }

        constexpr const value_type&   operator()(size_t i) const
        {
            return _data[i];
        }

        constexpr value_type& operator()(size_t i)
        {
            return _data[i];
        }


        constexpr zvec() noexcept
        {
            recorder::current() << declare_expr<zvec>(*this);
        }

        constexpr zvec(std::initializer_list<T> init_list)
        {
            recorder::current() << declare_expr<zvec>(*this);

            std::copy(std::begin(init_list), std::end(init_list), std::begin(_data));
        }

        template<typename Expr>
        constexpr zvec(Expr expr) noexcept
        {
            auto d = declare_expr<zvec>(*this);
            auto e = assign_expr<zvec, Expr>(*this, expr);

            recorder::current() << d << e;
            evaluator::current() << d << e;
        }

        template<typename Expr>
        constexpr zvec& operator=(Expr expr) noexcept
        {
            auto e = assign_expr<zvec, Expr>(*this, expr);

            recorder::current() << e;
            evaluator::current() << e;

            return *this;
        }

        void print_data() const
        {
            std::cout << "[ ";

            for(size_t i = 0; i < size(); ++i)
            {
                std::cout << _data[i] << " ";
            }

            std::cout << "]";
        }

    private:
        alignas(T) typename container<T, Size>::type _data;
    };

    // =================================================================================================================


    // =================================================================================================================

    template<typename Left, typename Right>
    bin_expr_t<plus, lit, Left, Right>
    operator+(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<minus, lit, Left, Right>
    operator-(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<multiplies, lit, Left, Right>
    operator*(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<divides, lit, Left, Right>
    operator/(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<modulus, lit, Left, Right>
    operator%(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Right>
    un_expr_t<negate, Right>
    operator-(const Right& right)
    {
        return { right };
    }

    template<typename Right>
    un_expr_t<promote, Right>
    operator+(const Right& right)
    {
        return { right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    bin_expr_t<equal_to, lit, Left, Right>
    operator==(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<not_equal_to, lit, Left, Right>
    operator!=(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<greater, lit, Left, Right>
    operator>(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<less, lit, Left, Right>
    operator<(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<greater_equal, lit, Left, Right>
    operator>=(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<less_equal, lit, Left, Right>
    operator<=(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    bin_expr_t<logical_and, lit, Left, Right>
    operator&&(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<logical_or, lit, Left, Right>
    operator||(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Right>
    un_expr_t<logical_not, Right>
    operator!(const Right& right)
    {
        return { right };
    }

    // =================================================================================================================

    template<typename Left, typename Right>
    bin_expr_t<bit_and, lit, Left, Right>
    operator&(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<bit_or, lit, Left, Right>
    operator|(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<bit_xor, lit, Left, Right>
    operator^(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<bit_shl, lit, Left, Right>
    operator<<(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<bit_shr, lit, Left, Right>
    operator>>(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Right>
    un_expr_t<bit_not, Right>
    operator~(const Right& right)
    {
        return { right };
    }

    // =================================================================================================================

//    template<typename Left, typename Right>
//    std::enable_if_t<is_functor<Left>::value && !is_pipe<Left>::value, pipe<Left, Right>>
//    operator<<(Left left, const Right& right)
//    {
//        return { left, right };
//    }

    template<typename Left, typename Right>
    std::enable_if_t<is_pipe<Left>::value, pipe<decltype(Left::_left), pipe<decltype(Left::_right), Right>>>
    operator<<(Left left, Right right)
    {
        return { left._left, {left._right, right} };
    }

    template<typename Expr>
    std::enable_if_t<is_expr<Expr>::value, std::ostream>&
    operator<<(std::ostream& os, const Expr& expr)
    {
        auto p = evaluator::current() << [&os](auto item)
        {
            os << item << " ";
            return item;
        } << expr;

        os << "[ ";

        p();

        os << "]";
        return os;
    }
}}