/**
 * PROJETO INTEGRADO: REDE SOCIAL E SISTEMA DE ROTAS COM GRAFOS
 * Disciplina: Estrutura de Dados
 * 
 * Este programa implementa:
 * 1. Uma rede social simulada usando grafos (BFS/DFS para relações)
 * 2. Um sistema de rotas entre cidades usando algoritmo de Dijkstra
 * 
 * Autor: [Seu Nome]
 * Data: [Data]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <windows.h>

// Constantes do programa
#define MAX_USERS 100          // Número máximo de usuários/cidades
#define MAX_NAME_LENGTH 50     // Tamanho máximo para nomes
#define INFINITY INT_MAX       // Representação de infinito


/**
 * Estrutura do nó para lista de adjacência
 * - id: identificador do vértice
 * - name: nome do vértice (usuário/cidade)
 * - weight: peso da aresta (1 para amizades, distância para rotas)
 * - next: próximo nó na lista
 */

typedef struct Node {
    int id;
    char name[MAX_NAME_LENGTH];
    int weight;
    struct Node* next;
} Node;



typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited;
    char vertexNames[MAX_USERS][MAX_NAME_LENGTH];
} Graph;

/* Protótipos das funções */
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));
    
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
        strcpy(graph->vertexNames[i], "");
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = dest;
    newNode->weight = weight;
    strcpy(newNode->name, graph->vertexNames[dest]);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->id = src;
    newNode->weight = weight;
    strcpy(newNode->name, graph->vertexNames[src]);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjLists[v];
        printf("\n%s [%d]: ", graph->vertexNames[v], v);
        while (temp) {
            printf("-> %s (%d) ", temp->name, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void clearScreen() {
    system("cls");
}

// Funções da Rede Social
void addUser(Graph* graph, int userId, const char* name) {
    if (userId >= 0 && userId < graph->numVertices) {
        strcpy(graph->vertexNames[userId], name);
    }
}

void addFriendship(Graph* graph, int user1, int user2) {
    addEdge(graph, user1, user2, 1); // Peso 1 para amizades
}

void BFS(Graph* graph, int startVertex) {
    int queue[MAX_USERS];
    int front = 0, rear = 0;
    
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
    
    graph->visited[startVertex] = 1;
    queue[rear++] = startVertex;
    
    printf("\nAmigos de %s (BFS):\n", graph->vertexNames[startVertex]);
    
    while (front < rear) {
        int currentVertex = queue[front++];
        printf("Visitando: %s\n", graph->vertexNames[currentVertex]);
        
        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->id;
            if (!graph->visited[adjVertex]) {
                printf("Encontrou amigo: %s\n", graph->vertexNames[adjVertex]);
                graph->visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
}

void DFS(Graph* graph, int startVertex) {
    graph->visited[startVertex] = 1;
    printf("Visitando: %s\n", graph->vertexNames[startVertex]);
    
    Node* temp = graph->adjLists[startVertex];
    while (temp) {
        int adjVertex = temp->id;
        if (!graph->visited[adjVertex]) {
            DFS(graph, adjVertex);
        }
        temp = temp->next;
    }
}

void suggestFriends(Graph* graph, int userId) {
    printf("\nSugestoes de amigos para %s:\n", graph->vertexNames[userId]);
    
    // Marca os amigos diretos
    Node* temp = graph->adjLists[userId];
    while (temp) {
        graph->visited[temp->id] = 2; // 2 = amigo direto
        temp = temp->next;
    }
    
    // Procura amigos de amigos
    temp = graph->adjLists[userId];
    while (temp) {
        Node* friendOfFriend = graph->adjLists[temp->id];
        while (friendOfFriend) {
            if (friendOfFriend->id != userId && graph->visited[friendOfFriend->id] != 2) {
                printf("Talvez voce conheca: %s (amigo de %s)\n", 
                       graph->vertexNames[friendOfFriend->id],
                       graph->vertexNames[temp->id]);
            }
            friendOfFriend = friendOfFriend->next;
        }
        temp = temp->next;
    }
    
    // Reseta os visitados
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

// Funções do Sistema de Rotas
void addCity(Graph* graph, int cityId, const char* name) {
    if (cityId >= 0 && cityId < graph->numVertices) {
        strcpy(graph->vertexNames[cityId], name);
    }
}

void addRoute(Graph* graph, int city1, int city2, int distance) {
    addEdge(graph, city1, city2, distance);
}

int minDistance(int dist[], int visited[], int vertices) {
    int min = INFINITY, min_index;
    for (int v = 0; v < vertices; v++)
        if (visited[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void printPath(int parent[], int j, Graph* graph) {
    if (parent[j] == -1) return;
    printPath(parent, parent[j], graph);
    printf(" -> %s", graph->vertexNames[j]);
}

void dijkstra(Graph* graph, int startCity, int endCity) {
    int dist[MAX_USERS];
    int parent[MAX_USERS];
    int visited[MAX_USERS];
    
    for (int i = 0; i < graph->numVertices; i++) {
        dist[i] = INFINITY;
        visited[i] = 0;
        parent[i] = -1;
    }
    
    dist[startCity] = 0;
    
    for (int count = 0; count < graph->numVertices - 1; count++) {
        int u = minDistance(dist, visited, graph->numVertices);
        visited[u] = 1;
        
        Node* temp = graph->adjLists[u];
        while (temp != NULL) {
            int v = temp->id;
            if (!visited[v] && dist[u] != INFINITY && dist[u] + temp->weight < dist[v]) {
                dist[v] = dist[u] + temp->weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }
    
    printf("\nMenor caminho de %s para %s:\n", 
           graph->vertexNames[startCity], graph->vertexNames[endCity]);
    printf("Distancia total: %d km\n", dist[endCity]);
    printf("Rota: %s", graph->vertexNames[startCity]);
    printPath(parent, endCity, graph);
    printf("\n");
}

// Menus e inicialização
void socialNetworkMenu(Graph* socialGraph) {
    int choice, user1, user2;
    do {
        clearScreen();
        printf("\n=== REDE SOCIAL ===\n");
        printf("1. Listar usuarios e conexoes\n");
        printf("2. Adicionar amizade\n");
        printf("3. Explorar rede (BFS)\n");
        printf("4. Explorar rede (DFS)\n");
        printf("5. Sugerir amigos\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printGraph(socialGraph);
                break;
            case 2:
                printf("Digite os IDs dos usuarios (ex: 0 1): ");
                scanf("%d %d", &user1, &user2);
                addFriendship(socialGraph, user1, user2);
                printf("Amizade adicionada!\n");
                break;
            case 3:
                printf("Digite o ID do usuario: ");
                scanf("%d", &user1);
                BFS(socialGraph, user1);
                break;
            case 4:
                printf("Digite o ID do usuario: ");
                scanf("%d", &user1);
                for (int i = 0; i < socialGraph->numVertices; i++) {
                    socialGraph->visited[i] = 0;
                }
                DFS(socialGraph, user1);
                break;
            case 5:
                printf("Digite o ID do usuario: ");
                scanf("%d", &user1);
                suggestFriends(socialGraph, user1);
                break;
        }
        if (choice != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar(); getchar();
        }
    } while(choice != 0);
}

void routeSystemMenu(Graph* routeGraph) {
    int choice, city1, city2, distance;
    do {
        clearScreen();
        printf("\n=== SISTEMA DE ROTAS ===\n");
        printf("1. Listar cidades e rotas\n");
        printf("2. Adicionar rota\n");
        printf("3. Calcular menor caminho (Dijkstra)\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printGraph(routeGraph);
                break;
            case 2:
                printf("Digite os IDs das cidades e a distancia (ex: 0 1 430): ");
                scanf("%d %d %d", &city1, &city2, &distance);
                addRoute(routeGraph, city1, city2, distance);
                printf("Rota adicionada!\n");
                break;
            case 3:
                printf("Digite os IDs de origem e destino (ex: 0 3): ");
                scanf("%d %d", &city1, &city2);
                dijkstra(routeGraph, city1, city2);
                break;
        }
        if (choice != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar(); getchar();
        }
    } while(choice != 0);
}

void initSocialGraph(Graph* graph) {
    addUser(graph, 0, "Alice");
    addUser(graph, 1, "Bob");
    addUser(graph, 2, "Carol");
    addUser(graph, 3, "David");
    addUser(graph, 4, "Eve");
    
    addFriendship(graph, 0, 1);
    addFriendship(graph, 0, 2);
    addFriendship(graph, 1, 3);
    addFriendship(graph, 2, 4);
    addFriendship(graph, 3, 4);
}

void initRouteGraph(Graph* graph) {
    addCity(graph, 0, "Sao Paulo");
    addCity(graph, 1, "Rio de Janeiro");
    addCity(graph, 2, "Belo Horizonte");
    addCity(graph, 3, "Brasilia");
    addCity(graph, 4, "Salvador");
    
    addRoute(graph, 0, 1, 430);  // SP-RJ
    addRoute(graph, 0, 2, 586);  // SP-BH
    addRoute(graph, 1, 2, 434);  // RJ-BH
    addRoute(graph, 2, 3, 716);  // BH-BSB
    addRoute(graph, 3, 4, 1446); // BSB-SSA
}

int main() {
    Graph* socialGraph = createGraph(MAX_USERS);
    Graph* routeGraph = createGraph(MAX_USERS);
    
    initSocialGraph(socialGraph);
    initRouteGraph(routeGraph);
    
    int choice;
    do {
        clearScreen();
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Rede Social Simulada\n");
        printf("2. Sistema de Rotas entre Cidades\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                socialNetworkMenu(socialGraph);
                break;
            case 2:
                routeSystemMenu(routeGraph);
                break;
        }
    } while(choice != 0);
    
    free(socialGraph);
    free(routeGraph);
    return 0;
}