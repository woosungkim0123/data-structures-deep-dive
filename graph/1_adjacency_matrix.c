#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int vertexCount;
    int **arr; // 동적 할당된 포인터 배열의 주소를 저장
} Graph;

void init(Graph *pGraph, int count)
{
    pGraph->vertexCount = count;
    pGraph->arr = (int **)malloc(sizeof(int *) * count); // 정점이 저장되는 배열이 만들어짐

    for (int i = 0; i < count; i++) 
    {
        pGraph->arr[i] = (int *)malloc(sizeof(int) * count);
    }
}

void insert_vertex(GraphType* g, int v)
{
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "graph vertex error");
        return;
    }
    g->n++;
}

void insert_edge(GraphType* g, int start, int end)
{
    if (start >= g->n || end >= g->n) {
        fprintf(stderr, "graph edge error");
        return;
    }
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

void print_adj_mat(GraphType* g)
{
    for (int r = 0; r < g->n; r++) {
        for (int c = 0; c < g->n; c++) {
            printf("%d ", g->adj_mat[r][c]);
        }
        printf("\n");
    }
}

void main()
{
    GraphType *g;
    g = (GraphType*)malloc(sizeof(GraphType));
    init(g);

    for (int i = 0; i < 4; i++) {
        insert_vertex(g, i);
    }
    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);
    
    print_adj_mat(g);

    free(g);
}

