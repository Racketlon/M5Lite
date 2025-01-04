// components/Pulse/src/system.cpp

#include "../include/system.h"
#include <array>
#include <memory>
#include <stdexcept>
#include <cstdio>

std::string System::execute(const std::string& command) {
    std::array<char, 128> buffer;
    std::string result;

    // Open pipe to file
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    // Read till end of process:
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}
