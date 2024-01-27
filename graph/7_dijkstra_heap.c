#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 6
#define INF 987654321

typedef struct Edge {
    int dest;
    int cost;
    struct Edge *next;
}Edge;

typedef struct Graph {
    Edge *head;
}Graph;

typedef struct Node {
    int vertex;
    int cost;
}Node;

typedef struct MinHeap {
    Node nodes[MAX_NODES];
    int size;
}MinHeap;

void swap(Node *a, Node *b);
void initMinHeap(MinHeap *heap);
void insertMinHeap(MinHeap *heap, int vertex, int cost);
void heapifyUp(MinHeap *heap, int currentIndex);
void heapifyDown(MinHeap *heap, int currentIndex);
void addDirectedEdge(Graph *pGrp, int src, int dest, int cost);
void addUnDirectedEdge(Graph *pGrp, int src, int dest, int cost);
void initGraph(Graph *graph, int numNodes);
void freeGraph(Graph *graph, int numNodes);
void dijkstra(Graph *graph, int src);

int main() 
{
    // Graph 초기화
    Graph graph[MAX_NODES];
    initGraph(graph, MAX_NODES);

    addDirectedEdge(graph, 0, 1, 3);
    addDirectedEdge(graph, 0, 2, 1);
    addDirectedEdge(graph, 0, 3, 10);
    addDirectedEdge(graph, 1, 3, 5);
    addDirectedEdge(graph, 2, 3, 8);
    addDirectedEdge(graph, 2, 4, 4);
    addDirectedEdge(graph, 2, 5, 6);
    addDirectedEdge(graph, 3, 5, 2);
    addDirectedEdge(graph, 4, 5, 8);

    dijkstra(graph, 0);

    freeGraph(graph, MAX_NODES);

    return 0;
}

void swap(Node *a, Node *b)
{
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void initMinHeap(MinHeap *heap) 
{
    heap->size = 0;
}

void insertMinHeap(MinHeap *heap, int vertex, int cost) 
{
    // 힙의 맨 끝에 새로운 노드를 추가한다.
    int currentIndex = heap->size++;
    heap->nodes[currentIndex].vertex = vertex;
    heap->nodes[currentIndex].cost = cost;

    heapifyUp(heap, currentIndex);
}

void heapifyUp(MinHeap *heap, int currentIndex)
{
    int parentIndex = (currentIndex - 1) / 2;

    // 부모 노드가 존재하고, 부모 노드의 값이 자식 노드의 값보다 크다면 swap (최소힙)
    if (parentIndex >= 0 && heap->nodes[parentIndex].cost > heap->nodes[currentIndex].cost)
    {
        swap(&heap->nodes[parentIndex], &heap->nodes[currentIndex]);
        heapifyUp(heap, parentIndex);
    }
}

void heapifyDown(MinHeap *heap, int currentIndex) 
{
    int leftChildIndex = 2 * currentIndex + 1;
    int rightChildIndex = leftChildIndex + 1;
    int smallestIndex = currentIndex;

    if (leftChildIndex < heap->size && heap->nodes[leftChildIndex].cost < heap->nodes[smallestIndex].cost) 
    {
        smallestIndex = leftChildIndex;
    }

    if (rightChildIndex < heap->size && heap->nodes[rightChildIndex].cost < heap->nodes[smallestIndex].cost) 
    {
        smallestIndex = rightChildIndex;
    }

    if (smallestIndex != currentIndex) 
    {
        swap(&heap->nodes[currentIndex], &heap->nodes[smallestIndex]);
        heapifyDown(heap, smallestIndex);
    }
}

Node extractMin(MinHeap *heap) 
{
    Node temp = heap->nodes[0]; // 임시 변수에 최소값을 저장한다.
    heap->nodes[0] = heap->nodes[heap->size - 1]; // 힙의 루트를 마지막 원소로 대체
    heap->size--; // 힙의 크기를 감소

    heapifyDown(heap, 0); // 힙을 재정렬한다.

    return temp;
}

void addDirectedEdge(Graph *pGrp, int src, int dest, int cost)
{
    Edge *newNode = (Edge *)malloc(sizeof(Edge));
    newNode->dest = dest;
    newNode->cost = cost;
    newNode->next = pGrp[src].head;
    pGrp[src].head = newNode;
}

void addUnDirectedEdge(Graph *pGrp, int src, int dest, int cost)
{
    addDirectedEdge(pGrp, src, dest, cost);
    addDirectedEdge(pGrp, dest, src, cost);
}

void dijkstra(Graph *graph, int src) 
{
    // 최소힙을 초기화한다.
    MinHeap heap;
    initMinHeap(&heap);

    int dist[MAX_NODES]; // 최단 거리를 저장할 배열 
    int visited[MAX_NODES] = {0}; // 방문 여부를 저장할 배열

    for (int i = 0; i < MAX_NODES; i++) 
    {
        dist[i] = INF;
    }
    dist[src] = 0; // 출발지의 거리는 0

    insertMinHeap(&heap, src, 0); // 출발지를 최소힙에 삽입한다.

    while (heap.size > 0) 
    {
        // 최소힙에서 최소값을 추출한다.
        Node minNode = extractMin(&heap);
        int currentVertex = minNode.vertex;

        // 이미 방문한 정점이라면 무시한다.
        if (visited[currentVertex])
        {
            continue;
        }

        visited[currentVertex] = 1; // 방문 표시를 한다.

        // 현재 정점과 연결된 모든 간선을 순회한다.
        Edge *edge = graph[currentVertex].head; 
        while (edge) 
        {
            int neighborVertex = edge->dest; // 현재 정점과 연결된 정점
            int edgeCost = edge->cost; // 현재 정점과 연결된 정점의 비용

            // 이웃 정점이 방문한 적이 없고, 현재 정점을 거쳐서 이웃 정점으로 가는 비용이 더 작다면 최단 거리를 갱신한다.
            if (!visited[neighborVertex] && dist[neighborVertex] > dist[currentVertex] + edgeCost) 
            {
                dist[neighborVertex] = dist[currentVertex] + edgeCost;
                insertMinHeap(&heap, neighborVertex, dist[neighborVertex]);
            }
            edge = edge->next;
        }
    }

    for (int i = 0; i < MAX_NODES; i++) 
    {
        if (dist[i] == INF) 
        {
            printf("Distance from %d to %d: INF\n", src, i);
        } else {
            printf("Distance from %d to %d: %d\n", src, i, dist[i]);
        }
    }
}

void initGraph(Graph *graph, int numNodes) 
{
    for (int i = 0; i < numNodes; i++) 
    {
        graph[i].head = NULL;
    }
}

void freeGraph(Graph *graph, int numNodes) 
{
    for (int i = 0; i < numNodes; i++) 
    {
        Edge *current = graph[i].head;
        while (current) 
        {
            Edge *temp = current;
            current = current->next;
            free(temp);
        }
    }
}
