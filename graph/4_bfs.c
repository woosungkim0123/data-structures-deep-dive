#include <stdio.h>
#include <stdlib.h>
#include "header/queue.h"  // 큐 구현을 위한 헤더 파일

typedef struct Node {
    int vertex; // 정점
    int cost; // 비용
    struct Node *next; // 다음 노드의 주소
} Node;

typedef struct Graph {
    Node *head; // 각 정점의 인접 리스트 헤드
    int vertexCount; // 정점의 개수
} Graph;

void init(Graph *pGraph, int count);
void addUnDirectedEdge(Graph *pGraph, int src, int dst, int cost);
void addDirectedEdge(Graph *pGraph, int src, int dst, int cost);
void printGraph(Graph *pGraph);
void bfs(Graph *pGraph, int startVertex);
void freeGraph(Graph *pGraph);

int main() 
{
    Graph graph;
    init(&graph, 6);

    // 간선 추가
    addUnDirectedEdge(&graph, 0, 1, 1);
    addUnDirectedEdge(&graph, 0, 2, 1);
    addUnDirectedEdge(&graph, 0, 3, 1);
    addUnDirectedEdge(&graph, 1, 2, 1);
    addUnDirectedEdge(&graph, 1, 4, 1);
    addUnDirectedEdge(&graph, 2, 3, 1);
    addUnDirectedEdge(&graph, 2, 4, 1);
    addUnDirectedEdge(&graph, 2, 5, 1);
    addUnDirectedEdge(&graph, 3, 5, 1);
    addUnDirectedEdge(&graph, 4, 5, 1);


    printf("Graph:\n");
    printGraph(&graph);

    printf("\nBFS:\n");
    bfs(&graph, 0);

    freeGraph(&graph);
    return 0;
}

void init(Graph *pGraph, int count) 
{
    pGraph->vertexCount = count;
    pGraph->head = (Node *)malloc(sizeof(Node) * count); 

    for (int i = 0; i < count; i++) 
    {
        pGraph->head[i].vertex = i;
        pGraph->head[i].cost = 0;
        pGraph->head[i].next = NULL;
    }
}

void addUnDirectedEdge(Graph *pGraph, int src, int dst, int cost)
{  
    addDirectedEdge(pGraph, src, dst, cost);
    addDirectedEdge(pGraph, dst, src, cost);
}

void addDirectedEdge(Graph *pGraph, int src, int dst, int cost)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = dst;
    newNode->cost = cost;
    newNode->next = NULL;

    if (pGraph->head[src].next == NULL)
    {
        pGraph->head[src].next = newNode;
        return;
    }

    newNode->next = pGraph->head[src].next;
    pGraph->head[src].next = newNode;
}

void printGraph(Graph *pGraph) 
{
    for (int i = 0; i < pGraph->vertexCount; i++) 
    {
        Node *pNode = pGraph->head[i].next;
        printf("Vertex %d: ", i);
        while (pNode != NULL) 
        {
            printf("%d(cost: %d) ", pNode->vertex, pNode->cost);
            pNode = pNode->next;
        }
        printf("\n");
    }
}

void bfs(Graph *pGraph, int startVertex) 
{
    int *visited = (int *)calloc(pGraph->vertexCount, sizeof(int));
    QueueType que;

    initQueue(&que);

    enqueue(&que, startVertex); // 시작 정점을 큐에 삽입
    visited[startVertex] = 1; // 시작 정점 방문 표시

    while (!isEmpty(&que)) // 큐가 비어있지 않은 동안
    {
        int currentVertex = dequeue(&que); // 큐에서 정점을 꺼냄
        printf("%d ", currentVertex);

        Node *pNode = pGraph->head[currentVertex].next;
        while (pNode) 
        {
            if (!visited[pNode->vertex]) // 방문하지 않은 정점이라면 
            {
                enqueue(&que, pNode->vertex);
                visited[pNode->vertex] = 1;
            }
            pNode = pNode->next;
        }
    }
    printf("\n");

    free(visited);
}

void freeGraph(Graph *pGraph) 
{
    for (int i = 0; i < pGraph->vertexCount; i++) 
    {
        Node *pNode = pGraph->head[i].next;
        while (pNode != NULL) 
        {
            Node *temp = pNode;
            pNode = pNode->next;
            free(temp);
        }
    }
    free(pGraph->head);
}