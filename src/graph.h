#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <utility>

struct Vertex
{
    std::string ip;
    std::vector<int> adj;
    int indegree = 0;
};

class Graph
{
private:
    std::vector<Vertex> vertices;
    std::unordered_map<std::string, int> mapIPs;
    int numArestas;

public:
    Graph();

    // busca um IP e retorna seu índice.
    // caso não exista, cria um novo vértice.
    int obterIndiceIP(const std::string &ip);

    // busca sem criar vértice
    int buscarIndiceIP(const std::string &ip) const;

    std::vector<int> menorCaminho(
        const std::string &origem,
        const std::string &destino) const;

    // adiciona uma aresta direcionada
    void adicionarAresta(const std::string &origem,
                         const std::string &destino);

    // verifica se a aresta já existe
    bool arestaExiste(int origem, int destino) const;

    // getters
    int getNumVertices() const;
    int getNumArestas() const;

    // acesso aos vértices (útil para BFS e Graphviz)
    const std::vector<Vertex> &getVertices() const;

    //retorna o ip associado ao indice do vertice
    std::string obterIP(int indice) const;

    std::vector<std::pair<std::string, int>>
    topRoteadoresCriticos(int quantidade = 5) const;
};

#endif