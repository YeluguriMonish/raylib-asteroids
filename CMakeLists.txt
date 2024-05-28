set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.29.1)

project(raylib-asteroids)

# where is the flecs source file?
add_library(flecs STATIC lib/flecs/flecs.c)
# where is the flecs header file?
# PUBLIC makes sure that we can include flecs in main.cpp
target_include_directories(flecs PUBLIC lib/flecs)

find_package(raylib REQUIRED)

add_executable(asteroids src/main.cpp src/systems/systems.cpp src/entities/entities.cpp src/utils/utils.cpp src/globals/globals.cpp)
target_link_libraries(asteroids raylib flecs)
# where is the systems header file?
# PRIVATE indicates that the systems header file will only be linked to asteroids and no other executable will link asteroids
target_include_directories(asteroids PRIVATE src/systems src/components src/entities src/utils src/globals)

set_target_properties(asteroids PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
