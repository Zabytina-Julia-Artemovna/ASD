#include "graph_edge_list.h"

GraphEdgeList::GraphEdgeList(bool is_oriented, bool is_weighted)
    : _is_oriented(is_oriented), _is_weighted(is_weighted) {}

GraphEdgeList::GraphEdgeList(std::vector<int> items, bool is_oriented, bool is_weighted)
    : _is_oriented(is_oriented), _is_weighted(is_weighted)
{}

void GraphEdgeList::add_edge(int from, int to, int weight) {
    _edges.push_back({ from, to, weight });

    if (!_is_oriented) {
        _edges.push_back({ to, from, weight });
    }
}

void GraphEdgeList::delete_edge(int from, int to) {
    auto it = std::find_if(_edges.begin(), _edges.end(),
        [from, to](const Edge& e) {
            return e.from == from && e.to == to;
        });

    if (it != _edges.end()) {
        _edges.erase(it);
    }

    if (!_is_oriented) {
        auto it_reverse = std::find_if(_edges.begin(), _edges.end(),
            [from, to](const Edge& e) {
                return e.from == to && e.to == from;
            });
        if (it_reverse != _edges.end()) {
            _edges.erase(it_reverse);
        }
    }
}

void GraphEdgeList::delete_vertex(int vertex) {
    _edges.erase(
        std::remove_if(_edges.begin(), _edges.end(),
            [vertex](const Edge& e) {
                return e.from == vertex || e.to == vertex;
            }),
        _edges.end()
    );
}

int GraphEdgeList::get_weight(int from, int to) {
    auto it = std::find_if(_edges.begin(), _edges.end(),
        [from, to](const Edge& e) {
            return e.from == from && e.to == to;
        });

    if (it != _edges.end()) {
        return _is_weighted ? it->weight : 1;
    }
    return INF2;
}

void GraphEdgeList::print() const noexcept {
    if (_edges.empty()) {
        std::cout << "Нет ребер\n";
        return;
    }

    for (const auto& edge : _edges) {
        std::cout << edge.from << " -> " << edge.to;
        std::cout << "\n";
    }
}
