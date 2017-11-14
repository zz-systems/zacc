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

// @file mandelbrot_engine.hpp

#include "zacc.hpp"
#include "math/complex.hpp"
#include "system/branch_entrypoint.hpp"

namespace zacc { namespace examples {

    template<typename _InitData, typename _RuntimeData, typename _OutputContainer = void, typename _InputContainer = void,
            typename = std::enable_if_t<all<iterable, _InputContainer, _OutputContainer>>>
    struct kernel : public zacc::system::entrypoint
    {
        using input_container_t     = _InputContainer;
        using output_container_t    = _OutputContainer;


        virtual void configure(_InitData data) {};



        //template<typename _Output = _OutputContainer>
        virtual void run(_OutputContainer output, _RuntimeData data) {};

        //template<typename _Input = _InputContainer>
        virtual void run(_InputContainer input, _OutputContainer output, _RuntimeData data) {};
    };
}}