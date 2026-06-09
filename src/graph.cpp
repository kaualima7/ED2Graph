#include "graph.h"

Graph::Graph()
{
    numArestas = 0;
}

int Graph::obterIndiceIP(const std::string &ip)
{

    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].ip == ip)
        {
            return i;
        }
    }

    Vertex novo;
    novo.ip = ip;

    vertices.push_back(novo);

    return vertices.size() - 1;
}

bool Graph::arestaExiste(int origem, int destino) const
{

    for (int vizinho : vertices[origem].adj)
    {
        if (vizinho == destino)
        {
            return true;
        }
    }

    return false;
}

void Graph::adicionarAresta(const std::string &origem,
                            const std::string &destino)
{

    int idxOrigem = obterIndiceIP(origem);
    int idxDestino = obterIndiceIP(destino);

    if (!arestaExiste(idxOrigem, idxDestino))
    {
        vertices[idxOrigem].adj.push_back(idxDestino);
        numArestas++;
    }
}

int Graph::getNumVertices() const
{
    return vertices.size();
}

int Graph::getNumArestas() const
{
    return numArestas;
}

const std::vector<Vertex> &Graph::getVertices() const
{
    return vertices;
}