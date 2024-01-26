#include <stdio.h>
#include <stdlib.h>

const int INFINITE =  987654321;
const int VERTEX_COUNT = 6;

typedef struct Node {
    int vertex;
    int cost;
    struct Node *next;
}Node;

typedef struct Graph {
    int count; // 정점의 개수
    Node *arr;
}Graph;

typedef struct TableNode {
	int vertex;
	int cost;
	int visited;
}TableNode;

typedef struct Heap {
    TableNode *arr; // 힙을 저장하는 배열
    int size; // 배열의 크기
    int capacity;  // 배열의 최대용량
}Heap;

void dijkstra(Graph *pGrp, int startVertex);
void shiftDown(TableNode *arr, int parentIndex, int size);
void heapify(TableNode *arr, int size);
void heapInit(Heap *heap, TableNode *arr, int size);
void display(Graph *pGrp);
void graphInit(Graph *pGrp, int vertexCnt);
void addDirectedEdge(Graph *pGrp, int src, int dst, int cost);
void addUnDirectedEdge(Graph *pGrp, int src, int dst, int cost);
void memoryFree(Graph *pGrp);


int main()
{

    Graph graph;
    
    graphInit(&graph, VERTEX_COUNT);

    addUnDirectedEdge(&graph, 0, 1, 3);
    addUnDirectedEdge(&graph, 0, 2, 1);
    addUnDirectedEdge(&graph, 0, 3, 10);
    addUnDirectedEdge(&graph, 1, 3, 5);
    addUnDirectedEdge(&graph, 2, 3, 8);
    addUnDirectedEdge(&graph, 2, 4, 4);
    addUnDirectedEdge(&graph, 2, 5, 6);
    addUnDirectedEdge(&graph, 3, 5, 2);
    addUnDirectedEdge(&graph, 4, 5, 8);

    display(&graph);

    dijkstra(&graph, 0);

    memoryFree(&graph);

    return 0;
}

void graphInit(Graph *pGrp, int vertexCnt) 
{
    pGrp->count = vertexCnt;
    pGrp->arr = (Node *)calloc(vertexCnt, sizeof(Node));
    
    for (int i = 0; i < vertexCnt; i++) 
    {
        pGrp->arr[i].vertex = i;
        pGrp->arr[i].cost = 0;
        pGrp->arr[i].next = NULL;
    }
}

void dijkstra(Graph *pGrp, int startVertex)
{
    // 내부값 전부 0으로 초기화
    TableNode *table = (TableNode *)calloc(VERTEX_COUNT, sizeof(TableNode));

    for (int i = 0; i < pGrp->count; i++)
    {
        table[i].vertex = i;

        if (i == startVertex)
        {
            table[i].cost = 0;
        }
        else
        {
            table[i].cost = INFINITE;
        }
    }

    // 0에서 인접한 노드의 가중치 값을 저장
    Node *curNode = pGrp->arr[startVertex].next;
    
    while(curNode)
	{
		table[curNode->vertex].cost = curNode->cost;
		curNode = curNode->next;
	}

    Heap heap;
    // 최소힙
	heapInit(&heap, table, pGrp->count);

    int top = 0;

    while (heap.size > 0)
    {
        int vertex = heap.arr[top].vertex; // 가장 위. 즉, 가장 작은 값을 가진 노드의 인덱스
        table[vertex].visited = 1; // 방문처리
        heap.size--;
        top++;

        curNode = pGrp->arr[vertex].next;

        while(curNode) 
        {
			int destination = curNode->vertex;
            int cost = curNode->cost;

            // 현재 노드의 가중치 + 다음 노드의 가중치가 다음 노드의 가중치보다 작을 때
			int newCost = cost + table[vertex].cost;

            if (table[destination].visited == 0 && newCost < table[destination].cost)
            {
                table[destination].cost = newCost;
                shiftDown(table, destination, heap.size);
            }
			curNode = curNode->next;
        }
    }

    for(int i = 0; i < pGrp->count; i++) 
    {
		if(table[i].cost == INFINITE)
        {
            printf("unreachable\n");
        }
		else
        {
            printf("vertex 0 ~ vertex %d cost = %d\n", i, table[i].cost);
        }
			
	}

}

void addUnDirectedEdge(Graph *pGrp, int src, int dst, int cost) 
{
	addDirectedEdge(pGrp, src, dst, cost);
	addDirectedEdge(pGrp, dst, src, cost);
}

// 포인터, 출발지, 도착지, 비용
void addDirectedEdge(Graph *pGrp, int src, int dst, int cost) 
{
    Node *newNode = (Node *)malloc(sizeof(Node));

	// 인접리스트 방식 (맨 앞에 삽입)
	newNode->vertex = dst;
	newNode->cost = cost;
	newNode->next = pGrp->arr[src].next;
	pGrp->arr[src].next = newNode;
}

void heapInit(Heap *heap, TableNode *arr, int size)
{
    heap->capacity = VERTEX_COUNT;
    heap->size = size;
    heap->arr = arr;
    heapify(heap->arr, heap->size);
}

void heapify(TableNode *arr, int size)
{
    // 완전 이진 트리 부모 노드의 개수 = (전체 개수 / 2)
    int parent = (size / 2) - 1; // -1을 해주는 이유는 배열의 인덱스가 0부터 시작하기 때문에

    for (int i = parent; i >= 0; i--)
    {
        shiftDown(arr, i, size); // 부모 노드의 값을 자식 노드의 값과 비교;
    }
}

// 최소힙
void shiftDown(TableNode *arr, int parentIndex, int size)
{
    int leftChildIndex = parentIndex * 2 + 1;
    int rightChildIndex = leftChildIndex + 1;
    int smallIndex = -1;

    if (leftChildIndex < size)
    {
        smallIndex = leftChildIndex;
    }

    // 오른쪽 자식이 부모 보다 작을 때
    if (rightChildIndex < size && arr[rightChildIndex].cost < arr[leftChildIndex].cost)
    {
        smallIndex = rightChildIndex;
    }
    
    // 자식의 값이 부모보다 작을 때
    if (smallIndex != -1 && arr[smallIndex].cost < arr[parentIndex].cost)
    {
        TableNode temp = arr[smallIndex];
        arr[smallIndex] = arr[parentIndex];
        arr[parentIndex] = temp;

        shiftDown(arr, smallIndex, size);
    }
}

void memoryFree(Graph *pGrp)
{
    Node *delNode = NULL;

    for (int i = 0; i < pGrp->count; i++) 
    {
        while (pGrp->arr[i].next != NULL)
        {
            delNode = pGrp->arr[i].next;
            pGrp->arr[i].next = delNode->next;
            free(delNode);
        }
    }

    free(pGrp->arr);
}

void display(Graph *pGrp) 
{
	int i;
	Node *curNode = NULL;

	if(pGrp->arr == NULL) return;

	for(i = 0; i < pGrp->count; i++) 
    {
		curNode = pGrp->arr[i].next;
		printf("start Node : %d => ", pGrp->arr[i].vertex);

		while(curNode != NULL) 
        {
			printf("%d (cost: %d) ", curNode->vertex, curNode->cost);
			curNode = curNode->next;
		}
		puts("");
	}
}