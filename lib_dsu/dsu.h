#pragma once 
class DSU {
private:
    int* _parent;
    size_t _size;
public:
    DSU(size_t size);
    DSU(const DSU& other);
    ~DSU();
    void dsu_union(int x, int y);
    int dsu_find(int x);
};