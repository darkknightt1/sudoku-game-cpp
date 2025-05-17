cmake_minimum_required(VERSION 3.10)

# Project name
project(SudokuGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Add include directories
include_directories(include)

# Tell CMake where Qt is
#set(CMAKE_PREFIX_PATH "E:/APPS/QT/6.7.0/mingw_64/lib/cmake")

# Find Qt components
#find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Add executable and source files
add_executable(sudoku_game main.cpp src/sudoko.cpp)

# Link Qt libraries
#target_link_libraries(sudoku_game PRIVATE Qt6::Widgets)
