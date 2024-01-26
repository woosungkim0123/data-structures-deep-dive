#include <stdio.h>
#include <stdlib.h>

const int INFINITE =  987654321;
const int VERTEX_COUNT = 6;

void dijkstra(int src, int (*arr)[6], int *cost);

int main()
{
    int arr[6][6] = {
        {0, 3, 1, 10, INFINITE, INFINITE}, // 0정점에서 0, 1, 2, 3, 4, 5 정점으로 가는 가중치
        {3, 0, INFINITE, 5, INFINITE, INFINITE},  // 1정점에서 0, 1, 2, 3, 4, 5 정점으로 가는 가중치
        {1, INFINITE, 0, 8, 4, 6}, // ...
        {10, 5, 8, 0, INFINITE, 2},
        {INFINITE, INFINITE, 4, INFINITE, 0, 8},
        {INFINITE, INFINITE, 6, 2, 8, 0}
    }; 

    int cost[6]; // 최소 가중치를 저장할 배열

    dijkstra(0, arr, cost); // 시작정점, 초기 가중치, 최단 경로 가중치를 저장할 배열

    for (int i = 0; i < VERTEX_COUNT; i++)
    {
        printf("%d ", cost[i]);
    }

    return 0;
}

/**
 * 시간복잡도: O(n^2)
 * int (*arr)[6] - 6개의 정수를 포함하는 배열에 대한 포인터 즉, 
 * arr은 6개의 정수를 갖는 배열의 "배열"에 접근하기 위한 포인터
*/
void dijkstra(int src, int (*arr)[6], int *cost)
{
    int *visited = (int *)calloc(VERTEX_COUNT, sizeof(int));
    visited[src] = 1;

    // 0번 정점에서 각 정점으로 가는 가중치로 초기화
    for (int i = 0; i < VERTEX_COUNT; i++)
    {
        cost[i] = arr[src][i];
    }

    for (int i = 0; i < VERTEX_COUNT - 1; i++)
    {
        int minCost = INFINITE;
        int minVertex = -1;

        // 최소 가중치를 갖는 정점을 찾는다.
        for (int j = 0; j < VERTEX_COUNT; j++) 
        {
            if (!visited[j] && cost[j] < minCost) 
            {
                minCost = cost[j];
                minVertex = j;
            }
        }

        if (minVertex != -1)
        {
            visited[minVertex] = 1;
            
            // 최소 가중치를 갖는 정점과 연결된 정점들의 가중치를 갱신한다.
            for (int j = 0; j < VERTEX_COUNT; j++)
            {
                if (!visited[j] && cost[j] > cost[minVertex] + arr[minVertex][j])
                {
                    cost[j] = cost[minVertex] + arr[minVertex][j];
                }
            }
        }
    }
}

