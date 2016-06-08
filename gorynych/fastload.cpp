//
// Created by szuyev on 19.05.16.
//


#include "fastload.h"
#include "dependencies.h"
#include "dispatch.h"
#include "gorynych.h"

namespace zzsystems { namespace gorynych {


#define CFL_TYPE(capability) static_dispatcher<capability>::vint
#define CFL_SPECIALIZATION(capability, for_value)\
        template<>	CFL_TYPE(capability) cfl<CFL_TYPE(capability), for_value>::val()

#define CFL_SPECIALIZATIONS(capability) \
	CFL_SPECIALIZATION(capability, -1) 	{ return ccl<CFL_TYPE(capability)>::ones(); } \
	CFL_SPECIALIZATION(capability, 0) 	{ return ccl<CFL_TYPE(capability)>::zeros(); } \
	CFL_SPECIALIZATION(capability, 1) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 31; } \
	CFL_SPECIALIZATION(capability, 2) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 31 << 1; } \
	CFL_SPECIALIZATION(capability, 3) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 30; } \
	CFL_SPECIALIZATION(capability, 4) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 31 << 2; } \
	CFL_SPECIALIZATION(capability, 5) 	{ return cfl<CFL_TYPE(capability), 1>::val() + cfl<CFL_TYPE(capability), 4>::val(); } \
	CFL_SPECIALIZATION(capability, 6) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 30 << 1; } \
	CFL_SPECIALIZATION(capability, 7) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 29; } \
	CFL_SPECIALIZATION(capability, 8) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 31 << 3; } \
	CFL_SPECIALIZATION(capability, 9) 	{ return cfl<CFL_TYPE(capability), 8>::val() + cfl<CFL_TYPE(capability), 1>::val(); } \
	CFL_SPECIALIZATION(capability, 10) 	{ return cfl<CFL_TYPE(capability), 7>::val() + cfl<CFL_TYPE(capability), 3>::val(); } \
	CFL_SPECIALIZATION(capability, 11) 	{ return cfl<CFL_TYPE(capability), 7>::val() + cfl<CFL_TYPE(capability), 4>::val(); } \
	CFL_SPECIALIZATION(capability, 12) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 30 << 2; } \
	CFL_SPECIALIZATION(capability, 13) 	{ return cfl<CFL_TYPE(capability), 7>::val() + cfl<CFL_TYPE(capability), 6>::val(); } \
	CFL_SPECIALIZATION(capability, 14) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 29 << 1; } \
	CFL_SPECIALIZATION(capability, 15) 	{ return cfl<CFL_TYPE(capability), 7>::val() + cfl<CFL_TYPE(capability), 8>::val(); }


#if defined(COMPILE_AVX2)
        CFL_SPECIALIZATIONS(capability_AVX2);
#elif defined(COMPILE_AVX1)
        CFL_SPECIALIZATIONS(capability_AVX1);
#elif defined(COMPILE_SSE4FMA)
        CFL_SPECIALIZATIONS(capability_SSE4FMA);
#elif defined(COMPILE_SSE4)
        CFL_SPECIALIZATIONS(capability_SSE4);
#elif defined(COMPILE_SSSE3)
        CFL_SPECIALIZATIONS(capability_SSSE3);
#elif defined(COMPILE_SSE3)
        CFL_SPECIALIZATIONS(capability_SSE3);
#elif defined(COMPILE_SSE2)
        CFL_SPECIALIZATIONS(capability_SSE2);
#else
        CFL_SPECIALIZATIONS(capability_FPU);

        //template<> float ccl<float>::sign1all0() 	{ return -0 }
		//template<> float ccl<float>::sign0all1() 	{ int temp = 0x7FFFFFFF; return *reinterpret_cast<float*>(&temp); }
#endif

#undef CFL_SPECIALIZATIONS
    }}
