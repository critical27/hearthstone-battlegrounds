cmake_minimum_required (VERSION 3.0)

project (hearthstone-battlegrounds)

MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
add_subdirectory(3rd-party/googletest)
add_subdirectory(3rd-party/glog)
add_subdirectory(3rd-party/gflags)
include_directories(3rd-party/googletest/include)
include_directories(3rd-party/glog)
include_directories(3rd-party/gflags)
