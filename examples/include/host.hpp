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

#include "system/sysinfo.hpp"
#include "system/kernel_dispatcher.hpp"
#include "math/matrix.hpp"
#include "util/color.hpp"

namespace zacc { namespace examples {

    template<typename Kernel, typename... ReferenceKernels>
    class host
    {
        using input_container     = typename system::kernel_traits<Kernel>::input_container;
        using output_container    = typename system::kernel_traits<Kernel>::output_container;

        using kernel_result_t       = std::tuple<std::shared_ptr<output_container>, std::chrono::milliseconds>;
    public:
        struct result
        {
            std::string kernel_name;
            output_container data;
            std::chrono::milliseconds duration;
            arch selected_arch;
        };


        struct stat
        {
            std::string title;
            typename output_container::value_type min_element, max_element;
            std::chrono::milliseconds duration;
            arch selected_arch;

            stat(const std::string& title, const result& result)
                : title(title + result.kernel_name),
                min_element(*std::min_element(std::begin(result.data), std::end(result.data))),
                max_element(*std::max_element(std::begin(result.data), std::end(result.data))),
                duration(result.duration),
                selected_arch(result.selected_arch)
            {}

            friend std::ostream& operator<<(std::ostream& os, const stat& data)
            {
                using namespace std;
                os  << setw(30) << data.title << setw(15) << data.selected_arch.name << setw(10) << data.duration.count()
                    << setw(15) << data.min_element << setw(15) << data.max_element;

                return os;
            }
        };

        host(const sysinfo& sysinfo, math::vec2<int> dim)
                : _dim(dim), _sysinfo(sysinfo)
        {}

        virtual ~host() {}

        virtual void run()
        {
            this->configure();

            _main_dispatcher.features().reset();
            auto scalar  = this->execute(_main_dispatcher);

            _main_dispatcher.features() = _sysinfo;
            auto simd = this->execute(_main_dispatcher);

            std::vector<result> results;
            std::vector<stat> stats;

            zacc::for_each(_reference_dispatchers, [&results, &stats, this](auto& d){
                auto r = this->execute(d);
                results.push_back(r);
                stats.push_back(stat("REF: ", r));

                //display_image("REF: " + r.kernel_name, r);
            });

            display_stat(stat("SISD: ", scalar), stat("SIMD: ", simd), stats);


            display_image("SIMD: ", simd);
            display_image("SISD: ", scalar);
        }

        virtual void display_stat(stat scalar, stat simd, const std::vector<stat>& refs)
        {
            using namespace std;

            cout << endl << string(83, '-') << endl;
            cout << setw(30) << "" << setw(15) << "_mask" << setw(10) << "Time (ms)" << setw(15) << "Min" << setw(15) << "Max" << endl;
            cout << string(83, '-') << endl;
            cout << scalar << endl;
            cout << simd << endl;
            cout << string(83, '-') << endl;
            cout << setw(30) << "Speedup " << setw(10) << (double)scalar.duration.count() / simd.duration.count() << endl;
            cout << string(83, '-') << endl;

            for(auto r : refs)
            {
                cout << r << endl;
            }

            cout << string(83, '-') << endl;
        }

        virtual void display_image(const std::string& title, const result& result)
        {
            cimg_library::CImg<uint8_t> img(_dim.x(), _dim.y(), 1, 3);

            for (int i = 0; i < _dim.x() * _dim.y(); i++)
            {
                int x, y;

                std::tie(x, y) = math::reshape<std::tuple<int, int>>(i, _dim);

                auto color1 = this->map_value(result.data[i]);

                img(x, y, 0) = color1.r;
                img(x, y, 1) = color1.g;
                img(x, y, 2) = color1.b;
            }

            img.display(title.c_str(), true);
        }
    protected:

        template<typename Disp>
        result execute(Disp& dispatcher)//, input_container input)
        {
            using namespace std::chrono;

            std::clog << "[HOST][EXECUTE] " << Disp::kernel_name() << std::endl;

            output_container data(_dim.x() * _dim.y());

            auto start = high_resolution_clock::now();
            auto arch = dispatcher.dispatch_one(data);
            auto end = high_resolution_clock::now();

            auto duration = duration_cast<milliseconds>(end - start);

            return {
                Disp::kernel_name(),
                data,
                duration,
                arch
            };
        }

        template<typename... Args>
        constexpr void configure_kernels(Args&& ...args)
        {
            _main_dispatcher.features() = _sysinfo;
            _main_dispatcher.dispatch_some(std::forward<Args>(args)...);

            zacc::for_each(_reference_dispatchers, [&](auto& k){
                k.features() = _sysinfo;
                k.dispatch_some(std::forward<Args>(args)...);
            });
        }

        virtual void configure() = 0;
        virtual util::color_rgb map_value(typename output_container::value_type value) = 0;

        math::vec2<int> _dim;

        system::dispatcher<system::kernel_dispatcher<Kernel>> _main_dispatcher;
        std::tuple<system::dispatcher<system::kernel_dispatcher<ReferenceKernels>>...> _reference_dispatchers;

        sysinfo _sysinfo;
    };

}}