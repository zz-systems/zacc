//
// Vectorized and parallelized version of libnoise using the gorynych SIMD toolkit
// Copyright (C) 2015-2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
//
// Original libnoise:
// Copyright (C) 2003, 2004 Jason Bevins
// The developer's email is jlbezigvins@gmzigail.com (for great email, take
// off every 'zig'.)
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License (COPYING.txt) for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#pragma once

#include "../macros.h"
#include "dispatch.h"
#include "../math/matrix.h"

namespace zzsystems { namespace gorynych { namespace platform {

    DISPATCHED class ALIGNED scheduler_base
    {
        using vreal = typename static_dispatcher<capability>::vreal;
        using vint  = typename static_dispatcher<capability>::vint;

    public:
        virtual void schedule(float *target, const vec3<float> &origin)     /*const*/ = 0;
        virtual float* operator()(const vec3<float> &origin)                /*const*/ = 0;
        virtual void operator()(float *target, const vec3<float> &origin)   /*const*/
        {
            schedule(target, origin);
        }

    protected:

        inline vec3<_float4> build_coords(const _float4 & x, const _float4 & y, const _float4 & z)
        {
            return vec3<_float4>(
                    x + _float4(0, 1, 2, 3),
                    y,
                    z
            );
        }


        inline vec3<_float8> build_coords(const _float8 &x, const _float8 &y, const _float8 &z)
        {
            return vec3<_float8>(
                    x + _float8(0, 1, 2, 3, 4, 5, 6, 7),
                    y,
                    z
            );
        }

        inline vec3<float> build_coords(float x, float y, float z)
        {
            return vec3<float> {
                    x,
                    y,
                    z
            };
        }

        inline void stream_result(float* stride, size_t x, const float r)
        {
            stride[x] = r;
        }

        inline void store_result(float* stride, size_t x, const float r)
        {
            stride[x] = r;
        }

        inline void stream_result(float* stride, size_t x, const _float4 &r)
        {
            _mm_stream_ps(stride + x, r.val);
        }

        inline void store_result(float* stride, size_t x, const _float4 &r)
        {
            _mm_storeu_ps(stride + x, r.val);
        }

        inline void stream_result(float* stride, size_t x, const _float8 &r)
        {
            //_mm256_stream_ps(stride + x, r.val);
            _mm256_storeu_ps(stride + x, r.val);
        }

        inline void store_result(float* stride, size_t x, const _float8 &r)
        {
            _mm256_storeu_ps(stride + x, r.val);
        }

        void write_result(const vec3<int> &dimensions, float *stride, size_t remainder, size_t x, const vreal &result)
        {
            if (remainder == 0) // All rows aligned on required boundaries -> stream
            {
                stream_result(stride, x, result);
            }
            else if (x < (dimensions.x - remainder)) // Not aligned - but still in the "good" range
            {
                store_result(stride, x, result);
            }
            else // Fill remaining columns
            {
                float extracted[dim<vreal>()];
                extract(result, extracted);

                for (size_t i = 0; i < remainder; i++)
                    stride[x + i] = extracted[i];
            }
        }
    };
}}}