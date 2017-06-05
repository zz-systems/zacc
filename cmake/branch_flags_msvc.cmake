insert_kv(branch_flags  scalar              /arch:IA32)
insert_kv(branch_flags  sse.sse2            /arch:SSE2)
insert_kv(branch_flags  sse.sse3            /arch:SSE2)

insert_kv(branch_flags  sse.sse41           /arch:SSE2)
insert_kv(branch_flags  sse.sse41.fma3      /arch:SSE2)
insert_kv(branch_flags  sse.sse41.fma4      /arch:SSE2)

#insert_kv(branch_flags  sse.sse42      -msse4.1 -msse4.2)
#insert_kv(branch_flags  sse.sse42.fma3 -msse4.1 -msse4.2 -mfma)
#insert_kv(branch_flags  sse.sse42.fma4 -msse4.1 -msse4.2 -mfma4)

insert_kv(branch_flags  avx           /arch:AVX)
insert_kv(branch_flags  avx2          /arch:AVX2)
insert_kv(branch_flags  avx512        /arch:AVX512)