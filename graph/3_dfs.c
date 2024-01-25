#include <stdio.h>
#include <stdlib.h>
#include "header/stack.h"

typedef struct Node {
    int vertex; // 정점
    int cost; // 비용
    struct Node *next; // 다음 노드의 주소
} Node;

typedef struct Graph {
    Node *head; // 출발지 노드의 주소
    int vertexCount; // 정점의 개수
} Graph;

void init(Graph *pGraph, int count);
void addDirectedEdge(Graph *pGraph, int src, int dst, int cost);
void addUnDirectedEdge(Graph *pGraph, int src, int dst, int cost);
void printGraph(Graph *pGraph);
void dfsStack(Graph *pGraph, int startVertex);

int main()
{
    Graph graph;

    init(&graph, 10);

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

    dfsStack(&graph, 0);

    return 0;
}

void init(Graph *pGraph, int count)
{
    pGraph->vertexCount = count;
    pGraph->head = (Node *)malloc(sizeof(Node) * count); 

    for (int i = 0; i < count; i++) 
    {
        pGraph->head[i].vertex = i;
        pGraph->head[i].cost = 1;
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
        printf("%d: ", i);

        while (pNode != NULL)
        {
            printf("%d(cost: %d) ", pNode->vertex, pNode->cost);
            pNode = pNode->next;
        }
        printf("\n");
    }
}

void dfsStack(Graph *pGraph, int startVertex)
{
    int *visited = (int *)calloc(pGraph->vertexCount, sizeof(int));
    Stack stk;
    initStack(&stk, pGraph->vertexCount);

    // 1. push
    push(&stk, startVertex);
    visited[startVertex] = 1; // 방문체크

    // 2. 비어있는지 확인
    while (!isEmpty(&stk))
    {
        // 3. pop
        int currentVertex = pop(&stk);
        printf("%d ", currentVertex);

        // pop한 정점의 인접 정점을 push
        Node *pNode = pGraph->head[currentVertex].next;
        while (pNode)
        {
            if (visited[pNode->vertex] == 0)
            {
                push(&stk, pNode->vertex);
                visited[pNode->vertex] = 1; // 방문 체크
            }
            pNode = pNode->next;
        }
    }
    printf("\n");

    free(stk.data);
    free(visited);
}