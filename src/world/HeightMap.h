#pragma once

#include "NoiseGenerator.h"
#include <vector>


class HeightMap {
private:
    std::vector<std::vector<int>> heights;

    int chunkZ;
    int chunkX;
public:
    HeightMap(int chunkX, int chunkZ, NoiseGenerator& noiseGenerator);
    
    int GetHeight(int x, int z);
};
