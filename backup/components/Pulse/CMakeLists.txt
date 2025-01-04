# components/Pulse/CMakeLists.txt

# Create a library for Pulse
add_library(PulseLib STATIC
    src/button.cpp
    src/input.cpp
    src/label.cpp
    src/parser.cpp
    src/system.cpp
    compiler.cpp
    debugger.cpp
)

# Include directories
target_include_directories(PulseLib PUBLIC include)

# Optionally, build the Pulse compiler as an executable
add_executable(pulse-compiler compiler.cpp src/parser.cpp src/input.cpp src/button.cpp src/label.cpp src/system.cpp)
target_include_directories(pulse-compiler PUBLIC include)

# Link libraries if necessary (e.g., UI framework)
# find_package(Qt5 COMPONENTS Widgets REQUIRED)
# target_link_libraries(PulseLib PRIVATE Qt5::Widgets)

# Install targets if necessary
install(TARGETS PulseLib pulse-compiler
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)

# Add system.cpp to PulseLib
target_sources(PulseLib PRIVATE src/system.cpp)

# If building the compiler as an executable
target_sources(pulse-compiler PRIVATE src/system.cpp)