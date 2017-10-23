cmake_minimum_required(VERSION 3.4)
project(Lab3)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Lab3_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR}/headers ${Lab3_SOURCE_DIR}/headers /Library/Frameworks/SDL2.framework/Headers)
link_directories (${SDL2_LIBRARY_DIRS}
        ${SDL2_IMAGE_LIBRARY_DIRS}
        ${SDL2_MIXER_LIBRARY_DIRS})

set(SOURCE_FILES skeleton.cpp SDL2Auxiliary.cpp headers/SDL2Auxiliary.h headers/TestModel.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2IMAGE_LIBRARY})

add_custom_target(
        Name [ALL]
        COMMAND valgrind --leak-check=full)

enable_testing()

add_test(toDoTest toDo)