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


#include "math/interpolation.hpp"
#include "util/algorithm.hpp"
#include <vector>


namespace zacc { namespace util {
	using namespace math;

	union color_rgb
	{
		uint8_t components[4];
		uint32_t integral;
		struct { uint8_t r, g, b, a; };

		color_rgb(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
			: r(r), g(g), b(b), a(a)
		{}
	};

	//ALIGN(32) union color_hsv
	//{
	//	uint8 components[4];
	//	struct { uint8 a, r, g, b; };

	//	color_hsv(uint8 r, uint8 g, uint8 b, uint8 a = 255)
	//		: r(r), g(g), b(b), a(a)
	//	{}
	//};
		
	struct gradient1D
	{
		std::vector<std::pair<const float, color_rgb>> colors;

		gradient1D() = default;

		gradient1D(std::vector<std::pair<const float, color_rgb>> init)
			: colors(std::move(init))
		{}

		gradient1D(const std::initializer_list<std::pair<const float, color_rgb>>& init)
			: colors(init)
		{}

		color_rgb getColor(const float value) const
		{
			auto v = value;//zzsystems::zacc::clamp(value, -1.01f, 1.01f);

			int index = 0;
			for (auto &iter : colors)
			{
				index++;
				if (value < iter.first)
					break;
			}

			auto i0 = vclamp<int>(index - 1, 0, (int)colors.size() - 1);
			auto i1 = vclamp<int>(index,     0, (int)colors.size() - 1);

			//auto i0 = std::max(0, std::min(index - 1, (int)colors.size() - 1));
			//auto i1 = std::max(0, std::min(index    , (int)colors.size() - 1));

			if (i0 == i1)
				return colors[i1].second;

			auto k0 = colors[i0].first;
			auto c0 = colors[i0].second;


			auto k1 = colors[i1].first;
			auto c1 = colors[i1].second;
			//auto i0 = colors.lower_bound(v);
			
			/*if (v0 == v1)
				return v1->second;*/

			/*auto k0 = i0->first;
			auto c0 = i0->second;

			if (i0 == colors.end())
				return color_rgb(0xFF, 0, 0xFF, 0xFF);
			
			i0++;

			if (i0 == colors.end())
				return c0;

			auto k1 = i0->first;
			auto c1 = i0->second;*/

			auto alpha = ((v - k0) / (k1 - k0));

			color_rgb result(
				static_cast<uint8_t>(vclamp(lerp<float>(c0.r, c1.r, alpha), 0.0f, 255.0f)),
				static_cast<uint8_t>(vclamp(lerp<float>(c0.g, c1.g, alpha), 0.0f, 255.0f)),
				static_cast<uint8_t>(vclamp(lerp<float>(c0.b, c1.b, alpha), 0.0f, 255.0f)),
				static_cast<uint8_t>(vclamp(lerp<float>(c0.a, c1.a, alpha), 0.0f, 255.0f))
			);

			return result;
		}
	};
}}
