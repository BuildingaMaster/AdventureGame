
add_executable(AdventureGame 
    AdventureGame.cpp 
    BaseHealth.cpp 
    Consumable.cpp 
    ContextParser.cpp 
    Inventory.cpp 
    Item.cpp 
    Location.cpp
    PlayerActions.cpp
)

if(${CMAKE_GENERATOR} EQUAL "Xcode")
add_custom_command(
        TARGET AdventureGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbm
                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbd
                ${CMAKE_BINARY_DIR}/AdventureGame/${CMAKE_BUILD_TYPE}
        COMMENT "Copy files.")
else()
add_custom_command(
        TARGET AdventureGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbm
                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbd
                ${CMAKE_BINARY_DIR}/AdventureGame
        COMMENT "Copy files.")
endif()
set_property(TARGET AdventureGame PROPERTY CXX_STANDARD 14)
message(STATUS "CMAKE_CURRENT_BINARY_DIR/CMAKE_BUILD_TYPE = ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}")
