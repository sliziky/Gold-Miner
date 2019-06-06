cmake_minimum_required(VERSION 3.1)

project(GoldMiner)

## c++11
set(CMAKE_CXX_STANDARD 11)

## compiler flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GCC" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /Wall /EHsc")
endif()


set(SFML_DIR "C:/SFML-2.5.1-x64/lib/cmake/SFML")
set(PROJECT_SOURCE_DIR "C:/Users/Peter/Source/Repos/Gold-Miner/")

include_directories(
		${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)


file(GLOB src
        "${PROJECT_SOURCE_DIR}/include/*.h"
		"${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )

## find SFML 
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
add_executable(${PROJECT_NAME} ${src})
target_link_libraries(GoldMiner sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${SFML_DEPENDENCIES})