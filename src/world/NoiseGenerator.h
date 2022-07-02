#pragma once

#include <cmath>

class NoiseGenerator {
private:
    int octaves;
    int amplitude;
    int smoothness;
    int heightOffset;
    double roughness;

    int seed;

    double GetNoise(int n);
    double GetNoise(double x, double z);
    double Lerp(double a, double b, double z);
    double Noise(double x, double z);
public:
    NoiseGenerator(int seed);
    int GetSeed() { return seed; }
    double GetHeight(int x, int z, int chunkX, int chunkZ);
    double GetHeight(int x, int z);
};
