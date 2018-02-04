//
// Vectorized and parallelized version of libnoise using the zacc SIMD toolkit
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


#include "entrypoint.hpp"

#include "system/arch.hpp"
#include "kernels/mandelbrot.hpp"
#include "kernels/julia.hpp"

zacc::system::entrypoint *mandelbrot_create_instance()
{
    using namespace zacc;
    using namespace zacc::examples;

    auto alloc = zacc::aligned_allocator<mandelbrot_kernel<dispatched_arch>, dispatched_arch::alignment>();
    auto ptr = alloc.allocate(sizeof(mandelbrot_kernel<dispatched_arch>));

    auto result = new(ptr) mandelbrot_kernel<zacc::dispatched_arch>();

    return result;
    //return new zacc::examples::mandelbrot_kernel<zacc::dispatched_arch>();
}

void mandelbrot_delete_instance(zacc::system::entrypoint* instance)
{
    using namespace zacc;
    using namespace zacc::examples;

    auto alloc = zacc::aligned_allocator<mandelbrot_kernel<dispatched_arch>, dispatched_arch::alignment>();

    if(instance != nullptr)
        alloc.deallocate(static_cast<mandelbrot_kernel<dispatched_arch>*>(instance), 0);
}

zacc::system::entrypoint *julia_create_instance()
{

    using namespace zacc;
    using namespace zacc::examples;


    auto alloc = zacc::aligned_allocator<julia_kernel<dispatched_arch>, dispatched_arch::alignment>();
    auto ptr = alloc.allocate(sizeof(julia_kernel<dispatched_arch>));

    auto result = new(ptr) julia_kernel<zacc::dispatched_arch>();

    return result;

    //return new zacc::examples::julia_kernel<zacc::dispatched_arch>();
}

void julia_delete_instance(zacc::system::entrypoint* instance)
{
    using namespace zacc;
    using namespace zacc::examples;

    auto alloc = zacc::aligned_allocator<julia_kernel<dispatched_arch>, dispatched_arch::alignment>();

    if(instance != nullptr)
        alloc.deallocate(static_cast<julia_kernel<dispatched_arch>*>(instance), 0);
}