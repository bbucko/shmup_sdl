 set(resources shooter/1945.png)

 foreach (item IN LISTS resources)
     message(STATUS "Adding ${CMAKE_CURRENT_BINARY_DIR}/${item}")
     add_custom_command(
             OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
             COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
             DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
     )
 endforeach ()

 add_custom_target(resources ALL DEPENDS "${resources}")