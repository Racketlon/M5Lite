#ifndef GESTURE_H
#define GESTURE_H

class Gesture {
public:
    enum SwipeDirection { NONE, LEFT, RIGHT, UP, DOWN };

    SwipeDirection direction;

    Gesture() : direction(NONE) {}

    static SwipeDirection detect_swipe() {
        // Placeholder for swipe detection logic
        return NONE;
    }
};

#endif
