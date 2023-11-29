add_executable(AdventureTimeTesting
    test.cpp
    ../AdventureGame/BaseHealth.cpp 
    ../AdventureGame/CommonGameObjects.cpp
    ../AdventureGame/Consumable.cpp 
    ../AdventureGame/ContextParser.cpp 
    ../AdventureGame/Inventory.cpp 
    ../AdventureGame/Item.cpp 
    ../AdventureGame/Location.cpp
    ../AdventureGame/NPC.cpp
    ../AdventureGame/PlayerActions.cpp
    ../AdventureGame/PrintDisplay.cpp
)

set_property(TARGET AdventureTimeTesting PROPERTY CXX_STANDARD 14)
target_link_libraries(AdventureTimeTesting GTest::gtest)

add_custom_command(
        TARGET AdventureTimeTesting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbm
                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbd
                $<TARGET_FILE_DIR:AdventureTimeTesting>)
                
gtest_discover_tests(AdventureTimeTesting
        WORKING_DIRECTORY $<TARGET_FILE_DIR:AdventureTimeTesting>
)