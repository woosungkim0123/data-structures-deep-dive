#include <stdio.h>
#include <stdlib.h>

#define EMPTY_MODE 0
#define DELETE_MODE -1
#define FILLED_MODE 1

typedef struct HashTable {
    int size;
    int *arr;
	int *flag;
}HashTable;

void hashInit(HashTable *pHt, int size);
int hashFunction(int key, int size);
void hashAdd(HashTable *pHt, int key);
void hashPrint(const HashTable *pHt);
int hashFind(HashTable *pHt, int key);
void hashRemove(HashTable *pHt, int key);

int main()
{
    HashTable ht;
    hashInit(&ht, 7);
	
	hashAdd(&ht, 77);
	hashAdd(&ht, 23);
	hashAdd(&ht, 36);
    hashAdd(&ht, 96);
    hashAdd(&ht, 69);
	hashAdd(&ht, 18);

    hashPrint(&ht);
    printf("\n");

    hashAdd(&ht, 92); // 92 % 7 = 1이지만 1번, 2번 인덱스가 이미 차있으므로 3번 인덱스에 저장된다.

    hashPrint(&ht);

    if (hashFind(&ht, 77))
    {
        printf("77 exist.\n");
    }
    else
    {
        printf("77 not exist \n");
    }

    hashRemove(&ht, 77);

    if (hashFind(&ht, 77))
    {
        printf("77 exist.\n");
    }
    else
    {
        printf("77 not exist \n");
    }
}

void hashInit(HashTable *pHt, int size)
{
    pHt->size = size;
    pHt->arr = (int *)malloc(sizeof(int) * size);
    pHt->flag = (int *)malloc(sizeof(int) * size);
    
    for(int i = 0; i < size; i++)
    {
        pHt->flag[i] = EMPTY_MODE;
    }
}

int hashFunction(int key, int size)
{
    return key % size;
}

/**
 * open addressing 방식의 해시 테이블에 key를 추가한다.
*/
void hashAdd(HashTable *pHt, int key)
{
    int hashValue = hashFunction(key, pHt->size);

    int i;
    for (i = 0; i < pHt->size; i++)
    {
        if (pHt->flag[hashValue] == EMPTY_MODE || pHt->flag[hashValue] == DELETE_MODE)
        {
            pHt->arr[hashValue] = key;
            pHt->flag[hashValue] = FILLED_MODE;
            break;
        }
        // 해시 충돌 발생시
        ++hashValue;
        hashValue %= pHt->size; // 해시 테이블의 크기를 초과하지 않도록 함
    }

    if (i == pHt->size)
    {
        printf("해시 테이블이 가득 찼습니다.\n");
    }
}

void hashPrint(const HashTable *pHt)
{
	for (int i = 0; i < pHt->size; i++)
	{
		if (pHt->flag[i] == FILLED_MODE)
		{
			printf("%d ", pHt->arr[i]);
		} else {
            printf("X ");
        }
	}
	puts("");
}

int hashFind(HashTable *pHt, int key)
{
    int hashValue = hashFunction(key, pHt->size);

    for (int i = 0; i < pHt->size; i++)
    {
        // 빈 공간을 만나면 탐색을 종료한다.
        if (pHt->flag[hashValue] == EMPTY_MODE) 
        {
            break;
        }
        // 값이 일치하면 탐색을 종료한다.
        if (pHt->flag[hashValue] == FILLED_MODE && pHt->arr[hashValue] == key) 
        {
            return key;
        }

        ++hashValue;
        hashValue %= pHt->size;
    }

    return 0;
}

void hashRemove(HashTable *pHt, int key)
{
    int hashValue = hashFunction(key, pHt->size);

    for (int i = 0; i < pHt->size; i++)
    {
        // 빈 공간을 만나면 탐색을 종료한다.
        if (pHt->flag[hashValue] == EMPTY_MODE) 
        {
            break;
        }
        // 값이 일치하면 탐색을 종료한다.
        if (pHt->flag[hashValue] == FILLED_MODE && pHt->arr[hashValue] == key) 
        {
            pHt->flag[hashValue] = DELETE_MODE;
            return;
        }

        ++hashValue;
        hashValue %= pHt->size;
    }
}