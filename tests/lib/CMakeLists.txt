project(shmup_tests_lib)

add_subdirectory(googletest)

target_compile_options(gtest PUBLIC "-pthread" "-w")
