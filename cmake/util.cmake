cmake_minimum_required(VERSION 3.6)

macro(insert_kv dict key)
    set("${dict}_${key}" ${ARGN})
endmacro()
