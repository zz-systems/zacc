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

// @file perlin_engine.hpp

#include "zacc.hpp"

DISPATCHED class perlin_engine
{
    void run(const vec3<float> &origin, float *target)
    {
        const size_t real_size = 1024; // length of target

        const int octaves = 5;
        const int seed = 1337;
        const double frequency = 1.0;
        const float lacunarity = 1.0;
        const float persistence = 0.5;

        int cur_octave = 0;

        zfloat value = 0, currentPersistence = 1;

        // Generate values
        zacc::generate<zfloat>(target, target + real_size, [this](auto i)
        {
            zfloat	value = 0,
                    currentPersistence = 1;

            vec3<zfloat> origin { i, i, i };

            auto _coords = origin / real_size * frequency;

            for (int curOctave = 0; cur_octave < octaves; cur_octave++)
            {
                value += currentPersistence * noisegen<branch>::gradient_coherent_3d(
                        clamp_int32<zfloat>(_coords),
                        seed + cur_octave,
                        quality);

                // Prepare the next octave.
                _coords *= lacunarity;
                currentPersistence *= persistence;
            }
            return value;
        });
    }
}