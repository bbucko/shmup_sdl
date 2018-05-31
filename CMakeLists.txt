cmake_minimum_required(VERSION 3.9)
project(shmup VERSION 0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(glm REQUIRED)

include_directories(game)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR})

add_subdirectory(game)
add_subdirectory(res)

#Game binary
add_executable(shmup main.cpp)

add_dependencies(shmup resources)

target_link_libraries(shmup game)

#Tests
add_subdirectory(tests)

enable_testing()
add_test(basic_tests tests/basic_tests/shmup_tests)