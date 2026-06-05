#include "graph.h"

Graph::Graph() {
    numArestas = 0;
}

int Graph::getNumVertices() const {
    return vertices.size();
}

int Graph::getNumArestas() const {
    return numArestas;
}