#include "touch.h"
#include <iostream>

void touch_init() {
    std::cout << "[Touch] Driver initialized.\n";
}

bool touch_read_coordinates(int* x, int* y) {
    // Example stub
    *x = 100;
    *y = 200;
    std::cout << "[Touch] Read coordinates: (" << *x << ", " << *y << ")\n";
    return true;
}
