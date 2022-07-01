#include "HeightMap.h"

HeightMap::HeightMap(int chunkX, int chunkZ, NoiseGenerator& noiseGenerator) {
    for (int x=0; x<16; x++) {
        std::vector<int> rowVec {};
        for (int z=0; z<16; z++) {
            int noiseHeight = noiseGenerator.GetHeight(x, z, chunkX, chunkZ);     
            if (noiseHeight >= 128) {
                noiseHeight = 127;
            }
            rowVec.push_back(noiseHeight);
        }
        heights.push_back(rowVec);
    }
}

int HeightMap::GetHeight(int x, int z) {
    return heights[x][z];
}
