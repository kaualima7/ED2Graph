#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

struct Vertex {
    std::string ip;
    std::vector<int> adj;
};

class Graph {
private:
    std::vector<Vertex> vertices;
    int numArestas;

public:
    Graph();

    int obterIndiceIP(const std::string& ip);

    void adicionarAresta(const std::string& origem,
                         const std::string& destino);

    bool arestaExiste(int origem, int destino) const;

    int getNumVertices() const;
    int getNumArestas() const;
};

#endif