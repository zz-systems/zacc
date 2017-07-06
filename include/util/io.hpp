//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

#include <iostream>
#include <iomanip>
#include <sstream>

#ifdef WIN32
#include <windows.h>
#endif

namespace zacc {

    enum color_codes {
            FG_RED      = 31,
            FG_GREEN    = 32,
            FG_YELLOW   = 33,
            FG_BLUE     = 34,            
            FG_DEFAULT  = 39,

            BG_RED      = 41,
            BG_GREEN    = 42,
            BG_YELLOW   = 43,
            BG_BLUE     = 44,
            BG_DEFAULT  = 49
    };

    struct color 
    {
        color(color_codes color_code) 
        {
            #if WIN32
                switch(color_code)
                {
                    case FG_RED:    this->color_code = FOREGROUND_RED|FOREGROUND_INTENSITY; break;
                    case FG_GREEN:  this->color_code = FOREGROUND_GREEN|FOREGROUND_INTENSITY; break;
                    case FG_YELLOW: this->color_code = FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_INTENSITY; break;
                    case FG_BLUE:   this->color_code = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY; break;
                    case FG_DEFAULT: this->color_code = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY; break;
                    
                    case BG_RED:        /*TODO*/ break;
                    case BG_GREEN:      /*TODO*/ break;
                    case BG_YELLOW:     /*TODO*/ break;
                    case BG_BLUE:       /*TODO*/ break;
                    case BG_DEFAULT:    /*TODO*/ break;
                }
            #else
                this->color_code = color_code; 
            #endif
        };

        unsigned short color_code;
        
        friend std::ostream &
            operator<<(std::ostream& s, const color& c)
        {
            #ifdef WIN32
                auto hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
                SetConsoleTextAttribute(hStdout,c.color_code);
            #else
                s << "\033[" << c.color_code << "m";
            #endif
            return s;
        }    
    };    

    struct blue_t     : color { blue_t()    : color(FG_BLUE) {} };
    struct red_t      : color { red_t()     : color(FG_RED) {} };
    struct green_t    : color { green_t()   : color(FG_GREEN) {} };
    struct yellow_t   : color { yellow_t()  : color(FG_YELLOW) {} };
    struct def_t      : color { def_t()     : color(FG_DEFAULT) {} };

    inline std::ostream& blue(std::ostream& out)   { return out << blue_t(); }
    inline std::ostream& red(std::ostream& out)    { return out << red_t(); }
    inline std::ostream& green(std::ostream& out)  { return out << green_t(); }
    inline std::ostream& yellow(std::ostream& out) { return out << yellow_t(); }
    inline std::ostream& def(std::ostream& out)    { return out << def_t(); }

    struct indent_t
    {
        using indentation_t = unsigned short;

        indent_t() : indentation(1) {}
        indent_t(indentation_t indentation) : indentation(indentation) {}
        indentation_t indentation;

        friend std::ostream& 
            operator<<(std::ostream& s, const indent_t& i)
        {
            for(unsigned short t = 0; t < i.indentation; t++)
                s << "\t";   
            
            return s;
        }                 
    };

    inline std::ostream& indent(std::ostream& out) { return out << indent_t(); }
    inline std::ostream& indent(std::ostream& out, indent_t::indentation_t indentation) { return out << indent_t(indentation); }
    
    struct boolcolor
    {
        boolcolor(bool value) : value(value) {}
        bool value;

        friend std::ostream& 
            operator<<(std::ostream& out, const boolcolor& i)
        {
            return out << std::boolalpha << (i.value ? green : red) << i.value << def << std::noboolalpha;
        }                 
    };

#ifdef WIN32
    #define ZTRACE_INTERNAL(cmd) do { std::stringstream s; s << cmd << std::endl; OutputDebugString(s.str().c_str()); } while(0)
#else
    #define ZTRACE_INTERNAL(cmd) std::clog << std::flush <<  cmd << std::endl;
#endif

#ifdef ZACC_TRACE
    #define ZTRACE_RAW(cmd) ZTRACE_INTERNAL(cmd)
#else
    #define ZTRACE_RAW(cmd)
#endif

#define ZTRACE_BACKEND(file, line, type, branch, func) ZTRACE_RAW(std::left << std::setw(32) << file << " line " STRINGIZE(line) ":" << std::left << std::setw(24) << " " << type << " " << std::left << std::setw(10) << branch << " " << func)

#define ZTRACE(block, message) ZTRACE_RAW(">> " << std::left << std::setw(29) << block << " line " << __LINE__ << ": " << message)

}