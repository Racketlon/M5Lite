#include "keyboard.h"
#include <iostream>

void keyboard_init() {
    std::cout << "[Keyboard] Driver initialized.\n";
}

bool keyboard_is_key_pressed(int key) {
    // Stub logic
    std::cout << "[Keyboard] Checking if key " << key << " is pressed...\n";
    return false;
}
