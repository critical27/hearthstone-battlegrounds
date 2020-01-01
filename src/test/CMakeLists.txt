include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(
    minion_board_test
    MinionBoardTest.cpp
)

target_link_libraries(
    minion_board_test
    utils
    gtest
    glog
)