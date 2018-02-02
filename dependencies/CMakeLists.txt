cmake_minimum_required(VERSION 3.3.2)
project(zacc.dependencies NONE)


# Store old value
set(BUILD_SHARED_LIBS_OLD ${BUILD_SHARED_LIBS})
# Assign desired value for subproject
set(BUILD_SHARED_LIBS ON)
# Step into subproject
add_subdirectory(googletest)
# Restore old value
set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS_OLD})

include_directories(cimg)