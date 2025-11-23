#pragma once 
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
    int dsu_find(int x);
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
