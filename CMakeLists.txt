cmake_minimum_required(VERSION 3.9)
project(shmup VERSION 0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -O3")

if (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -fsanitize=address,undefined,leak -O1 -fno-omit-frame-pointer")
else ()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic")
endif ()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(glm REQUIRED)
find_package(TinyXML2 REQUIRED)

include_directories(game)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR} ${TINYXML2_INCLUDE_DIR})

add_subdirectory(game)
add_subdirectory(assets)

#Game binary
add_executable(shmup main.cpp)

add_dependencies(shmup assets)

target_link_libraries(shmup game)

#Tests
enable_testing()

add_subdirectory(tests)

add_test(base_tests tests/base_tests/shmup_tests)