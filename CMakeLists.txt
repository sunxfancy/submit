cmake_minimum_required(VERSION 2.8)
project("submit")

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
endif()
conan_basic_setup()

set(VERSION_MAJOR "0")
set(VERSION_MINOR "3")
set(VERSION_PATCH "0")

configure_file (
    "${PROJECT_SOURCE_DIR}/include/config.h.in"
    "${PROJECT_BINARY_DIR}/config/config.h"
)

include_directories(src include ${PROJECT_BINARY_DIR}/config)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

if (UNIX)
    SET (CMAKE_CXX_COMPILER clang++)
    SET (CMAKE_CXX_FLAGS "-std=c++11")
    SET (CMAKE_CXX_FLAGS_DEBUG "-g")
    SET (CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")
endif()

if(UNIX AND NOT APPLE)
	message(STATUS ">>> Linux & link static gcc")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()


file(GLOB_RECURSE source_files
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    )
list(REMOVE_ITEM  source_files  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)


# 生成库目标
add_library(${PROJECT_NAME} ${source_files})
add_executable("sub" ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries("sub" ${PROJECT_NAME})

add_subdirectory(doc)
add_subdirectory(test)
