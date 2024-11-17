# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(ChessLayoutEngine)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for headers
include_directories(
    boards
    engine
    pieces
)

# Add source files
file(GLOB BOARD_SOURCES boards/*.cpp)
file(GLOB ENGINE_SOURCES engine/*.cpp)
file(GLOB PIECE_SOURCES pieces/*.cpp)
file(GLOB MAIN_SOURCE main.cpp)

# Combine all source files
set(SOURCES
    ${BOARD_SOURCES}
    ${ENGINE_SOURCES}
    ${PIECE_SOURCES}
    ${MAIN_SOURCE}
)

# Add the executable
add_executable(ChessLayoutEngine ${SOURCES})

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Link SFML libraries to your executable
target_link_libraries(ChessLayoutEngine sfml-graphics sfml-window sfml-system)
