cmake_minimum_required(VERSION 3.5)
project(AdventureGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(Headers)

set(ITEM_FILES Items/Chest.cpp Items/Key.cpp Items/Map.cpp Items/Scroll.cpp Items/Potion.cpp Items/Equipment.cpp)
set(SETTING_FILES Settings/Gurubashi.cpp Settings/Icecrown.cpp Settings/Orgrimmar.cpp Settings/Ruins.cpp Settings/Woods.cpp Settings/Onyxia.cpp)
set(CHARACTER_FILES Characters/Beast.cpp Characters/DeathKnight.cpp Characters/Mage.cpp Characters/Paladin.cpp Characters/Priest.cpp Characters/Boss.cpp)

set(SOURCE_FILES Main.cpp GameEngine.cpp Setting.cpp Character.cpp ${ITEM_FILES} ${SETTING_FILES} ${CHARACTER_FILES})
# GameEngine.cpp Headers/Character.h Headers/GameEngine.h Headers/Item.h Headers/Setting.h
# Headers/Scroll.h Headers/Map.h Headers/Chest.h Headers/Key.h Headers/Gurubashi.h
# Headers/Icecrown.h Headers/Orgrimmar.h Headers/Ruins.h Headers/Woods.h
# Items/Chest.cpp Items/Key.cpp Items/Map.cpp Items/Scroll.cpp
# Settings/Gurubashi.cpp Settings/Icecrown.cpp Settings/Orgrimmar.cpp Settings/Ruins.cpp Settings/Woods.cpp
add_executable(AdventureGame ${SOURCE_FILES})