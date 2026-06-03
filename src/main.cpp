#include <stdio.h>
#include <stdlib.h>

void exibirGrafo();
void encontrarMenorCaminho();
void calcularDiametro();
void identificarRoteadoresCriticos();

int main(int argc, char *argv[]){

    if (argc != 2){ //verifica argumento da linha de comando
        printf("Uso: %s <arquivo.log>\n", argv[0]);
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r"); //tenta abrir o arquivo

    if (arquivo == NULL){ //verifica se o arquivo foi aberto com sucesso
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;   
    }

    printf("Carregando arquivo %s...\n", argv[1]);

    // TODO:
    // - Ler arquivo de entrada 
    // - Construir lista de adjacência
    // - Contar vértices e arestas

    fclose(arquivo);

    printf("Grafo de roteamento inicializado!\n");

    return 0;
}