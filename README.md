[![Build Status](https://travis-ci.org/zz-systems/gorynych.svg?branch=develop)](https://travis-ci.org/zz-systems/gorynych)
[![Build status](https://ci.appveyor.com/api/projects/status/j2pe355ld0pt60sq/branch/develop?svg=true)](https://ci.appveyor.com/project/zz-systems/gorynych/branch/develop)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Gorynych
Yet another SIMD Abstraction layer

## License
Gorynych is released under the MIT License. See LICENSE.txt for details.

## About
Gorynych is an simple yet powerful computation abstraction layer targeting primarily game development due to its less precise nature.

It is still under development which is synchronous to [libsolowej](https://github.com/zz-systems/solowej) development.

Please keep in mind, that this release is a **Preview/Alpha Release** and feel free to report issues and bugs to the [Issue tracker on GitHub](https://github.com/zz-systems/gorynych/issues)

[Documentation](http://zz-systems.github.io/gorynych/htmldoc/index.html)

## Current state
* In development! 
* Tests insufficent (Only two different CPU's tested)
* Successfully used in [libsolowej](https://github.com/zz-systems/solowej) - a coherent noise library

## Tested CPU's:
* AMD FX-8350, Max. Feature: AVX1
* Intel Core i7 6500U, Max. Feature: AVX2

## Supported featuresets
* x87 FPU
* SSE2
* SSE3
* SSE3 + SSSE3
* SSE4.1/2
* FMA3/4 (not completely tested though)
* AVX1 (incomplete - int emulation is simply bad. You're better off using SSE4 for now) 
* AVX2

## Planned featuresets
* OpenCL / GPGPU support
* Verilog / VHDL generation for hardware synthesis
* Extending with more datatypes

## Functionality
* Basic matrix / vector support
* Basic arithmetics
* Conditionals
* Basic functions like abs, min, max, etc...
* Rounding 
* Trigonometry is in development
