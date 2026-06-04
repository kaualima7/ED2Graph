#ifndef GRAPH_H
#define GRAPH_H

//estrutura para representar um nó na lista de adjacências
typedef struct AdjNode { 
    int destino;
    struct AdjNode *prox;
} AdjNode;

//estrutura para representar um vértice do grafo
typedef struct Vertex { 
    char ip[16];
    AdjNode *listaAdj;
} Vertex;

//estrutura para representar o grafo
typedef struct Graph { 
    Vertex *vertices;
    int numVertices;
    int numArestas;
} Graph;

#endif