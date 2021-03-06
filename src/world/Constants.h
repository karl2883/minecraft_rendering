#pragma once

namespace WorldConstants {
    constexpr int CHUNK_SIZE_XZ = 16;
    constexpr int CHUNK_SIZE_Y = 128;
    constexpr int CHUNK_LAYER_SIZE = CHUNK_SIZE_XZ * CHUNK_SIZE_Y;
    constexpr int CHUNK_VOLUME = CHUNK_LAYER_SIZE * CHUNK_SIZE_Y;

    constexpr int Y_OFFSET = -100;

    constexpr int RENDER_DISTANCE = 9;

    constexpr int FOG_END = (RENDER_DISTANCE-1) * CHUNK_SIZE_XZ;
    constexpr int FOG_START = FOG_END - 10;

    constexpr int WATER_LEVEL = 64;

    constexpr double TREE_ODDS = 1/200.0;
}
