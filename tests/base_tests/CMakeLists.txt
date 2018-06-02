include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(shmup_tests StateParserTest.cpp)

add_dependencies(shmup_tests test_assets)

target_link_libraries(shmup_tests gtest gtest_main)
target_link_libraries(shmup_tests game)
