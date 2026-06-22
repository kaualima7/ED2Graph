# ED2Graph

Trabalho desenvolvido para a disciplina de Estrutura de Dados II do curso de Ciência da Computação da Universidade de Passo Fundo (UPF).

## Descrição

O ED2Graph é uma aplicação desenvolvida em C++ para análise de rotas de rede a partir de arquivos de traceroute.
O programa realiza a leitura dos logs fornecidos, constrói um grafo direcionado representando a topologia observada da rede e disponibiliza funcionalidades para análise e visualização dessa estrutura.
A partir do grafo gerado, é possível identificar caminhos entre roteadores, calcular características da rede e gerar representações visuais utilizando o Graphviz.

---

## Funcionalidades

O sistema oferece as seguintes funcionalidades:

- Construção automática do grafo a partir dos arquivos de entrada;
- Exibição da estrutura do grafo em formato de lista de adjacência;
- Cálculo do menor caminho entre dois endereços IP utilizando Busca em Largura (BFS);
- Cálculo do diâmetro da rede;
- Identificação dos roteadores mais críticos com base no grau de entrada;
- Visualização gráfica da rede utilizando Graphviz;
- Exportação do grafo para os formatos DOT, PNG e PDF;
- Visualização do menor caminho com destaque visual;
- Interface interativa baseada em menus.

---

## Estrutura do Projeto

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

Para compilar o projeto:

```bash
g++ src/main.cpp src/graph.cpp -o ED2Graph
```

---

## Execução

Após a compilação:

```bash
./ED2Graph inputs/input_1.log
```

Também podem ser utilizados:

```bash
./ED2Graph inputs/input_2.log
```

ou

```bash
./ED2Graph inputs/input_3.log
```

---

## Menu Principal

Ao iniciar a aplicação, o usuário terá acesso ao seguinte menu:

```text
1 - Exibir Grafo
2 - Menor Caminho
3 - Diâmetro
4 - Roteadores Críticos
5 - Visualização Graphviz
0 - Sair
```

### Exibir Grafo

Mostra a estrutura do grafo em formato de lista de adjacência, exibindo os vértices e suas conexões.

### Menor Caminho

Solicita um IP de origem e um IP de destino e utiliza BFS para encontrar o caminho com menor número de saltos entre eles.

O resultado é exibido no terminal juntamente com a quantidade de saltos percorridos.

### Diâmetro

Calcula a maior distância mínima existente entre dois vértices da rede.

### Roteadores Críticos

Exibe os cinco roteadores com maior grau de entrada, indicando os pontos mais relevantes da rede.

### Visualização Graphviz

Disponibiliza recursos de visualização gráfica da rede.

---

## Visualização com Graphviz

Ao acessar a opção de visualização, o usuário encontra o seguinte menu:

```text
1 - Grafo Completo
2 - Menor Caminho
0 - Voltar
```

### Formatos Disponíveis

Para cada visualização, estão disponíveis os seguintes formatos:

```text
1 - Tela
2 - PNG
3 - PDF
0 - Voltar
```

---

## Grafo Completo

Permite visualizar toda a topologia da rede.

Arquivos gerados:

```text
rede.dot
rede.png
rede.pdf
```

As opções disponíveis são:

- Visualização direta na tela;
- Geração de imagem PNG;
- Geração de arquivo PDF.

---

## Visualização do Menor Caminho

Após o cálculo do menor caminho, o programa pode gerar uma visualização destacando a rota encontrada dentro do grafo completo.
Os vértices pertencentes ao caminho são destacados em dourado e as arestas da rota são destacadas em vermelho, facilitando a identificação visual da sequência de saltos.

Arquivos gerados:

```text
menor_caminho.dot
menor_caminho.png
menor_caminho.pdf
```

---

## Dependências

Para utilizar os recursos gráficos é necessário possuir o Graphviz instalado no sistema.
Exemplos de comandos utilizados:

```bash
dot -Tx11 rede.dot
dot -Tpng rede.dot -o rede.png
dot -Tpdf rede.dot -o rede.pdf
```

Em sistemas Linux, a abertura automática de arquivos é realizada através do comando:

```bash
xdg-open
```

---

## Estruturas de Dados Utilizadas

### Lista de Adjacência

O grafo foi implementado utilizando lista de adjacência.
Essa estrutura foi escolhida por ser mais eficiente para representar redes esparsas, consumindo menos memória do que uma matriz de adjacência e permitindo percorrer apenas as conexões existentes.

### Tabela Hash (`unordered_map`)

Os endereços IP são armazenados em uma tabela hash utilizando a estrutura `unordered_map`.
Essa abordagem permite localizar rapidamente os vértices associados a cada IP, reduzindo significativamente o custo das buscas durante a construção e utilização do grafo.

---

## Algoritmos Utilizados

### Busca em Largura (BFS)

A BFS é utilizada para:

- Encontrar o menor caminho entre dois IPs;
- Determinar a quantidade mínima de saltos;
- Auxiliar no cálculo do diâmetro da rede.

### Cálculo do Diâmetro

O diâmetro é obtido executando uma BFS a partir de cada vértice do grafo e registrando a maior distância encontrada.

### Identificação de Roteadores Críticos

Os roteadores críticos são determinados através do grau de entrada (*indegree*), que representa a quantidade de conexões recebidas por cada vértice.
Após o cálculo dos graus, os vértices são ordenados para identificação dos mais relevantes.

---

## Justificativa das Escolhas de Implementação

A utilização de lista de adjacência foi escolhida por representar melhor redes reais, onde normalmente o número de conexões é muito menor que o número máximo possível de ligações entre vértices.
Para a busca do menor caminho foi utilizada a Busca em Largura (BFS), pois todos os saltos possuem o mesmo peso e esse algoritmo garante encontrar o caminho mínimo em número de arestas.
A utilização de `unordered_map` permitiu otimizar a localização dos vértices associados aos endereços IP, evitando buscas lineares durante a construção do grafo (que o professor abobina :D).
Por fim, o Graphviz foi utilizado para fornecer uma representação visual da topologia da rede, facilitando a interpretação dos resultados obtidos pelos algoritmos implementados.

---

## Requisitos Implementados

- [x] Construção automática do grafo a partir dos logs;
- [x] Representação por lista de adjacência;
- [x] Busca do menor caminho utilizando BFS;
- [x] Cálculo do diâmetro da rede;
- [x] Identificação de roteadores críticos;
- [x] Visualização da topologia utilizando Graphviz;
- [x] Exportação para formato DOT;
- [x] Exportação para formato PNG;
- [x] Exportação para formato PDF;
- [x] Destaque visual do menor caminho;
- [x] Interface interativa baseada em menus.

---

## Complexidade dos Algoritmos

### Menor Caminho (BFS)

```
O(V + E)
```

Onde:

- V = número de vértices;
- E = número de arestas.

### Cálculo do Diâmetro

```
O(V × (V + E))
```

Uma BFS é executada para cada vértice do grafo.

### Roteadores Críticos

```
O(V log V)
```

Devido a etapa de ordenação dos vértices pelo grau de entrada.

---

## Autores

- Kauã Lima Rodrigues
- Gabriel Furigo Knopf

---

## Informações adicionais

**Curso:** Ciência da Computação - UPF

**Disciplina:** Estrutura de Dados II

**Professor:** Marcos José Brusso
