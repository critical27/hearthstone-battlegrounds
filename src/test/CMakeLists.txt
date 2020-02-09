include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(
    minion_board_test
    MinionBoardTest.cpp
)

target_link_libraries(
    minion_board_test
    simulate
    utils
    gtest
    glog
)

add_executable(
    battle_test
    BattleTest.cpp
)

target_link_libraries(
    battle_test
    simulate
    utils
    gtest
    glog
)

add_executable(
    simulation_test
    SimulationTest.cpp
)

target_link_libraries(
    simulation_test
    simulate
    utils
    gtest
    glog
)
