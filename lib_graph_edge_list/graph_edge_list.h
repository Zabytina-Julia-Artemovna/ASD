#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>

const int INF2 = INT_MAX;

class GraphEdgeList {
private:
    struct Edge {
        int from;
        int to;
        int weight;
    };

    std::vector<Edge> _edges;
    bool _is_oriented;
    bool _is_weighted;

public:
    GraphEdgeList(bool is_oriented, bool is_weighted);
    GraphEdgeList(std::vector<int> items, bool is_oriented, bool is_weighted);

    void add_edge(int from, int to, int weight = 1);
    void delete_edge(int from, int to);
    void delete_vertex(int vertex);
    int get_weight(int from, int to);
    void print() const noexcept;
};
