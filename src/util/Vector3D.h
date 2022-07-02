#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <ostream>
#include <vector>

template <class T>
class Vector3D {
private:
    std::vector<std::vector<std::vector<T>>> data;
public:
    Vector3D(glm::vec3& size, T fill_value) {
        for (int x=0; x<size.x; x++) {
            std::vector<std::vector<T>> new_layer {};
            for (int y=0; y<size.y; y++) {
                std::vector<T> new_row {};
                for (int z=0; z<size.z; z++) {
                    new_row.push_back(fill_value); 
                }
                new_layer.push_back(new_row);
            }
            data.push_back(new_layer);
        }
    }

    T Get(int x, int y, int z) {
        return data[x][y][z];
    }

    void Set(int x, int y, int z, T value) {
        data[x][y][z] = value;
    }
};
