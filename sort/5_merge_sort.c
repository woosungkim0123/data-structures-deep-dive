#include <stdio.h>
#include <stdlib.h>

void merge_sort(int *arr, int size);
void merge_sort_util(int *arr, int *arrMerge, int left, int right);
void merge(int *arr, int *arrMerge, int left, int mid, int right);
void print_array(int *arr, int size);

#define ARRAY_SIZE 5

/**
 * 시간복잡도: O(nlogn)
 * 공간복잡도: 0(n) - 정렬된 배열을 담을 공간이 필요함
*/
int main()
{
    int arr[ARRAY_SIZE] = {7, 5, 2, 4, 1};

    printf("Array before sorting: ");
    print_array(arr, ARRAY_SIZE);

    merge_sort(arr, ARRAY_SIZE);
    
    printf("Array after sorting: ");
    print_array(arr, ARRAY_SIZE);

    return 0;
}

void merge_sort(int *arr, int size)
{
    int *arrCopy = (int *)malloc(sizeof(int) * size);
    merge_sort_util(arr, arrCopy, 0, size - 1);
    free(arrCopy);
}

void merge_sort_util(int *arr, int *arrCopy, int left, int right)
{
    int mid;
    
    if (left < right)
    {
        mid = (left + right) / 2;
        merge_sort_util(arr, arrCopy, left, mid);
        merge_sort_util(arr, arrCopy, mid + 1, right);
        merge(arr, arrCopy, left, mid, right);
    }
}

/**
 * 병합 정렬 과정에서 두 개의 정렬된 부분 배열을 하나의 정렬된 배열로 병합합니다.
 * 이 함수는 주어진 배열의 특정 범위(left부터 right까지)를 대상으로 합니다.
 * 
 * @param arr 원본 배열의 포인터. 이 배열의 일부 범위가 병합될 것입니다.
 * @param arrCopy 원본 배열의 복사본을 저장할 배열의 포인터. 병합 과정 중 임시 저장공간으로 사용됩니다.
 * @param left 병합을 시작할 배열의 가장 왼쪽 인덱스.
 * @param mid 배열을 두 부분으로 나누는 중간 인덱스. left부터 mid까지가 첫 번째 부분 배열, mid+1부터 right까지가 두 번째 부분 배열입니다.
 * @param right 병합을 마칠 배열의 가장 오른쪽 인덱스.
 * 
 * 이 함수는 두 부분 배열을 순회하면서 각 부분 배열의 요소들을 비교하고, 더 작은 값을 가진 요소를 선택하여
 * 원본 배열의 left부터 right 범위에 오름차순으로 재배치합니다. 이 과정은 두 부분 배열 중 하나가 완전히
 * 소진될 때까지 계속됩니다. 만약 한 부분 배열의 요소들이 모두 선택되어 다른 배열에 남아 있는 요소가 있다면,
 * 남은 요소들은 그대로 원본 배열에 복사됩니다.
 */
void merge(int *arr, int *arrCopy, int left, int mid, int right)
{
    int index1 = left;
    int index2 = mid + 1;
    int indexM = left;

    // merge 배열 값을 arrCopy에 미리 복사
    for (int i = left; i <= right; i++)
    {
        arrCopy[i] = arr[i];
    }

    while (index1 <= mid && index2 <= right)
    {
        if (arrCopy[index1] < arr[index2])
        {
            arr[indexM++] = arrCopy[index1++];
        }
        else 
        {
            arr[indexM++] = arrCopy[index2++];
        }
    }

    while (index1 <= mid)
    {
        arr[indexM++] = arrCopy[index1++];
    }

    while (index2 <= right)
    {
        arr[indexM++] = arrCopy[index2++];
    }
}

void print_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}