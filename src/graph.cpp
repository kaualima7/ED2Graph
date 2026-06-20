#include "graph.h"
#include <algorithm>
#include <fstream>

Graph::Graph()
{
    numArestas = 0;
}

int Graph::obterIndiceIP(const std::string &ip)
{
    auto it = mapIPs.find(ip);

    // ip ja existe
    if (it != mapIPs.end())
    {
        return it->second;
    }

    // cria novo vertice
    Vertex novo;
    novo.ip = ip;

    vertices.push_back(novo);

    int novoIndice = vertices.size() - 1;

    // registra no map
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

int Graph::bfsMaiorDistancia(int origem) const
{
    // mesma fila da bfs usada na função anterior
    std::queue<int> fila;

    // pra nao visitar o mesmo vertice duas vezes
    std::vector<bool> visitado(vertices.size(), false);

    // diferente de antes, agora armazena a distancia e nao o predecessor
    std::vector<int> distancia(vertices.size(), 0);

    visitado[origem] = true;
    fila.push(origem);

    int maiorDistancia = 0;

    while (!fila.empty())
    {
        int atual = fila.front();
        fila.pop();

        for (int vizinho : vertices[atual].adj)
        {
            if (!visitado[vizinho])
            {
                visitado[vizinho] = true;

                distancia[vizinho] =
                    distancia[atual] + 1;

                if (distancia[vizinho] > maiorDistancia)
                {
                    maiorDistancia = distancia[vizinho];
                }

                fila.push(vizinho);
            }
        }
    }

    return maiorDistancia;
}

int Graph::calcularDiametro() const
{
    int diametro = 0;
    for (int i = 0; i < vertices.size(); i++)
    {
        int distancia = bfsMaiorDistancia(i);

        if (distancia > diametro)
        {
            diametro = distancia;
        }
    }
    return diametro;
}

void Graph::exportarGraphviz(const std::string &nomeArquivo) const
{
    std::ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open())
    {
        return;
    }

    arquivo << "digraph G {\n";

    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].adj.empty())
        {
            arquivo << "    \""
                    << vertices[i].ip
                    << "\";\n";
        }

        for (int vizinho : vertices[i].adj)
        {
            arquivo << "    \""
                    << vertices[i].ip
                    << "\" -> \""
                    << vertices[vizinho].ip
                    << "\";\n";
        }
    }

    arquivo << "}\n";

    arquivo.close();
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
        vertices[idxDestino].indegree++;
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
    std::vector<std::pair<std::string, int>> resultado;

    for (int i = 0; i < vertices.size(); i++)
    {
        resultado.push_back(
            {vertices[i].ip,
             vertices[i].indegree});
    }

    std::sort(
        resultado.begin(),
        resultado.end(),
        [](const auto &a, const auto &b)
        {
            if (a.second != b.second)
            {
                return a.second > b.second;
            }

            return a.first < b.first;
        });

    if (resultado.size() > quantidade)
    {
        resultado.resize(quantidade);
    }

    return resultado;
}