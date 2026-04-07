cmake_minimum_required(VERSION 3.16)
project(SnakeGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SnakeConsole snake_console.cpp)

# Build the SFML version only when the dependency is available.
find_package(SFML 2.5 COMPONENTS graphics window system QUIET)

if (SFML_FOUND)
    add_executable(SnakeGame main.cpp)
    target_link_libraries(SnakeGame PRIVATE sfml-graphics sfml-window sfml-system)
else()
    message(WARNING "SFML 2.5+ was not found. The SnakeGame target will be skipped; SnakeConsole is still available.")
endif()
