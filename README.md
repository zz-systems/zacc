[![Build Status](https://travis-ci.org/zz-systems/zacc.svg?branch=develop)](https://travis-ci.org/zz-systems/zacc)
[![Build status](https://ci.appveyor.com/api/projects/status/j2pe355ld0pt60sq/branch/develop?svg=true)](https://ci.appveyor.com/project/zz-systems/zacc/branch/develop)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# ZACC
SIMD Abstraction layer that lets you write code as usual.

## License
Gorynych is released under the MIT License. See LICENSE.txt for details.

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
| AVX2 | :warning: | in development |
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
