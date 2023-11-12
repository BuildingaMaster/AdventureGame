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

set_property(TARGET AdventureTimeTesting PROPERTY CXX_STANDARD 14)
target_link_libraries(AdventureTimeTesting GTest::gtest)
gtest_discover_tests(AdventureTimeTesting)

if(${CMAKE_GENERATOR} EQUAL "Xcode")
add_custom_command(
        TARGET AdventureTimeTesting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbm
                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbd
                ${CMAKE_BINARY_DIR}/AdventureTimeTesting/${CMAKE_BUILD_TYPE})
else()                
add_custom_command(
        TARGET AdventureTimeTesting POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbm
                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbd
                ${CMAKE_BINARY_DIR}/AdventureTimeTesting)
endif()
#add_custom_command(
#        TARGET AdventureTimeTesting POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbd
#                ${CMAKE_CURRENT_BINARY_DIR}/map.mbd)