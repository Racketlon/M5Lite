// components/Pulse/include/system.h

#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>

class System {
public:
    // Executes a system command and returns the output
    static std::string execute(const std::string& command);
};

#endif // SYSTEM_H
