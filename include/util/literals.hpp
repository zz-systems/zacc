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

#include <cstdint>

constexpr std::int8_t operator "" _int8(unsigned long long v)
{ return static_cast<std::int8_t>(v); }

constexpr std::uint8_t operator "" _uint8(unsigned long long v)
{ return static_cast<std::uint8_t>(v); }

constexpr std::int16_t operator "" _int16(unsigned long long v)
{ return static_cast<std::int16_t>(v); }

constexpr std::uint16_t operator "" _uint16(unsigned long long v)
{ return static_cast<std::uint16_t>(v); }

constexpr std::int32_t operator "" _int32(unsigned long long v)
{ return static_cast<std::int32_t>(v); }

constexpr std::uint32_t operator "" _uint32(unsigned long long v)
{ return static_cast<std::uint32_t>(v); }

constexpr std::int64_t operator "" _int64(unsigned long long v)
{ return static_cast<std::int64_t>(v); }

constexpr std::uint64_t operator "" _uint64(unsigned long long v)
{ return static_cast<std::uint64_t>(v); }

constexpr std::int_fast8_t operator "" _int_fast8(unsigned long long v)
{ return static_cast<std::int_fast8_t>(v); }

constexpr std::uint_fast8_t operator "" _uint_fast8(unsigned long long v)
{ return static_cast<std::uint_fast8_t>(v); }

constexpr std::int_fast16_t operator "" _int_fast16(unsigned long long v)
{ return static_cast<std::int_fast16_t>(v); }

constexpr std::uint_fast16_t operator "" _uint_fast16(unsigned long long v)
{ return static_cast<std::uint_fast16_t>(v); }