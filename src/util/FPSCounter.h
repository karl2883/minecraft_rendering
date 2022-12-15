#pragma once

#include <iostream>

class FPSCounter {
public:
    FPSCounter();
    void tick(float deltaTime);
private:
    float time_since_last_print;
    int frames_since_last_print;
};
