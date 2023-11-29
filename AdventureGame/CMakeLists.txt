
add_executable(AdventureGame 
    AdventureGame.cpp 
    BaseHealth.cpp 
    CommonGameObjects.cpp
    Consumable.cpp 
    ContextParser.cpp 
    Inventory.cpp 
    Item.cpp 
    Location.cpp
    NPC.cpp
    PlayerActions.cpp
    PrintDisplay.cpp
)

add_custom_command(
        TARGET AdventureGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbm
                ${CMAKE_HOME_DIRECTORY}/AdventureGame/map.mbd
                $<TARGET_FILE_DIR:AdventureGame>
)
set_property(TARGET AdventureGame PROPERTY CXX_STANDARD 14)

