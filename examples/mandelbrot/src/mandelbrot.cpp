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

#include "mandelbrot.host.hpp"

#include "system/sysinfo.hpp"

int main(int argc, char** argv)
{
    zacc::option_parser options(argc, argv);
    zacc::sysinfo sysinfo;

    options >> zacc::get_sysinfo(sysinfo);

    std::cout << zacc::put_sysinfo(sysinfo) << std::endl;

    std::cout << "Your system supports: " << std::endl;
    std::cout << zacc::sysinfo() << std::endl;

    zacc::math::vec2<int> dim       = { 2048, 2048 };
    zacc::math::vec2<float> cmin    = { -2, -2 };
    zacc::math::vec2<float> cmax    = { 2, 2 };
    size_t max_iterations           = 2048;
    bool headless                   = false;

    options["dim"] >> dim;
    options["cmin"] >> cmin;
    options["cmax"] >> cmax;
    options["max_iterations"] >> max_iterations;
    options["headless"] >> headless;

    zacc::examples::mandelbrot_host host(sysinfo, dim, cmin, cmax, max_iterations);

    host.run(!headless);

    return 0;
}
