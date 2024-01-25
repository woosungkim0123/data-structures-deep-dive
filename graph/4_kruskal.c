#include <stdio.h>
#include <stdlib.h>

// 간선 구조체
typedef struct Edge {
    int src; // 출발지
    int dest; // 도착지
    int weight; 
} Edge;

// 그래프 구조체
typedef struct Graph {
    int vertexCount;
    int edgeCount;
    Edge *edge;
} Graph;

// 부모를 찾기 위한 서브셋 구조체
typedef struct Subset {
    int parent;
    int rank;
} Subset;

void initGraph(Graph *graph, int vertexCount, int edgeCount);
void addEdge(Graph *graph, int edgeIndex, int src, int dest, int weight); // 간선 추가 함수


int find(Subset subsets[], int i); // find 함수: 서브셋의 루트 찾기

// Union 함수: 두 서브셋을 합치기
void unionUsingRank(Subset subsets[], int x, int y); // rank를 사용한 최적화 방법
void unionUseSmallRoot(Subset subsets[], int x, int y); // 작은 루트 값을 가진 쪽이 큰 쪽을 흡수하는 방법

int compare(const void *a, const void *b); // 비교 함수: qsort를 위한 가중치 비교 함수
void kruskalMST(Graph *graph); // 크루스칼 알고리즘
void printEdges(Graph *graph);

int main() 
{
    Graph graph;
    int vertexCount = 6;  // 정점의 개수
    int edgeCount = 10;  // 간선의 개수

    initGraph(&graph, vertexCount, edgeCount);

    // 간선 추가
    addEdge(&graph, 0, 0, 1, 5); // 간선 0 -> 1, 가중치 5
    addEdge(&graph, 1, 0, 3, 8); // 간선 0 -> 3, 가중치 8
    addEdge(&graph, 2, 1, 2, 3); // 간선 1 -> 2, 가중치 3
    addEdge(&graph, 3, 1, 3, 10); // 간선 1 -> 3, 가중치 10
    addEdge(&graph, 4, 1, 5, 15); // 간선 1 -> 5, 가중치 15
    addEdge(&graph, 5, 2, 3, 2); // 간선 2 -> 3, 가중치 2
    addEdge(&graph, 6, 2, 5, 35); // 간선 2 -> 5, 가중치 35
    addEdge(&graph, 7, 2, 4, 12); // 간선 2 -> 4, 가중치 12
    addEdge(&graph, 8, 4, 3, 20); // 간선 4 -> 3, 가중치 20
    addEdge(&graph, 9, 4, 5, 18); // 간선 4 -> 5, 가중치 18

    // 크루스칼 알고리즘 실행
    kruskalMST(&graph);

    free(graph.edge);

    return 0;
}

void initGraph(Graph *graph, int vertexCount, int edgeCount) 
{
    graph->vertexCount = vertexCount;
    graph->edgeCount = edgeCount;
    graph->edge = (Edge *)malloc(edgeCount * sizeof(Edge));
}

void addEdge(Graph* graph, int edgeIndex, int src, int dest, int weight) 
{
    graph->edge[edgeIndex].src = src;
    graph->edge[edgeIndex].dest = dest;
    graph->edge[edgeIndex].weight = weight;
}

int find(Subset subsets[], int i)
{
    if (subsets[i].parent != i) 
    {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void unionUsingRank(Subset subsets[], int x, int y) 
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    
    // rank를 사용한 최적화 방법
    if (subsets[xroot].rank < subsets[yroot].rank) 
    {
        subsets[xroot].parent = yroot;
    } 
    else if (subsets[xroot].rank > subsets[yroot].rank) 
    {
        subsets[yroot].parent = xroot;
    } 
    else 
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

void unionUseSmallRoot(Subset subsets[], int x, int y) 
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // 작은 루트 값을 가진 쪽이 큰 쪽을 흡수하는 방법
    if (xroot < yroot) {
        subsets[yroot].parent = xroot;
    } else if (xroot > yroot) {
        subsets[xroot].parent = yroot;
    }
}

int compare(const void *a, const void *b)
{
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->weight - edgeB->weight;
}

void kruskalMST(Graph *graph) 
{
    int vertexCount = graph->vertexCount;
    Edge *result = (Edge *)malloc(sizeof(Edge) * (vertexCount - 1));

    // Step 1: 모든 간선을 가중치에 따라 오름차순으로 정렬.

    // printf("Edges before sorting:\n");
    // printEdges(graph);

    qsort(graph->edge, graph->edgeCount, sizeof(graph->edge[0]), compare); // qsort는 c표준 라이브러리 함수로 배열을 정렬하기 위해 사용. qsort(정렬할 배열, 배열의 크기, 배열의 원소 크기, 비교 함수)
    
    // printf("\nEdges after sorting:\n");
    // printEdges(graph);

    // union-find를 위한 서브셋 생성 & 초기화
    Subset *subsets = (Subset *)malloc(vertexCount * sizeof(Subset));

    for (int i = 0; i < vertexCount; ++i)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    int resultIndex = 0;  // 결과 배열의 인덱스
    int sortedEdgeIndex = 0;  // 정렬된 모든 간선들에 대한 인덱스

    // Step 2: 가중치가 가장 낮은 간선부터 선택하면서 사이클이 발생하는지 확인
    while (resultIndex <= vertexCount - 1 && sortedEdgeIndex < graph->edgeCount) 
    {
        Edge nextEdge = graph->edge[sortedEdgeIndex++];

        // 사이클이 발생하는지 확인
        int xRoot = find(subsets, nextEdge.src);
        int yRoot = find(subsets, nextEdge.dest);

        // 사이클이 발생하지 않으면 결과에 추가
        if (xRoot != yRoot) 
        {
            result[resultIndex++] = nextEdge;
            // Step3: 두 서브넷의 Root를 합침
            unionUsingRank(subsets, xRoot, yRoot);

            //unionUseSmallRoot(subsets, xRoot, yRoot);
        }

        // 사이클이 발생하면 무시
    }
    // 결과 출력
    
    printf("Minimum Spanning Tree:\n");
    for (int i = 0; i < vertexCount - 1; ++i) 
    {
        printf("Edge: %d - %d, Weight: %d\n", result[i].src, result[i].dest, result[i].weight);
    }

    return;
}

void printEdges(Graph *graph) 
{
    for (int i = 0; i < graph->edgeCount; i++) {
        printf("Edge: %d - %d, Weight: %d\n", graph->edge[i].src, graph->edge[i].dest, graph->edge[i].weight);
    }
}