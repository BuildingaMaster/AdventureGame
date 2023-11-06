add_executable(AdventureTimeTesting
    test.cpp
    ../AdventureGame/BaseHealth.cpp 
    ../AdventureGame/Consumable.cpp 
    ../AdventureGame/ContextParser.cpp 
    ../AdventureGame/Inventory.cpp 
    ../AdventureGame/Item.cpp 
    ../AdventureGame/Location.cpp
    ../AdventureGame/PlayerActions.cpp
)

target_link_libraries(AdventureTimeTesting GTest::gtest)

add_custom_command(
        TARGET AdventureTimeTesting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbm
                ${CMAKE_HOME_DIRECTORY}/build/AdventureTimeTesting/map.mbm)

add_custom_command(
        TARGET AdventureTimeTesting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbd
                ${CMAKE_HOME_DIRECTORY}/build/AdventureTimeTesting/map.mbd)