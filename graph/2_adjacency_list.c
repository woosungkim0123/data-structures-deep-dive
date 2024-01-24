#include <stdio.h>
#include <stdlib.h>

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

int main()
{
    Graph graph;

    init(&graph, 4);

    addUnDirectedEdge(&graph, 0, 1, 1);
    addUnDirectedEdge(&graph, 0, 2, 1);
    addUnDirectedEdge(&graph, 1, 2, 1);
    addUnDirectedEdge(&graph, 2, 3, 1);

    printGraph(&graph);
    
    return 0;
}

void init(Graph *pGraph, int count)
{
    pGraph->vertexCount = count;
    pGraph->head = (Node *)malloc(sizeof(Node) * count); // 4개의 노드를 저장할 수 있는 배열이 만들어짐

    for (int i = 0; i < count; i++) 
    {
        pGraph->head[i].vertex = i;
        pGraph->head[i].cost = 1;
        pGraph->head[i].next = NULL;
    }
}

void addUnDirectedEdge(Graph *pGraph, int src, int dst, int cost)
{  
    // 무방향 그래프이므로 양쪽으로 간선을 추가해줘야함
    addDirectedEdge(pGraph, src, dst, cost);
    addDirectedEdge(pGraph, dst, src, cost);
}

void addDirectedEdge(Graph *pGraph, int src, int dst, int cost)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = dst;
    newNode->cost = cost;
    newNode->next = NULL;

    // 아무 노드도 없을 때
    if (pGraph->head[src].next == NULL)
    {
        pGraph->head[src].next = newNode;
        return;
    }

    // 노드가 있을 때 앞에 삽입 (위치가 중요하지않음)
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