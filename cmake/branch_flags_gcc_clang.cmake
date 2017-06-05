insert_kv(branch_flags  scalar              "")
insert_kv(branch_flags  sse.sse2            -msse2)
insert_kv(branch_flags  sse.sse3            -msse3 -mssse3)

insert_kv(branch_flags  sse.sse41           -msse4.1)
insert_kv(branch_flags  sse.sse41.fma3      -msse4.1 -mfma)
insert_kv(branch_flags  sse.sse41.fma4      -msse4.1 -mfma4)

#insert_kv(branch_flags  sse.sse42      -msse4.1 -msse4.2)
#insert_kv(branch_flags  sse.sse42.fma3 -msse4.1 -msse4.2 -mfma)
#insert_kv(branch_flags  sse.sse42.fma4 -msse4.1 -msse4.2 -mfma4)

insert_kv(branch_flags  avx           -mavx -mfma)
insert_kv(branch_flags  avx2          -mavx2 -mfma)
insert_kv(branch_flags  avx512        -mavx512f -mavx512pf -mavx512er -mavx512cd -mavx512vl -mavx512bw -mavx512dq)