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

#include<chrono>

#include "../../dependencies/CImg/CImg.h"

#include "system/kernel_dispatcher.hpp"
#include "math/matrix.hpp"
#include "util/color.hpp"

namespace zacc { namespace examples {

    template<typename _KernelInterface>
    class host
    {
        using input_container     = typename system::kernel_traits<_KernelInterface>::input_container;
        using output_container    = typename system::kernel_traits<_KernelInterface>::output_container;

        using kernel_result_t       = std::tuple<std::shared_ptr<output_container>, std::chrono::milliseconds>;

    public:
        host(math::vec2<int> dim)
                : _dim(dim)
        {
        }

        virtual ~host() {}

        virtual void run()
        {
            platform::global().set(0);

            this->configure_kernel();
            auto reference  = this->run_kernel();

            platform::global().reload().set(capabilities::AVX2, true).set(capabilities::FMA3, true);

            this->configure_kernel();
            auto vectorized = this->run_kernel();

            display(reference, vectorized);
        }

        virtual void display(kernel_result_t reference, kernel_result_t vectorized)
        {
            using namespace math;
            using namespace std;

            auto reference_result   = *get<0>(reference);
            auto vectorized_result  = *get<0>(vectorized);

            auto reference_duration  = get<1>(reference).count();
            auto vectorized_duration = get<1>(vectorized).count();



            cout << endl << string(43, '-') << endl;
            cout << setw(15) << "" << setw(10) << "Time (ms)"  << setw(10) << "Min" << setw(10) << "Max" << endl;
            cout << string(43, '-') << endl;
            cout << setw(15) << "Vectorized" << setw(10) << vectorized_duration << setw(10) << *min_element(begin(vectorized_result), end(vectorized_result)) << setw(10) << *max_element(begin(vectorized_result), end(vectorized_result)) << endl;
            cout << setw(15) << "Reference" << setw(10) << reference_duration << setw(10) << *min_element(begin(reference_result), end(reference_result)) << setw(10) << *max_element(begin(reference_result), end(reference_result)) << endl;
            cout << string(43, '-') << endl;
            cout << setw(15) << "Speedup " << setw(10) << (double)reference_duration / vectorized_duration << endl << endl;

            cimg_library::CImg<uint8_t>
                    img1(_dim.x, _dim.y, 1, 3),
                    img2(_dim.x, _dim.y, 1, 3);

            for (int i = 0; i < _dim.x * _dim.y; i++)
            {
                int x, y;

                std::tie(x, y) = math::reshape<std::tuple<int, int>>(i, _dim);

                auto color1 = this->map_value(vectorized_result[i]);

                img1(x, y, 0) = color1.r;
                img1(x, y, 1) = color1.g;
                img1(x, y, 2) = color1.b;

                auto color2 = this->map_value(reference_result[i]);

                img2(x, y, 0) = color2.r;
                img2(x, y, 1) = color2.g;
                img2(x, y, 2) = color2.b;
            }

            img1.display("simd", true);
            img2.display("sisd", true);
        }
    protected:

        virtual kernel_result_t run_kernel()
        {
            using namespace std::chrono;

            std::cout << platform::global() << std::endl;

            auto start = high_resolution_clock::now();
            auto result = this->run_kernel(input_container{});
            auto end = high_resolution_clock::now();

            auto duration = duration_cast<milliseconds>(end - start);

            return {result, duration};
        }


        virtual void configure_kernel() = 0;
        virtual std::shared_ptr<output_container> run_kernel(input_container input) = 0;
        virtual util::color_rgb map_value(typename output_container::value_type value) = 0;

        math::vec2<int> _dim;
        system::runtime_dispatcher<system::kernel_dispatcher<_KernelInterface>> _dispatcher;
    };

}}