#pragma once
#include "../lib_matrix/matrix.h"
#include <random>
#include <utility> 
template <class T>
std::pair<size_t, size_t> find_min_neighbor_coords(const Matrix<T>& matrix, size_t x, size_t y) {
    T min_val = matrix[x][y];
    size_t min_x = x;
    size_t min_y = y;
    if (x > 0 && matrix[x - 1][y] < min_val) {
        min_val = matrix[x - 1][y];
        min_x = x - 1;
        min_y = y;
    }
    if (x < matrix.getM() - 1 && matrix[x + 1][y] < min_val) {
        min_val = matrix[x + 1][y];
        min_x = x + 1;
        min_y = y;
    }
    if (y > 0 && matrix[x][y - 1] < min_val) {
        min_val = matrix[x][y - 1];
        min_x = x;
        min_y = y - 1;
    }
    if (y < matrix.getN() - 1 && matrix[x][y + 1] < min_val) {
        min_val = matrix[x][y + 1];
        min_x = x;
        min_y = y + 1;
    }
    return { min_x, min_y };
}
size_t getRandomIndex(size_t max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, max - 1);
    return dist(gen);
}
template <class T>
T find_local_minimum(const Matrix<T>& matrix) {
    size_t x = getRandomIndex(matrix.getM());
    size_t y = getRandomIndex(matrix.getN());

    while (true) {
        std::pair<size_t, size_t> min_coords = find_min_neighbor_coords(matrix, x, y);
        size_t new_x = min_coords.first;
        size_t new_y = min_coords.second;

        if (new_x == x && new_y == y) {
            return matrix[x][y];
        }

        x = new_x;
        y = new_y;
    }
}
