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

namespace zacc::compute
{
    template<typename...>
    class func;

    template<>
    class func<>
        : public tracking<func<>>
    {};

    template<typename... Statements>
    class func
        : public func<>
        , public term<func<Statements...>>
    {
    public:
        using operator_type = call_op<>;
        using operands_type = std::tuple<Statements...>;

        constexpr explicit func(Statements ...statements) noexcept
            : func<>::func()
              , _statements { statements... }
        {}

        constexpr explicit func(Statements&& ...statements) noexcept
            : func<>::func()
            , _statements { std::forward<Statements>(statements)... }
        {}

        constexpr auto statements()
        {
            return _statements;
        }

        template<auto I>
        constexpr auto statement()
        {
            return std::get<I>(_statements);
        }

    private:
        operands_type _statements;
    };
}