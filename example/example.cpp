#include "grphx/grphx.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    grphx::undirected_graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2);

    if(graph.contains_edge(1, 2)) {
        std::cout << "Vertex 1 and 2 share an edge!" << std::endl;
    }

    return 0;
}