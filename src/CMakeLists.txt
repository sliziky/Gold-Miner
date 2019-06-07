cmake_minimum_required(VERSION 3.8)

project(GoldMiner)

## c++17
set(CMAKE_CXX_STANDARD 17)

## compiler flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror -std=c++17")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /Wall /EHsc /std:c++17")
endif()



if (WIN32)
    set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../SFML-2.5.1-x64/lib/cmake/SFML)
endif (WIN32)

if (UNIX)
    set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../SFML-2.5.1/lib/cmake/SFML)
endif (UNIX)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

include_directories(
		${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
		${PROJECT_SOURCE_DIR}/thirdparty
)


file(GLOB src
        "${PROJECT_SOURCE_DIR}/include/*.h"
	    "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
		"${PROJECT_SOURCE_DIR}/thirdparty/animation/src/*.cpp"
		"${PROJECT_SOURCE_DIR}/thirdparty/animation/src/*.h"
        )

## find SFML 
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
add_executable(${PROJECT_NAME} ${src})
target_link_libraries(GoldMiner sfml-system sfml-window sfml-graphics sfml-network sfml-audio ${SFML_DEPENDENCIES})
