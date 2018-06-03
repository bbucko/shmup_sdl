file(GLOB test_assets "*.png" "*.jpg" "*.xml")

foreach (resource IN LISTS test_assets)
    get_filename_component(FILE_NAME ${resource} NAME)
    message(STATUS "Copying test ${resource} to /tmp/shmup_tests/${FILE_NAME}")

    add_custom_command(
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${resource}"
            COMMAND ${CMAKE_COMMAND} -E copy "${resource}" "/tmp/shmup_tests/${FILE_NAME}"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME}"
    )
    set(resources_dep ${resources_dep} ${FILE_NAME})
endforeach ()

add_custom_target(test_assets ALL DEPENDS "${resources_dep}")