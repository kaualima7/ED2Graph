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

//procura ip que ja existe no grafo (n cria novos vertices)
int Graph::buscarIndiceIP(const std::string &ip) const
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].ip == ip)
        {
            return i;
        }
    }

    return -1;
}

//encontra o menor caminho entre dois ips usando a bfs
//retorna os indices dos vertices do caminho
std::vector<int> Graph::menorCaminho(
    const std::string &origem,
    const std::string &destino) const
{
    int idxOrigem = buscarIndiceIP(origem);
    int idxDestino = buscarIndiceIP(destino);
    if (idxOrigem == -1 || idxDestino == -1)
    {
        return {};
    }
    return{}; //temporario
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