cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(M5Lite)

# Add FreeRTOS include path explicitly
include_directories($ENV{IDF_PATH}/components/freertos/include)
include_directories($ENV{IDF_PATH}/components/freertos/FreeRTOS-Kernel/include)
include_directories($ENV{IDF_PATH}/components/freertos/config/include)
