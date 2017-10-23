cmake_minimum_required(VERSION 3.5)
project(Calendar)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${PROJECT_SOURCE_DIR}/headers) # Include headers diectory

set(HEADER_FILES Headers/date.hpp Headers/gregorian.hpp Headers/julian.hpp headers/kattistime.h headers/stripper.h Headers/calendar.hpp)
set(SOURCES main.cpp date.cpp gregorian.cpp julian.cpp kattistime.cpp)

# Add all files to the current target
add_executable(myexec ${SOURCES})



