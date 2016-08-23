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

// TODO

#include "../macros.h"
#include "float_cl.h"
#include "int_cl.h"
#include "builder.h"

namespace zzsystems { namespace gorynych {

	// Type traits =====================================================================================================

	/**
	 * @brief is true type when the supplied type is an opencl int32 value
	 */
	DISPATCHED struct is_vint<zzsystems::gorynych::_int_cl>
			: public std::true_type
	{};

	/**
	 * @brief is true type when the supplied type is an opencl float32 value
	 */
	DISPATCHED struct is_vreal<zzsystems::gorynych::_float_cl>
			: public std::true_type
	{};


	/**
	 * @brief the underlying type for opencl float32 value is a float scalar
	 */
	DISPATCHED struct scalar_type<_float_cl>
			: public __scalar_type<float>
	{};

	/**
	 * @brief the underlying type for opencl int32 value is an int scalar
	 */
	DISPATCHED struct scalar_type<_int_cl>
			: public __scalar_type<int>
	{};
    
	// Converting constructors =========================================================================================

    /// TODO

	/// converting constructor for float->int vector conversion
	DISPATCHED inline _int_cl::int_cl(const _float_cl& rhs) 
    			 { }

	/// copy constructor for int vector
	DISPATCHED inline _int_cl::int_cl(const _int_cl& rhs) 
			 { }

	/// copy constructor for float vector
	DISPATCHED inline _float_cl::float_cl(const _float_cl& rhs) 
    { 
        if(rhs.is_expression)
        {
            is_expression = false;
            name = random_var_name();           
        } 
        else 
        {
            is_expression = false;
            name = rhs.name;            
        }

        expression << name << " = " << var(rhs) << ";" << endl;
    }

	/// converting constructor for int->float vector conversion
	DISPATCHED inline _float_cl::float_cl(const _int_cl& rhs) 
    		{ }

	

	// Memory access: extract, gather, scatter (todo) ==================================================================

	/// extract int vector values to a memory location
	DISPATCHED void extract(const _int_cl &src, int* target)
	{
		// TODO
	}

	/// extract float vector values to a memory location
	DISPATCHED void extract(const _float_cl &src, float *target)
	{
		// TODO
	}

	/// gather int vector values from a memory location by an index vector
	DISPATCHED _int_cl vgather(const int* source, const _int_cl &index)
	{
		// TODO
        return 0;
	}

	/// gather float vector values from a memory location by an index vector
	DISPATCHED _float_cl vgather(const float* source, const _int_cl &index)
	{
		// TODO
        return 0;
	}

	// Converting selector =============================================================================================

	/// branchless if-then-else with conversion from float->int vector
	DISPATCHED_FUNC(vsel, _int_cl, HAS_OPENCL)
		(const _float_cl VREF mask, const _int_cl VREF b, const _int_cl VREF c)
	{
		BODY(vsel(_int_cl(mask), b, c));
	}

	/// branchless if-then-else with conversion from int->float vector
	DISPATCHED_FUNC(vsel, _float_cl, HAS_OPENCL)
		(const _int_cl VREF mask, const _float_cl VREF b, const _float_cl VREF c)
	{
		BODY(vsel(_float_cl(mask), b, c));
	}


	DISPATCHED_FUNC(visinf, _float_cl, HAS_OPENCL) (const _float_cl VREF a)
	{
		return 0;
	}

   
}}