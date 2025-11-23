#pragma once 
#include <stdexcept>
class DSU {
private:
    int* _parent;
    int* _rank;
    size_t _size;
public:
    DSU(size_t size);
    DSU(const DSU& other);
    ~DSU();
    size_t size() const noexcept;
    int* parent() const noexcept;
    int* rank() const noexcept;
    void dsu_union(int x, int y);
    int dsu_find_recursive(int x);
    DSU& operator=(const DSU& other);
};
DSU::DSU(size_t size) {
    _size = size;
    _parent = new int[_size];
    _rank = new int[_size];
    for (size_t i = 0; i < _size; i++) {
        _parent[i] = i;
        _rank[i] = 0;
    }
}
DSU::DSU(const DSU& other) {
    _size = other._size;
    _parent = new int[_size];
    _rank = new int[_size];
    for (size_t i = 0; i < _size; i++) {
        this->_parent[i] = other._parent[i];
        this->_rank[i] = other._rank[i];
    }
}
DSU::~DSU() {
    delete[] _parent;
    delete[] _rank;
    _parent = nullptr;
    _rank = nullptr;
}
size_t DSU::size() const noexcept {
    return _size;
}
int* DSU::parent() const noexcept {
    return _parent;
}
int* DSU::rank() const noexcept {
    return _rank;
}
void DSU::dsu_union(int x, int y) {
    if (x == y) {
        return;
    }
    if (x >= _size || y >= _size || x < 0 || y < 0) {
        throw std::logic_error("Uncorrect arguments");
    }
    int parent_x = dsu_find_recursive(x);
    int parent_y = dsu_find_recursive(y);
    if (_rank[parent_x] < _rank[parent_y]) {
        _parent[parent_x] = parent_y;
    } else if (_rank[parent_x] > _rank[parent_y]) {
        _parent[parent_y] = parent_x;
    } else {
        _parent[parent_y] = parent_x;
        _rank[parent_x]++;
    }
}
int DSU::dsu_find_recursive(int x) {
    if (x >= _size || x < 0) {
        throw std::logic_error("Uncorrect argument");
    }
    if (_parent[x] == x) {
        return x;
    }
    return _parent[x] = dsu_find_recursive(_parent[x]);
}
DSU& DSU::operator=(const DSU& other) {
    if (this != &other) {
        delete[] _parent;
        delete[] _rank;
        _size = other._size;
        _parent = new int[_size];
        _rank = new int[_size];
        for (size_t i = 0; i < _size; i++) {
            this->_parent[i] = other._parent[i];
            this->_rank[i] = other._rank[i];
        }
    }
    return *this;
}
