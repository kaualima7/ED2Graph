#include "graph.h"
#include <algorithm>

Graph::Graph()
{
    numArestas = 0;
}

int Graph::obterIndiceIP(const std::string &ip)
{
    auto it = mapIPs.find(ip);

    //ip ja existe
    if (it != mapIPs.end())
    {
        return it->second;
    }

    //cria novo vertice
    Vertex novo;
    novo.ip = ip;

    vertices.push_back(novo);

    int novoIndice = vertices.size() - 1;

    //registra no map
    mapIPs[ip] = novoIndice;

    return novoIndice;
}

// procura ip que ja existe no grafo (n cria novos vertices)
int Graph::buscarIndiceIP(const std::string &ip) const
{
    auto it = mapIPs.find(ip);

    if (it != mapIPs.end())
    {
        return it->second;
    }

    return -1;
}

// encontra o menor caminho entre dois ips usando a bfs
// retorna os indices dos vertices do caminho
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

    std::queue<int> fila;

    std::vector<bool> visitado(vertices.size(), false);

    std::vector<int> predecessor(vertices.size(), -1);

    visitado[idxOrigem] = true;
    fila.push(idxOrigem);

    bool encontrou = false; // variavel pra guardar quando achar, que fara parar o loop

    while (!fila.empty())
    {
        int atual = fila.front();
        fila.pop();

        if (atual == idxDestino)
        {
            encontrou = true; // uso da variavel pra indicar q achou o menor caminho
            break;
        }

        for (int vizinho : vertices[atual].adj)
        {
            // visita apenas vertices que ainda nao foram visitados
            if (!visitado[vizinho])
            {
                visitado[vizinho] = true;

                // guarda quem descobriu esse vertice
                predecessor[vizinho] = atual;

                fila.push(vizinho);
            }
        }
    }

    // se nao encontrou caminho entre origem e destino
    if (!encontrou)
    {
        return {};
    }

    std::vector<int> caminho;

    // reconstrucao do caminho usando o vetor predecessor
    for (int v = idxDestino; v != -1; v = predecessor[v])
    {
        caminho.push_back(v);
    }

    // inverte para ficar da origem ate o destino
    std::reverse(caminho.begin(), caminho.end());

    return caminho;
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

// retorna o IP associado ao indice do vertice
std::string Graph::obterIP(int indice) const
{
    return vertices[indice].ip;
}

std::vector<std::pair<std::string, int>>
Graph::topRoteadoresCriticos(int quantidade) const
{
    std::vector<int> grauEntrada(vertices.size(), 0);

    for (int i = 0; i < vertices.size(); i++)
    {
        for (int vizinho : vertices[i].adj)
        {
            grauEntrada[vizinho]++;
        }
    }

    std::vector<std::pair<std::string, int>> resultado;

    for (int i = 0; i < vertices.size(); i++)
    {
        resultado.push_back(
            {vertices[i].ip, grauEntrada[i]});
    }

    std::sort(
        resultado.begin(),
        resultado.end(),
        [](const auto &a, const auto &b)
        {
            return a.second > b.second;
        });

    if (resultado.size() > quantidade)
    {
        resultado.resize(quantidade);
    }

    return resultado;
}