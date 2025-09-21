# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(MyProject)

# Set the C++ standard (e.g., C++11, C++14, C++17, etc.)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# List all your source files in a variable
set(SOURCES
        Main.cpp
        LesData3.cpp
        Global.cpp
        Kunder.cpp
        Kunde.cpp
        Soner.cpp
        Sone.cpp
        Bolig.cpp
        Enebolig.cpp
)

# Create an executable using the specified source files
add_executable(MyExecutable ${SOURCES})
