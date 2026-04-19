#include "graph_adj_list.h"
void GraphAdjList::add_edge(int from, int to, int weight) {
   
    Neighbor added;
    added.vertex = to;
    added.weight = weight;
    _adj_list[from].push_back(added);

}
void GraphAdjList::delete_edge(int from, int to) {
    if (from >= static_cast<int>(_adj_list.size())) {
        return;
    }

    for (auto it = _adj_list[from].begin(); it != _adj_list[from].end(); ) {
        if (it->vertex == to) {
            it = _adj_list[from].erase(it); 
            break;
        }
        else {
            ++it;
        }
    }
}
void GraphAdjList::delete_vertex(int vertex) {
    _adj_list[vertex].clear();

}
int GraphAdjList::get_weight(int from, int to) {
    for (const auto& nb : _adj_list[from]) {
        if (nb.vertex == to) {
            return _is_weighted ? nb.weight : 1;
        }
    }
    return INF1;
}
GraphAdjList::GraphAdjList(std::vector<int> items, bool is_oriented, bool is_weighted)
    : _is_oriented(is_oriented), _is_weighted(is_weighted)
{
    if (items.empty()) {
        return;
    }
    int max_vertex = items[0];
    for (int v : items) {
        if (v > max_vertex) {
            max_vertex = v;
        }
    }
    _adj_list.resize(max_vertex + 1);
}
void GraphAdjList::print() const noexcept {
    for (size_t i = 0; i < _adj_list.size(); ++i) {
        if (!_adj_list[i].is_empty()) {  
            std::cout << i << ": ";
            for (const auto& nb : _adj_list[i]) {
                std::cout << nb.vertex << " ";
            }
            std::cout << "\n";
        }
    }
}
