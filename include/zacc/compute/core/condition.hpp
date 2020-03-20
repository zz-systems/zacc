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
    class condition;

    template<typename>
    class when;

    template<typename, typename>
    class then;

    template<>
    class condition<>
    {
    protected:
        constexpr condition() = default;
    };

    template<typename When, typename Then, typename Else>
    class condition<When, Then, Else>
        : public condition<>
        , public term<condition<When, Then, Else>>
    {
    public:
        using operator_type = select_op<>;
        using operands_type = std::tuple<When, Then, Else>;

        constexpr explicit condition(When when, Then then, Else e)
            : _when { (when) }
            , _then { (then) }
            , _else { (e) }
        {}

        constexpr auto operator()() const
        {
            return select_op{}(eval(_when), eval(_then), eval(_else));
        };

        constexpr auto operands()
        {
            return std::make_tuple(_when, _then, _else);
        }

        constexpr auto when() const
        {
            return _when;
        }

        constexpr auto is_true() const
        {
            return _then;
        }

        constexpr auto is_false() const
        {
            return _else;
        }

    private:
        When _when;
        Then _then;
        Else _else;
    };

    template<typename When, typename Then>
    class _is_true
    {
    public:
        constexpr _is_true(When when, Then then) noexcept
            : _when(when)
              , _then(then)
        {}

        template<typename Else>
        constexpr auto otherwise(Else other)
        {
            return make_expression<select_op<>>(_when, _then, other);
        }
    private:

        When _when;
        Then _then;
    };


    template<typename When>
    class when
    {

//        template<typename Then>
//        class _is_false
//        {
//        public:
//            constexpr _is_false(When&& when, Then&& then) noexcept
//                : _when(std::forward<When>(when))
//                , _then(std::forward<Then>(then))
//            {}
//        private:
//
//            When _when;
//            Then _then;
//        };

    public:
        constexpr explicit when(When when) noexcept
            : _when(when)
        {}

        template<typename Then>
        constexpr auto then(Then then)
        {
            return _is_true(_when, then);
        }
    private:
        When _when;
    };
}