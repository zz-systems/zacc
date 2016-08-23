//
// Created by szuyev on 17.05.16.
//

//#include "../Catch/single_include/catch.hpp"
#define COMPILE_OPENCL
#include "../gorynych/gorynych.h"

#include "test_extensions.h"

namespace zzsystems { namespace gorynych { namespace  test {

#define TYPE_PREFIX TEST_PREFIX("cl_float_codegen")


            const float _num1 = 45.56345f;
            const float _num2 = -23.00005f;
            const float _num3 = 192.060194f;

            TEST_CASE(TYPE_PREFIX" codegen", "[arithmetic]")
            {
                cl_builder::register_mapping("vreal",               "float");
                cl_builder::register_mapping("vint",                "int");
                cl_builder::register_mapping("vec3<vreal>",         "float3");
                cl_builder::register_mapping("vec3<vint>",          "int3");
                cl_builder::register_mapping("vec3<int>",           "float3");
                cl_builder::register_mapping("vec3<float>",         "int3");
                cl_builder::register_mapping("noisegen<SIMD_T>::",  "");
                cl_builder::register_mapping("static_cast<vint>",   "(int)");   
                cl_builder::register_mapping("static_cast<vreal>",  "(float)");
                cl_builder::register_mapping("static_cast<int>",   "(int)");   
                cl_builder::register_mapping("static_cast<float>",  "(float)");                   
                cl_builder::register_mapping("mat2x3<vint>",        "mat2x3i");
                cl_builder::register_mapping("this->",              "");
                cl_builder::register_mapping("numeric_limits<int>::max()", "INT_MAX");

                auto frequency = 0.5f;
                auto lacunarity = 0.125f;
                auto persistence = 0.25f;
                auto seed = 1111;
                auto octaves = 5;
                int quality = 34;

                REGISTER_CL_TYPE(enum, Quality, { Fast, Standard, Best });

                REGISTER_CL_TYPE(struct, mat2x3i, { int3 a; int3 b; });
                REGISTER_CL_TYPE(struct, mat2x3f, { float3 a; float3 b; });


                REGISTER_CL_FUNC(float, mod_perlin, (float3 c), 
				    CAPTURE_CL_PARAMS(NV(frequency), NV(lacunarity), NV(persistence), NV(seed), NV(octaves), NV(quality)),
                {			
                    vreal	value = cfl<vreal, 0>::val(),
                            currentPersistence = cfl<vreal, 1>::val();

                    vec3<vreal> _coords = c * frequency;

                    for (int curOctave = 0; curOctave < octaves; curOctave++)
                    {
                        value += currentPersistence * noisegen<SIMD_T>::gradient_coherent_3d(
                            clamp_int32(_coords),
                            seed + curOctave, //& 0xffffffff,
                            quality);

                        // Prepare the next octave.
                        _coords *= lacunarity;
                        currentPersistence *= persistence;
                    }

                    return value;
                });

				auto displacement = 0.625;

		        
		        bool enableDistance = true;

                REGISTER_CL_FUNC(float, mod_voronoi, (float3 coords), 
				    CAPTURE_CL_PARAMS(NV(frequency), NV(displacement), NV(seed), NV(enableDistance)),
                {			
                    vec3<vreal> _coords = coords * frequency;
                    vec3<vint> _seed = (seed, seed + 1, seed + 2);
                                
                    vec3<vint> lowerEdge
                    (
                        static_cast<vint>(vfloor(_coords.x)), 
                        static_cast<vint>(vfloor(_coords.y)),
                        static_cast<vint>(vfloor(_coords.z))
                    );

                    vreal value(0), absDist(0), minDist(static_cast<float>(numeric_limits<int>::max()));

                    vec3<vreal> candidate(0);//(0.0f, 0.0f, 0.0f);
                    vec3<vreal> cur_r(0), pos(0), dist(0);
                    vec3<vint> cur(0);

                    // Inside each unit cube, there is a seed point at a random position.  Go
                    // through each of the nearby cubes until we find a cube with a seed point
                    // that is closest to the specified position.

                    for (auto zoff = -2; zoff <= 2; zoff++)
                    {	
                        cur_r.z = static_cast<vreal>(cur.z = lowerEdge.z + zoff);

                        for (auto yoff = -2; yoff <= 2; yoff++)
                        {
                            cur_r.y = static_cast<vreal>(cur.y = lowerEdge.y + yoff);

                            for (auto xoff = -2; xoff <= 2; xoff++)
                            {
                                cur_r.x = static_cast<vreal>(cur.x = lowerEdge.x + xoff);

                                pos.x = cur_r.x + noisegen<SIMD_T>::realvalue_3d(cur, _seed.x);
                                pos.y = cur_r.y + noisegen<SIMD_T>::realvalue_3d(cur, _seed.y);
                                pos.z = cur_r.z + noisegen<SIMD_T>::realvalue_3d(cur, _seed.z);

                                dist = pos - _coords;
                                absDist = dist.dot(dist);

                                //select_candidate(absDist, pos, minDist, candidate);
                                auto mask = absDist < minDist;

                                candidate.x = vsel(mask, pos.x, candidate.x);
                                candidate.y = vsel(mask, pos.y, candidate.y);
                                candidate.z = vsel(mask, pos.z, candidate.z);

                                minDist = vsel(mask, absDist, minDist);
                            }
                        }
                    }
                            
                    auto noise = noisegen<SIMD_T>::realvalue_3d(
                    {
                        static_cast<vint>(vfloor(candidate.x)),
                        static_cast<vint>(vfloor(candidate.y)),
                        static_cast<vint>(vfloor(candidate.z))
                    },
                    _seed.x);

                auto v = value;

                if (this->enableDistance)
                {
                    auto diff		= candidate - _coords;
                    auto absDiff	= diff.magnitude();
                    
                    // value =  absDiff * sqrt3 - 1
                    value = vfmsub(absDiff, consts<vreal>::sqrt3(), cfl<vreal, 1>::val());
                }	
                else
                {
                    value = cfl<vreal, 0>::val();
                }

                /*if (dim<vreal>() > 1)
                    cout << extract(noise)[4] << endl;*/
                /*v = value;
                cout << extract(v)[0] << endl;*/
                // return settings.displacement * noise + value
                return vfmadd(this->displacement, noise, value);

                });

            }
            //SCENARIO()
            TEST_CASE(TYPE_PREFIX" arithmetic add", "[arithmetic]")
            {
                // vreal one(1), other(2);

                // //one = vreal(1);
                // //other = vreal(2);

                // //one = other + one;

                // cout << one.expression.str() << endl;
                // cout << other.expression.str() << endl;

                // auto temp = (one + other);
                // cout << temp.expression.str() << endl;

                // cout << (one + other + temp).expression.str() << endl;

                // auto temp2 = -one;
                // cout << temp2.expression.str() << endl;

                // cout << "inplace: " << (one + ((1 + one) + 5.0f)).expression.str() << endl;

                // vreal temp3(one + other);

                // cout << "temp3:" << temp3.expression.str() << endl;
                //test<vreal, sreal>(_num1, _num2, std::plus<sreal>(), std::plus<vreal>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic sub", "[arithmetic]")
            {
                //test<vreal, sreal>(_num1, _num2, std::minus<sreal>(), std::minus<vreal>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic mul", "[arithmetic]")
            {
                //test<vreal, sreal>(_num1, _num2, std::multiplies<sreal>(), std::multiplies<vreal>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic div", "[aritmetic]")
            {
                //test<vreal, sreal>(_num1, _num2, std::divides<sreal>(), std::divides<vreal>());
            }

            TEST_CASE(TYPE_PREFIX" arithmetic neg", "[arithmetic]")
            {
                //test<vreal, sreal>(_num2, std::negate<sreal>(), std::negate<vreal>());
            }

            TEST_CASE(TYPE_PREFIX" fused multiply add", "[arithmetic]")
            {
                //test<vreal, sreal>(_num1, _num2, _num3, [](auto a, auto b, auto c) { return a * b + c; }, [](auto a, auto b, auto c) { return vfmadd(a, b, c); });
            }

            TEST_CASE(TYPE_PREFIX" fused multiply sub", "[arithmetic]")
            {
                //test<vreal, sreal>(_num1, _num2, _num3, [](auto a, auto b, auto c) { return a * b - c; }, [](auto a, auto b, auto c) { return vfmsub(a, b, c); });
            }

            // Bitwise =================================================================================================

//            TEST_CASE(TYPE_PREFIX" bitwise and", "[bitwise]")
//            {
//                test<vreal, sreal>(_num1, _num2, std::bit_and<sreal>(), std::bit_and<vreal>());
//            }
//
//            TEST_CASE(TYPE_PREFIX" bitwise or", "[bitwise]")
//            {
//                test<vreal, sreal>(_num1, _num2, std::bit_or<sreal>(), std::bit_or<vreal>());
//            }
//
//            TEST_CASE(TYPE_PREFIX" bitwise not", "[bitwise]")
//            {
//                test<vreal, sreal>(_num2, std::bit_not<sreal>(), std::bit_not<vreal>());
//            }
//
//            TEST_CASE(TYPE_PREFIX" bitwise xor", "[bitwise]")
//            {
//                test<vreal, sreal>(_num1, _num2, std::bit_xor<sreal>(), std::bit_xor<vreal>());
//            }

            // Logic ===================================================================================================

            TEST_CASE(TYPE_PREFIX" logic gt", "[logic]")
            {
                //btest<vreal, sreal>(_num1, _num2, std::greater<sreal>(), [](auto a, auto b) { return a > b; });
                //btest<vreal, sreal>(_num2, _num1, std::greater<sreal>(), [](auto a, auto b) { return a > b; });
            }

            TEST_CASE(TYPE_PREFIX" logic lt", "[logic]")
            {
                //btest<vreal, sreal>(_num1, _num2, std::less<sreal>(), [](auto a, auto b) { return a < b; });
                //btest<vreal, sreal>(_num2, _num1, std::less<sreal>(), [](auto a, auto b) { return a < b; });
            }

            TEST_CASE(TYPE_PREFIX" logic eq", "[logic]")
            {
                //btest<vreal, sreal>(_num1, _num2, std::equal_to<sreal>(), [](auto a, auto b) { return a == b; });
                //btest<vreal, sreal>(_num2, _num2, std::equal_to<sreal>(), [](auto a, auto b) { return a == b; });
            }

            TEST_CASE(TYPE_PREFIX" logic neq", "[logic]")
            {
                //btest<vreal, sreal>(_num1, _num2, std::not_equal_to<sreal>(), [](auto a, auto b) { return a != b; });
                //btest<vreal, sreal>(_num2, _num2, std::not_equal_to<sreal>(), [](auto a, auto b) { return a != b; });
            }

            // Functions ===============================================================================================

            TEST_CASE(TYPE_PREFIX" functions vabs", "[functions]")
            {
                //test<vreal, sreal>(_num1, [](auto a) { return vabs(a); }, [](auto a) { return vabs(a); });
                //test<vreal, sreal>(_num2, [](auto a) { return vabs(a); }, [](auto a) { return vabs(a); });
            }

            TEST_CASE(TYPE_PREFIX" functions vmin", "[functions]")
            {
                //test<vreal, sreal>(_num1, _num2, [](auto a, auto b) { return vmin(a, b); }, [](auto a, auto b) { return vmin(a, b); });
                //test<vreal, sreal>(_num2, _num1, [](auto a, auto b) { return vmin(a, b); }, [](auto a, auto b) { return vmin(a, b); });
            }

            TEST_CASE(TYPE_PREFIX" functions vmax", "[functions]")
            {
                //test<vreal, sreal>(_num1, _num2, [](auto a, auto b) { return vmax(a, b); }, [](auto a, auto b) { return vmax(a, b); });
                //test<vreal, sreal>(_num2, _num1, [](auto a, auto b) { return vmax(a, b); }, [](auto a, auto b) { return vmax(a, b); });
            }

            TEST_CASE(TYPE_PREFIX" functions vsel", "[functions]")
            {
                //test<vreal, sreal>(_num1, _num2, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
                //test<vreal, sreal>(_num2, _num1, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
                //test<vreal, sreal>(_num2, _num2, [](auto a, auto b) { return a > b ? a : b; }, [](auto a, auto b) { return vsel(a > b, a, b); });
            }
            
            // Rounding ================================================================================================

            TEST_CASE(TYPE_PREFIX" truncate", "[rounding]")
            {
                //test<vreal, sreal>(_num1, [](auto a) { return std::trunc(a); }, [](auto a) { return vtrunc(a); });
                //test<vreal, sreal>(_num2, [](auto a) { return std::trunc(a); }, [](auto a) { return vtrunc(a); });
                //test<vreal, sreal>(_num3, [](auto a) { return std::trunc(a); }, [](auto a) { return vtrunc(a); });
            }

            TEST_CASE(TYPE_PREFIX" floor", "[rounding]")
            {
                //test<vreal, sreal>(_num1, [](auto a) { return std::floor(a); }, [](auto a) { return vfloor(a); });
                //test<vreal, sreal>(_num2, [](auto a) { return std::floor(a); }, [](auto a) { return vfloor(a); });
                //test<vreal, sreal>(_num3, [](auto a) { return std::floor(a); }, [](auto a) { return vfloor(a); });
            }

            TEST_CASE(TYPE_PREFIX" ceil", "[rounding]")
            {
                //test<vreal, sreal>(_num1, [](auto a) { return std::ceil(a); }, [](auto a) { return vceil(a); });
                //test<vreal, sreal>(_num2, [](auto a) { return std::ceil(a); }, [](auto a) { return vceil(a); });
                //test<vreal, sreal>(_num3, [](auto a) { return std::ceil(a); }, [](auto a) { return vceil(a); });
            }

            TEST_CASE(TYPE_PREFIX" round", "[rounding]")
            {
                //test<vreal, sreal>(_num1, [](auto a) { return std::round(a); }, [](auto a) { return vround(a); });
                //test<vreal, sreal>(_num2, [](auto a) { return std::round(a); }, [](auto a) { return vround(a); });
                //test<vreal, sreal>(_num3, [](auto a) { return std::round(a); }, [](auto a) { return vround(a); });
            }
        }
    }
}