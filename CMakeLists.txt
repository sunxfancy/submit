cmake_minimum_required(VERSION 2.8)
project("submit")

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
endif()
conan_basic_setup()

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "2")
SET(VERSION_PATCH "0")

include_directories(src include)

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
