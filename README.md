# Projeto Integrado: Rede Social e Sistema de Rotas com Grafos

## Documentação Completa

### Informações do Projeto
**Autor**: Gabriel Giacomoni  
**Email**: sampaio.giacomo@gmail.com  
**Data**: 31/05/2025  
**Disciplina**: Estrutura de Dados  

## Visão Geral

Este projeto integrado combina dois sistemas baseados em grafos:
1. **Rede Social Simulada**: Implementa relações de amizade com algoritmos BFS/DFS
2. **Sistema de Rotas**: Calcula caminhos ótimos entre cidades usando Dijkstra

## Arquitetura do Sistema

### 1. Estruturas de Dados Principais

```c
typedef struct Node {
    int id;                     // Identificador único
    char name[MAX_NAME_LENGTH]; // Nome do vértice
    int weight;                 // Peso da aresta
    struct Node* next;          // Próximo nó na lista
} Node;

typedef struct Graph {
    int numVertices;            // Número total de vértices
    Node** adjLists;            // Listas de adjacência
    int* visited;               // Array de visitados
    char vertexNames[MAX_USERS][MAX_NAME_LENGTH]; // Nomes dos vértices
} Graph;
```

### 2. Módulos Principais

#### Rede Social (`social_network.c`)
- **BFS**: Explora relações em largura
  ```c
  void BFS(Graph* graph, int startVertex) {
      // Implementação da busca em largura
  }
  ```
- **DFS**: Explora relações em profundidade
  ```c
  void DFS(Graph* graph, int startVertex) {
      // Implementação da busca em profundidade
  }
  ```

#### Sistema de Rotas (`route_system.c`)
- **Dijkstra**: Calcula caminhos mínimos
  ```c
  void dijkstra(Graph* graph, int startCity, int endCity) {
      // Implementação do algoritmo
  }
  ```

## Guia de Compilação

### Windows
```bash
gcc -o social_network_route_system.exe main.c social_network.c route_system.c
```

### Linux/MacOS
```bash
gcc -o social_network_route_system main.c social_network.c route_system.c
```

## Dados de Exemplo

### Rede Social
```c
void initSocialGraph(Graph* graph) {
    addUser(graph, 0, "Alice");
    addUser(graph, 1, "Bob");
    // ... mais inicializações
}
```

### Sistema de Rotas
```c
void initRouteGraph(Graph* graph) {
    addCity(graph, 0, "São Paulo");
    addRoute(graph, 0, 1, 430); // SP-RJ: 430km
    // ... mais inicializações
}
```

## Diagrama de Fluxo

```
Menu Principal
├─ 1. Rede Social
│  ├─ 1. Listar conexões
│  ├─ 2. Adicionar amizade
│  └─ 3. Explorar rede
└─ 2. Sistema de Rotas
   ├─ 1. Listar rotas
   ├─ 2. Adicionar rota
   └─ 3. Calcular menor caminho
```

## Dependências
- GCC (MinGW para Windows)
- Sistema operacional Windows/Linux/MacOS

## Licença
Este projeto está licenciado sob a [MIT License](LICENSE).

---
