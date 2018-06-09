include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(shmup_tests mocks/Mocks.h StateParserTest.cpp LevelParserTest.cpp TileLayerTest.cpp)

add_dependencies(shmup_tests test_assets)

target_link_libraries(shmup_tests gtest gmock gtest_main)
target_link_libraries(shmup_tests game)

#set(COVERAGE_EXCLUDES "tests/*" "/usr/include/*" "v1/*")

setup_target_for_coverage(
     NAME coverage
     EXECUTABLE shmup_tests -j ${PROCESSOR_COUNT}
     DEPENDENCIES shmup_tests
 )
