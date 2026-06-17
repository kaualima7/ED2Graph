#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "graph.h"

void exibirGrafo();
void encontrarMenorCaminho();
void calcularDiametro();
void identificarRoteadoresCriticos();

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

    
    // teste da funcionalidade de menor caminho

    std::string origem;
    std::string destino;

    std::cout << "\nDigite o IP de origem: ";
    std::cin >> origem;

    std::cout << "Digite o IP de destino: ";
    std::cin >> destino;

    std::vector<int> caminho =
        grafo.menorCaminho(origem, destino);

    if (caminho.empty())
    {
        std::cout << "\nNenhum caminho encontrado.\n";
    }
    else
    {
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

    return 0;
}