cmake_minimum_required(VERSION 3.10)
project(shmup VERSION 0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include(CodeCoverage)
include(cotire)

#set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}} -O3 ")

if (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic")
    append_coverage_compiler_flags()
    #    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -fsanitize=address -O1 -fno-omit-frame-pointer")
elseif (APPLE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -fsanitize=address -O0 -fno-omit-frame-pointer")
endif ()

#set(CMAKE_VERBOSE_MAKEFILE true)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(glm REQUIRED)
find_package(TinyXML2 REQUIRED)
find_package(ZLIB REQUIRED)

include_directories(game)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR} ${TINYXML2_INCLUDE_DIR} ${ZLIB_INCLUDE_DIRS})

add_subdirectory(game)
add_subdirectory(assets)

#Game binary
add_executable(shmup main.cpp)

add_dependencies(shmup assets)

target_link_libraries(shmup game)

if (APPLE)
    cotire(shmup)
endif ()

message(STATUS "Release mode: ${CMAKE_BUILD_TYPE}")

#Tests
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS_DEBUG "-DINCLUDE_MOCKS")

    enable_testing()

    add_subdirectory(tests)

    add_test(base_tests tests/base_tests/shmup_tests)
endif (CMAKE_BUILD_TYPE MATCHES Debug)
