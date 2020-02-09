include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(
    simulate OBJECT
    Minion.cpp
    MinionEvents.cpp
    Board.cpp
    Battle.cpp
    BattleMinions.cpp
    BattleEvents.cpp
    Simulation.cpp)

target_link_libraries(
    simulate
    gtest
    glog
)
