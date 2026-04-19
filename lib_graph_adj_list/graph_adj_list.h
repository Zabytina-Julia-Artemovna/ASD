#pragma once
#include <vector>
#include <iostream>
#include "../lib_list/List.h"
// edge ребро, vertex вершина
const int INF1 = INT_MAX;  

class GraphAdjList {
private:
    struct Neighbor {
        int vertex;      // КУДА идёт ребро
        int weight;    // вес ребра
    };
    std::vector<List<Neighbor>> _adj_list;
    bool _is_oriented = false;
    bool _is_weighted = false;
public:
    GraphAdjList() = default;
    GraphAdjList(std::vector<int> items, bool is_oriented, bool is_weighted);

    void add_edge(int from, int to, int weight = 1);
    void delete_edge(int from, int to);
    void delete_vertex(int vertex);

    int get_weight(int from, int to);
    void print() const noexcept;
};
