# ED2Graph

Trabalho desenvolvido para a disciplina de Estruturas de Dados II.

## Descrição

O ED2Graph é uma aplicação desenvolvida em C++ para análise de rotas de rede utilizando grafos direcionados construídos a partir de logs de traceroute.

A aplicação processa arquivos contendo informações sobre saltos de roteamento entre endereços IP e constrói uma representação em grafo da topologia observada. A partir dessa estrutura, são realizadas análises de conectividade e características estruturais da rede.

---

## Funcionalidades

- Construção automática de grafos direcionados a partir de logs de traceroute;
- Exibição da estrutura do grafo;
- Cálculo do menor caminho entre dois endereços IP utilizando Busca em Largura (BFS);
- Cálculo do diâmetro da rede;
- Identificação dos roteadores mais críticos com base no grau de entrada;
- Exportação do grafo para o formato Graphviz (.dot), permitindo visualização externa da topologia da rede.

---

## Estrutura do projeto

```text
ED2Graph/
│
├── src/
│   ├── main.cpp
│   ├── graph.cpp
│   └── graph.h
│
├── inputs/
│   ├── input_1.log
│   ├── input_2.log
│   └── input_3.log
│
└── README.md
```

---

## Compilação

```bash
g++ src/main.cpp src/graph.cpp -o ED2Graph
```

---

## Execução

```bash
./ED2Graph inputs/input_1.log
```

---

## Menu de Operações

Ao executar o programa, o usuário terá acesso às seguintes opções

```text
1 - Exibir Grafo
2 - Menor caminho
3 - Diâmetro
4 - Roteadores Críticos
5 - Exportar Graphviz
0 - Sair
```

---

## Visualização com Graphviz

A opção Exportar Graphviz gera um arquivo chamado rede.dot.

Para converter esse arquivo em PDF:

```bash
dot -Tpdf rede.dot -o rede.pdf
```

ou

```bash
sfdp -Tpdf rede.dot -o rede.pdf
```

---

## Estruturas de Dados Utilizadas

---

## Lista de Adjacência

O grafo foi implementado utilizando listas de adjacência, permitindo economia de memória e eficiência para representar redes esparsas.

---

## Tabela Hash

Os endereços IP são armazenados em uma estrutura unordered_map, possibilitando acesso rápido aos vértices através do endereço IP.

---

## Algoritmos Utilizados

---

## Busca em Largura (BFS)

Utilizada para:

- Encontrar o menor caminho entre dois vértices;
- Calcular distâncias mínimas na rede;
- Auxiliar no cálculo do diâmetro do grafo.

---

## Cálculo do Diâmetro

O diâmetro é obtido executando BFS a partir de cada vértice e registrando a maior distância encontrada.

---

## Identificação de Roteadores Críticos

Os roteadores críticos são determinados através do grau de entrada (indegree), indicando quantas conexões chegam a cada vértice.

---

## Formato dos Dados de Entrada

Os arquivos de entrada seguem o formato:

```csv
prb_id,probe_src,dst_addr,hop,hop_from,hop_to,rtt
```

Durante a leitura, são utilizados principalmente os campos:

- hop_from
- hop_to

Cada par gera uma aresta direcionada no grafo.

---

## Requisitos Implementados

- [x] Construção do grafo
- [x] Busca do menor caminho (BFS)
- [x] Cálculo do diâmetro
- [x] Identificação de roteadores críticos
- [x] Exportação para Graphviz
- [x] Interface interativa por menu

---

## Complexidade

### Menor Caminho (BFS)

Tempo: O(V + E)

### Cálculo do Diâmetro

Tempo: O(V × (V + E))

pois uma BFS é executada a partir de cada vértice.

### Roteadores Críticos

Tempo: O(V log V)

devido à ordenação dos vértices pelo grau de entrada.

---

## Autores

- Kauã Lima Rodrigues
- Gabriel Furigo Knopf

---

### Informações Acadêmicas

- Curso: Ciência da Computação - UPF
- Disciplina: Estrutura de Dados II
- Professor: Marcos Jose Brusso

---

*Este trabalho foi desenvolvido como requisito para a disciplina Estrutura de Dados II da UPF.*

