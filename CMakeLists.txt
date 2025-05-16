cmake_minimum_required(VERSION 3.10)

# Project name
project(SudokuGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add executable and source files
add_executable(sudoku_game main.cpp sudoko.cpp)
