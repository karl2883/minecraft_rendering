#include "FPSCounter.h"

FPSCounter::FPSCounter() {
    frames_since_last_print = 0;
    time_since_last_print = 0.0f;
}

// prints the FPS of the last second
void FPSCounter::tick(float deltaTime) {
    frames_since_last_print++;
    time_since_last_print += deltaTime;

    if (time_since_last_print > 1.0f) {
        std::cout << (frames_since_last_print*(1.0f/time_since_last_print)) << " FPS" << std::endl;
        frames_since_last_print = 0;
        time_since_last_print -= 1.0f;
    }
}
