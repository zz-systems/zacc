[![Build Status](https://travis-ci.org/zz-systems/zacc.svg?branch=develop)](https://travis-ci.org/zz-systems/zacc)
[![Build status](https://ci.appveyor.com/api/projects/status/j2pe355ld0pt60sq/branch/develop?svg=true)](https://ci.appveyor.com/project/zz-systems/zacc/branch/develop)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Design goals

# Integration

The required main header, file `zacc.hpp` is in the include directory. All you need to do is add

```cpp
#include "zacc.hpp"
```

To adapt your CMake project to the dispatched build system of **ZACC**, consider using the predefined macro `dispatch(_your_target_name_)`


# Examples

## About
ZACC is a powerful computation abstraction layer targeting primarily game development due to its less precise nature.

It is still under development which is synchronous to [cacophony](https://github.com/zz-systems/cacophony) development.

Please keep in mind, that this release is a **Preview/Alpha Release** and feel free to report issues and bugs to the [Issue tracker on GitHub](https://github.com/zz-systems/zacc/issues)

[Documentation](http://zz-systems.github.io/zacc/htmldoc/index.html)

## Current state
* In development! 
* Tests insufficent (Only two different CPU's tested)
* Successfully used in [cacophony](https://github.com/zz-systems/cacophony) - a coherent noise library

## Tested processing units:

| Processor | Featureset |
|-----------|------------|
| AMD FX-8350 | AVX1 |
| Intel Core i7 6500U | AVX2 |
| Intel Core i7 7700K | SSE4.1 |

## Featuresets

| Featureset | State |  |
|-----------|---|--------------|
| x87 FPU | :white_check_mark: | scalar |
| SSE2 | :white_check_mark: |  |
| SSE3 | :white_check_mark: |
| SSE3 + SSSE3 | :white_check_mark: |
| SSE4.1 | :white_check_mark: |
| SSE4.1 + FMA3 | :white_check_mark: |
| SSE4.1 + FMA4 | :white_check_mark: |
| AVX1 | :warning: | integer vector emulation sucks |
| AVX2 | :warning: | in development, works on windows |
| AVX512 | :no_entry: | in development, can't be tested by myself* |
| GPGPU | :no_entry: | May come, depending on my research success |
| HDL | :no_entry: | May come, depending on my research success |

## Supported datatypes 
| Type | State |  |
|-----------|---|--------------|
| int8 | :warning: | No real-life tests yet |
| int16 | :warning: | No real-life tests yet |
| int32 | :white_check_mark: |  |
| int64 | :no_entry: | Not implemented yet |
| float16 | :no_entry: | Not implemented yet |
| float32| :white_check_mark: |  |
| float64 | :white_check_mark: |  |

## Functionality
* Basic matrix / vector support
* Basic arithmetics
* Conditionals
* Basic functions like abs, min, max, etc...
* Rounding 
* Trigonometry is in development

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2013-2017 Sergej Zuyev

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.