#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "graph.h"

void exibirGrafo(const Graph &grafo);
void encontrarMenorCaminho(const Graph &grafo);
void calcularDiametro(const Graph &grafo);
void identificarRoteadoresCriticos(const Graph &grafo);

void exibirGrafo(const Graph &grafo)
{
    const auto &vertices = grafo.getVertices();

    std::cout << "\n=== Grafo de Roteamento ===\n\n";

    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << vertices[i].ip << " -> ";

        if (vertices[i].adj.empty())
        {
            std::cout << "(sem conexoes)";
        }
        else
        {
            for (int j = 0; j < vertices[i].adj.size(); j++)
            {
                std::cout << grafo.obterIP(vertices[i].adj[j]);

                if (j < vertices[i].adj.size() - 1)
                {
                    std::cout << ", ";
                }
            }
        }

        std::cout << "\n";
    }

    std::cout << "\nTotal de vertices: "
              << grafo.getNumVertices()
              << "\nTotal de arestas: "
              << grafo.getNumArestas()
              << "\n";
}

void encontrarMenorCaminho(const Graph &grafo)
{
    std::string origem;
    std::string destino;

    std::cout << "\nDigite o IP de origem: ";
    std::getline(std::cin, origem);

    std::cout << "Digite o IP de destino: ";
    std::getline(std::cin, destino);

    std::vector<int> caminho =
        grafo.menorCaminho(origem, destino);

    if (caminho.empty())
    {
        std::cout << "\nNenhum caminho encontrado.\n";
        return;
    }

    std::cout << "\nCaminho encontrado ("
              << caminho.size() - 1
              << " saltos):\n";

    for (int i = 0; i < caminho.size(); i++)
    {
        std::cout << grafo.obterIP(caminho[i]);

        if (i < caminho.size() - 1)
        {
            std::cout << " -> ";
        }
    }

    std::cout << "\n";
}

void calcularDiametro(const Graph &grafo)
{
    int diametro = grafo.calcularDiametro();

    std::cout << "\nDiametro da rede: "
              << diametro
              << " saltos\n";
}

void identificarRoteadoresCriticos(const Graph &grafo)
{
    auto top = grafo.topRoteadoresCriticos();

    std::cout << "\nTop 5 roteadores críticos:\n\n";

    for (const auto &item : top)
    {
        std::cout
            << item.first
            << " | Grau de Entrada: "
            << item.second
            << "\n";
    }
}

void menuPrincipal(const Graph &grafo)
{
    std::string opcao;

    do
    {
        std::cout << "\n=============================\n";
        std::cout << "1 - Exibir Grafo\n";
        std::cout << "2 - Menor caminho\n";
        std::cout << "3 - Diâmetro\n";
        std::cout << "4 - Roteadores Críticos\n";
        std::cout << "5 - Exportar Graphviz\n";
        std::cout << "0 - Sair\n";
        std::cout << "=============================\n";

        std::cout << "Escolha uma opção: ";
        std::getline(std::cin, opcao);

        if (opcao == "1")
        {
            exibirGrafo(grafo);
        }
        else if (opcao == "2")
        {
            encontrarMenorCaminho(grafo);
        }
        else if (opcao == "3")
        {
            calcularDiametro(grafo);
        }
        else if (opcao == "4")
        {
            identificarRoteadoresCriticos(grafo);
        }
        else if (opcao == "5")
        {
            grafo.exportarGraphviz("rede.dot");

            std::cout
                << "\nArquivo rede.dot gerado com sucesso.\n";
        }
        else if (opcao != "0")
        {
            std::cout << "\nOpção inválida\n";
        }

    } while (opcao != "0");
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        std::cout << "Uso: " << argv[0] << " <arquivo.log>\n";
        return 1;
    }

    std::ifstream arquivo(argv[1]);

    if (!arquivo.is_open())
    {
        std::cout << "Erro ao abrir arquivo " << argv[1] << "\n";
        return 1;
    }

    std::cout << "Carregando arquivo " << argv[1] << "...\n";

    Graph grafo;

    std::string linha;

    // ignora o cabeçalho
    std::getline(arquivo, linha);

    while (std::getline(arquivo, linha))
    {

        if (linha.empty())
        {
            continue;
        }

        std::stringstream ss(linha);

        std::vector<std::string> campos;
        std::string campo;

        while (std::getline(ss, campo, ','))
        {
            campos.push_back(campo);
        }

        // formato esperado:
        // prb_id,probe_src,dst_addr,hop,hop_from,hop_to,rtt

        if (campos.size() < 7)
        {
            continue;
        }

        std::string hop_from = campos[4];
        std::string hop_to = campos[5];

        // sanitização
        if (hop_from.empty() || hop_to.empty())
        {
            continue;
        }

        if (hop_to == "*")
        {
            continue;
        }

        grafo.adicionarAresta(hop_from, hop_to);
    }

    arquivo.close();

    std::cout << "\nGrafo de roteamento inicializado!\n";
    std::cout << "Vertices unicos (IPs): "
              << grafo.getNumVertices()
              << " | Arestas: "
              << grafo.getNumArestas()
              << "\n";

    menuPrincipal(grafo);

    return 0;
}