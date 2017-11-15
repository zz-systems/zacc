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

#include <iostream>

#include "../dependencies/CImg/CImg.h"

#include "math/matrix.hpp"

#include "kernels/mandelbrot_scheme.hpp"
#include "dispatcher.hpp"
#include "util/color.hpp"
namespace zacc { namespace examples
{
    using namespace util;
        
        inline void run(const int w, const int h,
                        const std::function<std::shared_ptr<std::vector<int>>(void)>& vector_algorithm,
                        const std::function<std::shared_ptr<std::vector<int>>(void)>& scalar_algorithm,
                         const gradient1D &gradient)
        {
            using namespace std;
            using namespace chrono;


            size_t max_iterations = 1024;

            //PreFetchCacheLine()
#ifndef PROFILE
            auto sisd_t1 = high_resolution_clock::now();
            auto result2 = *scalar_algorithm();
            //vector<float> result2(512 * 512 * 1);
            auto sisd_t2 = high_resolution_clock::now();
            auto sisd_duration = duration_cast<milliseconds>(sisd_t2 - sisd_t1).count();

            cout << "Time: " << sisd_duration << "ms" << endl;
#endif
            auto simd_t1 = high_resolution_clock::now();

            auto result1 = *vector_algorithm();

            auto simd_t2 = high_resolution_clock::now();
            auto simd_duration = duration_cast<milliseconds>(simd_t2 - simd_t1).count();

            cout << "Time: " << simd_duration << "ms" << endl;
#ifndef PROFILE
            cout << "Speedup : " << (double)sisd_duration / simd_duration << endl << endl;
#endif
            cout << "Minval SIMD: " << *min_element(begin(result1), end(result1)) << endl << endl;
            cout << "Maxval SIMD: " << *max_element(begin(result1), end(result1)) << endl << endl;

#ifndef PROFILE
            cout << "Minval SISD: " << *min_element(begin(result2), end(result2)) << endl << endl;
            cout << "Maxval SISD: " << *max_element(begin(result2), end(result2)) << endl << endl;

#ifndef CACOPHONY_EXAMPLES_HEADLESS
            cimg_library::CImg<uint8_t> img1(w, h, 1, 3), img2(w, h, 1, 3);

            //async::parallel_for(async::irange(0, w * h), [&](const auto i)
#pragma omp parallel for
            for (int i = 0; i < w * h; i++)
            {
                vec2<int> pos = math::reshape_i_xy<vec2<int>>(i, w);

                int x = pos.x, y = pos.y;
                auto color1 = gradient.getColor(result1[i]);

                img1(x, y, 0) = color1.r;
                img1(x, y, 1) = color1.g;
                img1(x, y, 2) = color1.b;

                auto color2 = gradient.getColor(result2[i]);

                img2(x, y, 0) = color2.r;
                img2(x, y, 1) = color2.g;
                img2(x, y, 2) = color2.b;
            }
            //);

            img1.display("simd", true);
            img2.display("sisd", true);
#endif

#endif

        }

        /*template<>
        struct kernel_traits<mandelbrot>
        {
            using output_container_t = std::vector<int>;
            using input_container_t  = std::vector<int>;

            static constexpr auto kernel_name() { return "mandelbrot"; }
        };*/

        void run()
        {
            auto sysinfo = &zacc::platform::instance();
            std::cout << *sysinfo;

            //platform e;

            //e.info.feature_flags = CAPABILITY_NONE;
            //sysinfo.setFlag(CAPABILITY_AVX2, false);
            //sysinfo.setFlag(CAPABILITY_AVX1, false);
            //e.info.setFlag(CAPABILITY_SSE42, false);
            //e.info.setFlag(CAPABILITY_SSE41, false);
            //e.info.setFlag(CAPABILITY_FMA3, false);
            //e.info.setFlag(CAPABILITY_FMA4, false);

            // Restrict with extracted bitmask
            auto flags = sysinfo->raw();
            //sysinfo->set(capabilities::AVX2, false);
            //sysinfo->set(capabilities::AVX1, false);
            //sysinfo->set(capabilities::SCALAR, false);


            std::cout << *sysinfo;



            auto mandelbrot_dispatcher = make_dispatcher<mandelbrot>();

            vec2<int>   dim  = {2048, 2048};
            vec2<float> cmin = {-2, -2};
            vec2<float> cmax = {2, 2};
            size_t max_iterations = 1024;

            mandelbrot_dispatcher.dispatch_some(dim, cmin, cmax, max_iterations);


            auto f1 = [&]()
            {
                auto t = zacc::make_shared<std::vector<int>>(dim.x * dim.y);

                sysinfo->reload();
                //sysinfo->set(capabilities::AVX2, false);
                //sysinfo->set(capabilities::AVX1, false);
                //sysinfo->set(capabilities::FMA3, false);

                mandelbrot_dispatcher.dispatch_one(*t);

                return t;
            };

            auto f2 = [&]()
            {
                auto t = zacc::make_shared<std::vector<int>>(dim.x * dim.y);

                sysinfo->set(0);

                mandelbrot_dispatcher.dispatch_one(*t);

                return t;
            };

            gradient1D grad
                    {
                            { -1, color_rgb(0, 0, 0 ) },
                            { 0, color_rgb(66, 30, 15 ) },
                            { 1, color_rgb(25, 7, 26 ) },
                            { 2, color_rgb(9, 1, 47 ) },
                            { 3, color_rgb(4, 4, 73 ) },
                            { 4, color_rgb(0, 7, 100 ) },
                            { 5, color_rgb(12, 44, 138 ) },
                            { 6, color_rgb(24, 82, 177 ) },
                            { 7, color_rgb(57, 125, 209 ) },
                            { 8, color_rgb(134, 181, 229 ) },
                            { 9, color_rgb(211, 236, 248 ) },
                            { 10, color_rgb(241, 233, 191 ) },
                            { 11, color_rgb(248, 201, 95 ) },
                            { 12, color_rgb(255, 170, 0 ) },
                            { 13, color_rgb(204, 128, 0 ) },
                            { 14, color_rgb(153, 87, 0 ) },
                            { 15, color_rgb(106, 52, 3 ) }
                    };



            run(dim.x, dim.y, f1, f2, grad);
        }
    }}

int main(int argc, char** argv)
{
    zacc::examples::run();

    return 0;
}
