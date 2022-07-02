#include "NoiseGenerator.h"

NoiseGenerator::NoiseGenerator(int seedx) {
    seed = seedx;

    octaves = 7;
    amplitude = 35;
    smoothness = 130;
    heightOffset = 20;
    roughness = 0.6;
}

// bit hacks no clue how this works
double NoiseGenerator::GetNoise(int n) {
    n += seed;
    n = (n << 13) ^ n;
    auto newN = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;

    return 1.0 - ((double)newN / 1073741824.0); 
}

double NoiseGenerator::GetNoise(double x, double z) {
    return GetNoise(x + z * 57);
}

double NoiseGenerator::Lerp(double a, double b, double z) {
    double mu2 = (1 - std::cos(z * 3.14)) / 2;
    return (a * (1 - mu2) + b * mu2);
}

double NoiseGenerator::Noise(double x, double z) {
    double floorX = std::floor(x); 
    double floorZ = std::floor(z);

    double a = GetNoise(floorX, floorZ);
    double b = GetNoise(floorX+1, floorZ);
    double c = GetNoise(floorX, floorZ+1);
    double d = GetNoise(floorX+1, floorZ+1);

    double rec1 = Lerp(a, b, x-floorX);
    double rec2 = Lerp(c, d, x-floorX);
    double rec3 = Lerp(rec1, rec2, z-floorZ);
    return rec3;
}

double NoiseGenerator::GetHeight(int x, int z, int chunkX, int chunkZ) {
    return GetHeight(x + chunkX, z + chunkZ);
}

double NoiseGenerator::GetHeight(int x, int z) {
    double totalValue = 0.0f;

    for (int octave=0; octave<octaves-1; octave++) {
        double frequency = std::pow(2.0, octave);
        double octaveAmplitude = std::pow(roughness, octave);
        totalValue += Noise(((double)x) * frequency / smoothness, ((double)z) * frequency / smoothness) * octaveAmplitude;
    }

    int value = (((totalValue/2.1) + 1.2) * amplitude) + heightOffset;
    return value > 0 ? value : 1;
}

