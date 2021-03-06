file(GLOB resources "*.png" "*.jpg" "*.xml" "*.tmx" "*.tsx")

foreach (resource IN LISTS resources)
    get_filename_component(FILE_NAME ${resource} NAME)
    message(STATUS "Copying ${resource} to ${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME}")

    add_custom_command(
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${resource}"
            COMMAND ${CMAKE_COMMAND} -E copy "${resource}" "${CMAKE_CURRENT_BINARY_DIR}"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME}"
    )
    set(resources_dep ${resources_dep} ${FILE_NAME})
endforeach ()

add_custom_target(assets ALL DEPENDS "${resources_dep}")