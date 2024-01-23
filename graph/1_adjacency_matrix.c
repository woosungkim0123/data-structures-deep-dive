#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int vertexCount;
    int **arr; // 동적 할당된 포인터 배열의 주소를 저장
} Graph;

void init(Graph *pGraph, int count);
void unDirectedEdge(Graph *pGraph, int start, int end);
void edgePrint(Graph *pGraph);
void memoryFree(Graph *pGraph);

int main()
{
    Graph graph;
    init(&graph, 4);

    unDirectedEdge(&graph, 0, 1);
    unDirectedEdge(&graph, 0, 2);
    unDirectedEdge(&graph, 1, 2);
    unDirectedEdge(&graph, 2, 3);

    edgePrint(&graph);

    memoryFree(&graph);
    return 0;
}

void init(Graph *pGraph, int count)
{
    pGraph->vertexCount = count;
    pGraph->arr = (int **)malloc(sizeof(int *) * count); // 정점이 저장되는 배열이 만들어짐

    for (int i = 0; i < count; i++) 
    {
        pGraph->arr[i] = (int *)calloc(count, sizeof(int)); // 0으로 초기화된 배열이 만들어짐
    }
}

void unDirectedEdge(Graph *pGraph, int start, int end)
{
    if (start >= pGraph->vertexCount || end >= pGraph->vertexCount) 
    {
        fprintf(stderr, "graph edge error");
        return;
    }

    pGraph->arr[start][end] = 1;
    pGraph->arr[end][start] = 1;
}

void edgePrint(Graph *pGraph)
{
    for (int i = 0; i < pGraph->vertexCount; i++) 
    {
        for (int j = 0; j < pGraph->vertexCount; j++) 
        {
            printf("%d ", pGraph->arr[i][j]);
        }
        printf("\n");
    }
}

void memoryFree(Graph *pGraph)
{
    for (int i = 0; i < pGraph->vertexCount; i++) 
    {
        free(pGraph->arr[i]); // arr[i]이 가리키는 일차원 배열 제거
    }
    free(pGraph->arr); // 이차원 배열을 만들기 위한 포인터 배열 제거
}