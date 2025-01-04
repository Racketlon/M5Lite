#include "storage.h"
#include <iostream>
#include <cstring>

bool storage_init() {
    // e.g. Initialize SPIFFS or SD card
    std::cout << "[Storage] Initialized.\n";
    return true;
}

bool storage_save_file(const char* filename, const char* data) {
    std::cout << "[Storage] Saving to file " << filename << " data: " << data << "\n";
    // Stub success
    return true;
}

bool storage_load_file(const char* filename, char* outData, int maxLen) {
    std::cout << "[Storage] Loading file " << filename << "\n";
    // Stub data
    std::strncpy(outData, "Stub content", maxLen);
    return true;
}
