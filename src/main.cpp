#include <iostream>
#include <fstream>
#include "graph.h"

void exibirGrafo();
void encontrarMenorCaminho();
void calcularDiametro();
void identificarRoteadoresCriticos();

int main(int argc, char *argv[]){

    if (argc != 2){ 
        std::cout << "Uso: " << argv[0] << " <arquivo.log>\n";
        return 1;
    }

    std::ifstream arquivo(argv[1]);

    if (!arquivo.is_open()){
        std::cout << "Erro ao abrir arquivo " << argv[1] << "\n";
        return 1;   
    }

    std::cout << "Carregando arquivo " << argv[1] << "...\n";

    // TODO:
    // - Ler arquivo de entrada 
    // - Construir lista de adjacência
    // - Contar vértices e arestas

    arquivo.close();

    std::cout << "Grafo de roteamento inicializado\n";

    return 0;
}