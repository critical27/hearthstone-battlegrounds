add_executable(
    demo
    Main.cpp
)

target_link_libraries(
    demo
    utils
    glog
    gtest
)

add_subdirectory(test)
add_subdirectory(utils)

