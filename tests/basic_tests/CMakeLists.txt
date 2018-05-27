include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(shmup_tests basic_tests.cpp)

target_link_libraries(shmup_tests gtest gtest_main)
target_link_libraries(shmup_tests game)
