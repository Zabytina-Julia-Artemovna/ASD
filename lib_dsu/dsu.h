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
