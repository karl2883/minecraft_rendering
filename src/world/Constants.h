#pragma once

namespace WorldConstants {
    constexpr int CHUNK_SIZE_XZ = 16;
    constexpr int CHUNK_SIZE_Y = 128;
    constexpr int CHUNK_LAYER_SIZE = CHUNK_SIZE_XZ * CHUNK_SIZE_Y;
    constexpr int CHUNK_VOLUME = CHUNK_LAYER_SIZE * CHUNK_SIZE_Y;

    constexpr int Y_OFFSET = -100;

    constexpr int RENDER_DISTANCE = 6;

    constexpr double TREE_ODDS = 1/200.0;
}
