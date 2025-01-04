#include "display.h"
#include <iostream>

void display_init() {
    std::cout << "[Display] Driver initialized.\n";
}

void display_clear() {
    std::cout << "[Display] Cleared.\n";
}

void display_draw_text(const char* text, int x, int y) {
    std::cout << "[Display] Drawing text '" << text << "' at (" << x << ", " << y << ")\n";
}
