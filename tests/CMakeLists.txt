cmake_minimum_required(VERSION 3.1)

project(GoldMinerTests)

## c++11
set(CMAKE_CXX_STANDARD 11)

## compiler flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /Wall /EHsc")
endif()

file(GLOB src
        "./*.cpp"
        )
## find SFML 

add_executable(${PROJECT_NAME} ${src})