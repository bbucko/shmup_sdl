project(game)

file(GLOB CXX_SOURCES "*.cpp" "**/*.cpp" "*.h" "**/*.h")

add_library(game SHARED "${CXX_SOURCES}")

target_link_libraries(game tinyxml2 glm SDL2 SDL2_image)