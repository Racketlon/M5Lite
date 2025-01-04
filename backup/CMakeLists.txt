cmake_minimum_required(VERSION 3.16)

# Include the ESP-IDF build system
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# Specify additional component directories
set(EXTRA_COMPONENT_DIRS 
    components/Apps 
    components/Drivers 
    components/Pulse 
    components/System
)

# Set the project name
project(M5PaperOS)
