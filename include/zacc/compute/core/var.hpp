//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2019 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

#include <variant>

namespace zacc::compute
{
    template<typename...>
    class expression;

    template<typename = void>
    class var;

    template<>
    class var<>
        : public tracking<var<>>
    {};

    template<typename T>
    class var
        : public var<>
        , public term<var<T>>
    {
    public:
        using value_type = T;
        using var<>::var;

        constexpr explicit var(T&& value) noexcept
            : var<>::var()
            , _initializer { make_expression<init_op<>>(std::ref(*this), std::forward<T>(value)) }
            , _assignment {}
        {}

//        template<typename Fn, std::enable_if_t<std::is_base_of_v<expression<>, std::decay_t<Fn>>, void**> = nullptr>
//        constexpr var(Fn&& value) noexcept
//            : var<>::var()
//            , _initializer { make_expression<init_op<>>(std::ref(*this), std::forward<T>(value)) }
//            , _assignment {}
//        {}

        constexpr var& operator=(T&& value) noexcept
        {
            _assignment = make_expression<assign_op<>>(std::ref(*this), std::forward<T>(value));

            return *this;
        }

//        template<typename Fn, std::enable_if_t<std::is_base_of_v<expression<>, std::decay_t<Fn>>, void**> = nullptr>
//        constexpr var& operator=(Fn&& value) noexcept
//        {
//            _assignment = make_expression<assign_op<>>(*this, std::forward<Fn>(value));
//
//            return *this;
//        }

        constexpr auto initializer() const
        {
            return _initializer;
        }

        constexpr auto get_assignment() const
        {
            return _assignment;
        }

    private:

        expression<init_op<>, std::reference_wrapper<var>, value_type> _initializer;
        std::optional<expression<assign_op<>, std::reference_wrapper<var>, value_type>> _assignment;
    };
}