cmake_minimum_required(VERSION 3.16)

# Include ESP-IDF's project.cmake
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# Project name
project(M5Paper)

# Add subdirectories
add_subdirectory(core)
add_subdirectory(screen)
add_subdirectory(lib)
add_subdirectory(pulse)
