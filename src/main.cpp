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
        std::cout << "0 - Sair\n";
        std::cout << "=============================\n";

        std::cout << "Escolha uma opção: ";
        std::getline(std::cin, opcao);

        if(opcao == "1"){

        } else if (opcao == "2"){
            encontrarMenorCaminho(grafo);
        } else if (opcao == "3"){

        } else if (opcao == "4"){

        } else if( opcao == "0"){
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

    menuPrincipal(grafo);

    return 0;
}