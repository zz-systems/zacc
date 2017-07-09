# ZACC
[![Build Status](https://travis-ci.org/zz-systems/zacc.svg?branch=develop)](https://travis-ci.org/zz-systems/zacc)
[![Build status](https://ci.appveyor.com/api/projects/status/j2pe355ld0pt60sq/branch/develop?svg=true)](https://ci.appveyor.com/project/zz-systems/zacc/branch/develop)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)


- [Abstract](#abstract)
- [Design goals](#design-goals)
- [Integration](#integration)
- [Examples](#examples)
    - [Implementation](#implementation)
    - [Entrypoint](#entrypoint)
    - [Dispatcher](#dispatcher)
    - [Invocation](#invocation)
- [Build system](#build-system)
- [Current state](#current-state)
    - [Tested hardware](#tested-hardware)
    - [Tested operating systems](#tested-operating-systems)
    - [Supported hardware features](#supported-hardware-features)
    - [Supported compilers](#supported-compilers)
    - [Supported data types](#supported-data-types)
    - [Functionality](#functionality)
- [License](#license)
- [Execute unit tests](#execute-unit-tests)


## Abstract

ZACC is a human-readable and extensible computation abstraction layer. 
Using ZACC and ZACC build, you are able to write and compile code once and execute it on target machines, unleashing their potential. 

It is still under development which is synchronous to [cacophony](https://github.com/zz-systems/cacophony) development.

Feel free to report issues and bugs to the [Issue tracker on GitHub](https://github.com/zz-systems/zacc/issues)

[Documentation](http://zz-systems.github.io/zacc/htmldoc/index.html)

## Design goals

There a few SIMD Libraries available, like Eigen or Agner Fog's vector class library, each of them following the same goal: accelerate your algorithms by using SIMD instructions.  

ZACC implementation had these goals:

- **Coding as if you would write vanilla C++.** 
    ```std::cout << (zint(32) % 16) << std::endl;``` prints ```[0, 0, 0, 0]``` if SSE extensions are used.
- **DRY.** 
    *Write once, run faster everywhere* 
- **Runtime feature selection.** 
    The dispatcher checks the system features and selects the best fitting implementation.
- **Easy integration.**
    ZACC offers cmake scripts to build your project.
- **Portability.**
    ZACC accelerated projects should be able to run on any OS and any processor.
- **Speed.**
    Although ZACC may be not the highest-optimized library in the world, speed combined with a great usability is a high priority.


## Integration

The project is available as a direct submodule if you use git or [released here](https://github.com/zz-systems/zacc/releases).

If you decide for the submodule way, simply add it via ```git submodule add https://github.com/zz-systems/zacc.git```

CMake is required in your project to be able to use ZACC and ZACC build system.

## Examples

### Implementation

Your algorithm may look like below and be able to use SSE2, SSE3, SSE4, FMA, AVX, AVX2 features of the host processor.
*Write once, run faster everywhere :)*

```cpp
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
```

To be able to run the implementation, you need some supporting infrastructure in the code.
You'll need an entrypoint and a dispatcher which will select the proper entrypoint at runtime. 
Fortunately, the dispatcher is already implemented and you only need to adapt it to fit your needs.

### Entrypoint

The entrypoint is a template specialization outside of a header, you need to implement it in your project.

```cpp
// @file perlin_engine_entrypoint.cpp

#include <memory>

#include "system/branch.hpp"
#include "system/entrypoint.hpp"
#include "perlin_engine.hpp"

template<>
std::shared_ptr<zacc::entrypoint> zacc::system::resolve_entrypoint<zacc::dispatched_branch::types>()
{
    std::cout   << "Creating engine for " 
                << zacc::dispatched_branch::types::major_branch_name() << std::endl;
                
    return std::static_pointer_cast<zacc::entrypoint>(
            zacc::make_shared<perlin_engine<zacc::dispatched_branch::types>>()
    );
}

```

### Dispatcher
The dispatcher only invokes the entrypoint function with fitting branch parameters. 

```cpp
// @file perlin_dispatcher.hpp

#include <memory>
#include "system/entrypoint.hpp"

struct perlin_dispatcher
{    
    DISPATCHED void dispatch_impl(const vec3<float> &origin, float *target)
    {
        auto engine = std::static_pointer_cast<perlin_engine<branch>>(
                        zacc::system::resolve_entrypoint<branch>()
                );
                
        engine->run(origin, float);
    }
};

using perlin_dispatcher = zacc::runtime_dispatcher<perlin_dispatcher>;
```

### Invocation
And put it all together:

```cpp
// @file perlin_main.cpp

#include <array>
#include "perlin_dispatcher.hpp"

int main(int argc, char** argv)
{
    std::array<float, 1024> target;
    perlin_dispatcher->run({0, 0, 0}, target.data());
    
    // display data
    ...
    
    return 0;    
}
```
## Build system 

The basic setup looks like this:
```cmake
# add zacc targets
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/zacc)

# use zacc build system
include(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/zacc/cmake/zacc.shared.cmake)

# add include lookup directories
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/zacc/include
)
```
Now you may want to introduce your own logic to be accelerated:
```cmake
# your shared library which aggregates the branches
zacc_add_dispatched_library(_your_library_ 
        # your accelerated logic
        ENTRYPOINT ${CMAKE_SOURCE_DIR}/_your_library_branch_entrypoint.cpp
        
        # branches to build for
        BRANCHES "${ZACC_CONFIGURED_BRANCHES}"
        
        # additional include directories
        INCLUDES ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/dependencies/zacc/include
        
        # your main library source
        SOURCES 
            ${CMAKE_SOURCE_DIR}/_your_library_.cpp 
        )
```

And you may want to test your implementation on all supported branches as well:

```cmake
# unit testing your implementation on all branches

# find the test main (you may provide your own implementation)
file(GLOB ZACC_TEST_MAIN "${PROJECT_SOURCE_DIR}/*/zacc/*/test_main.cpp")
# find the test entry point (you may provide your own implementation)
file(GLOB ZACC_TEST_ENTRYPOINT "${PROJECT_SOURCE_DIR}/*/zacc/*/test_entry_point.cpp")

zacc_add_dispatched_tests(cacophony.tests
        # test main. used to skip the tests if the processing unit is not 
        # capable of running a particular featureset
        TEST_MAIN ${ZACC_TEST_MAIN}
        
        # gtest main
        TEST_ENTRYPOINT ${ZACC_TEST_ENTRYPOINT}
        
        # branches to build for
        BRANCHES "${ZACC_CONFIGURED_BRANCHES}"
        
        # additional include directories
        INCLUDES ${CMAKE_SOURCE_DIR}/include
        
        # your test sources
        SOURCES
            ${_your_test_files_here}
        )
```

## Current state
* In development! 
* Tests insufficent (Only two different CPU's tested)
* Successfully used in [cacophony](https://github.com/zz-systems/cacophony) - a coherent noise library

### Tested hardware:

| Processor | Highest featureset |
|-----------|------------|
| AMD FX-8350 | AVX1 |
| Intel Core i7 6500U | AVX2 + FMA |
| Intel Core i7 7700K | AVX2 + FMA |
| Intel Xeon E5-2697 v3 | AVX2 + FMA|
| Intel Xeon E5-2680 v3 | AVX2 + FMA|
| Intel Xeon E5-2680 v2 | AVX1 |
| Intel Xeon X5570 | SSE4.1 |

### Tested operation systems

- Mac OS X Sierra
- Linux
- Windows 10

### Supported hardware features

| Featureset | State |  |
|-----------|---|--------------|
| x87 FPU | :white_check_mark: | scalar |
| SSE2 | :white_check_mark: |  |
| SSE3 | :white_check_mark: |
| SSE3 + SSSE3 | :white_check_mark: |
| SSE4.1 | :white_check_mark: |
| SSE4.1 + FMA3 | :white_check_mark: |
| SSE4.1 + FMA4 | :white_check_mark: |
| AVX1 | :white_check_mark: | Emulated integer vectors |
| AVX1 + FMA3 | :white_check_mark: | Emulated integer vectors |
| AVX2 | :white_check_mark: |  |
| AVX512 | :no_entry: | in development, can't be tested yet* |
| ARM NEON | :no_entry: | Not implemented yet |
| GPGPU | :no_entry: | Not implemented yet** |
| HDL | :no_entry: | Not implemented yet*** |

*For AVX512, access to a Xeon Phi accelerator or a modern Xeon CPU is necessary

**Some work is already done for the OpenCL implementation. Some macros or C++ code postprocessing may be introduced.

***Same starting issues as for the GPGPU feature, the code generation is another topic.


### Supported compilers
| Compiler | State |  |
|-----------|---|--------------|
| GCC 5 | :white_check_mark: |  |
| GCC 6 | :white_check_mark: |  |
| Clang 3.9 | :white_check_mark: |  |
| Clang 4.0 | :white_check_mark: |  |
| Clang-cl | :white_check_mark: |  |
| MSVC | :no_entry: | Not supported* |

*MSVC is not supported due to required fine granular compile options and non-conform C++ implementation. 
Instead Clang-cl is used, which is binary compatible with MSVC ([work in progress](https://clang.llvm.org/docs/MSVCCompatibility.html)). 

### Supported datatypes 
| C++ scalar type | ZACC vector type | State |   |
|-----------|---|---|--------------|
| signed int8 | zint8, zbyte | :white_check_mark: |  Partially emulated.  |
| signed int16 | zint16, zshort | :white_check_mark: |  |
| signed int32 | zint32, zint | :white_check_mark: |  |
| signed int64 | zint64, zlong | :no_entry: | Not implemented yet |
| float16 | zfloat16 | :no_entry: | Not implemented yet |
| float32| zfloat, zfloat32 | :white_check_mark: |  |
| float64 | zdouble, zfloat64 | :white_check_mark: | |


### Functionality
* Basic matrix / vector support
* Basic arithmetics
* Conditionals
* Basic functions like abs, min, max, etc...
* Rounding 
* Trigonometry is in development


## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The library is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2015-2017 Sergej Zuyev

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Execute unit tests
To compile and run the tests, you need to execute 
```
$ make zacc.tests.all
$ ctest
--------------------------------------------------------------------
    Start 1: ci.zacc.tests.scalar
1/8 Test #1: ci.zacc.tests.scalar .............   Passed    0.01 sec
    Start 2: ci.zacc.tests.sse.sse2
2/8 Test #2: ci.zacc.tests.sse.sse2 ...........   Passed    0.01 sec
    Start 3: ci.zacc.tests.sse.sse3
3/8 Test #3: ci.zacc.tests.sse.sse3 ...........   Passed    0.01 sec
    Start 4: ci.zacc.tests.sse.sse41
4/8 Test #4: ci.zacc.tests.sse.sse41 ..........   Passed    0.01 sec
    Start 5: ci.zacc.tests.sse.sse41.fma3
5/8 Test #5: ci.zacc.tests.sse.sse41.fma3 .....   Passed    0.01 sec
    Start 6: ci.zacc.tests.sse.sse41.fma4
6/8 Test #6: ci.zacc.tests.sse.sse41.fma4 .....   Passed    0.00 sec
    Start 7: ci.zacc.tests.avx
7/8 Test #7: ci.zacc.tests.avx ................   Passed    0.01 sec
    Start 8: ci.zacc.tests.avx2
8/8 Test #8: ci.zacc.tests.avx2 ...............   Passed    0.01 sec

100% tests passed, 0 tests failed out of 8

Total Test time (real) =   0.11 sec
```