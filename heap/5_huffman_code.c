#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 200
#define MAX_CODE_LENGTH 100

typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

typedef struct {
    TreeNode *ptree; // 각 노드가 어떤 서브트리에 속하는지를 표시합니다.
    char ch; // 문자
    int key; // 빈도수
} element;

typedef struct {
    element arr[MAX_ELEMENT];
    int size;
} Heap;

// 허프만 코드
typedef struct {
    char ch;
    char code[MAX_CODE_LENGTH];
} HuffmanCode;

HuffmanCode huffmanCodes[MAX_ELEMENT]; // 전역 변수로 허프만 코드 저장
int codeIndex = 0; // 허프만 코드 인덱스

void huffmanTree(char chList[], int freqList[], int n);
Heap * createHeap();
void init(Heap *heap);
element extractMin(Heap *heap);
void insertMinHeap(Heap *heap, element value);
void shiftUp(Heap *heap, int childIndex);
void shiftDown(Heap *heap, int parentIndex);
void destroyTree(TreeNode *root);
TreeNode * makeTree(TreeNode *left, TreeNode *right);
void printCode(TreeNode *root, int codes[], int top);
void storeCodes(TreeNode *root, char *code, int length);
void encode(char *str, char *encodedStr);
void decode(TreeNode *root, char *encodedStr, char *decodedStr);
void encodingDecodingPrint(char *randomString);

TreeNode *encodingRoot = NULL;

/**
 * 허프만 코드
*/
int main()
{
    /**
     * 허프만 코드 생성
    */
    char chList[] = {'s', 'i', 'n', 't', 'e'};
    int freqList[] = {4, 6, 8, 12, 15};

    huffmanTree(chList, freqList, 5);

    /**
     * 허프만 코드로 인코딩 디코딩 출력 (chList와 freqList를 이용하여 만든 임의 문자열)
    */
    char randomString[] = "nnieneenneineneesenenesttttietitineettieennet";
    encodingDecodingPrint(randomString);

    destroyTree(encodingRoot);
    return 0;
}

void huffmanTree(char chList[], int freqList[], int n)
{
    int i;
    TreeNode *node, *x;
    Heap *heap;
    element e, e1, e2;

    heap = createHeap();
    init(heap);

    for (i = 0; i < n; i++)
    {
        // 트리 노드 생성
        node = makeTree(NULL, NULL);
        node->ch = chList[i];
        node->weight = freqList[i];

        // element 구조체에 값 삽입
        e.ch = chList[i];
        e.key = freqList[i];
        e.ptree = node;

        // 최소 힙에 삽입
        insertMinHeap(heap, e);
    }

    for (i = 1; i < n; i++)
    {
        // 최소값 두개를 추출
        e1 = extractMin(heap);
        e2 = extractMin(heap);
        
        // 트리 노드 생성
        x = makeTree(e1.ptree, e2.ptree);
        e.key = x->weight = e1.key + e2.key;
        e.ptree = x;
        
        printf("%d + %d -> %d\n", e1.key, e2.key, e.key);

        // 최소 힙에 삽입
        insertMinHeap(heap, e);
    }

    e = extractMin(heap); // 최종 트리
    printf("Total length = %d\n", e.key);

    int codes[100];
    printCode(e.ptree, codes, 0);
    
    /**
     * 허프만 코드를 저장하여 인코딩 디코딩 해볼 목적
    */
    encodingRoot = e.ptree; // 전역변수에 최종 트리 저장
    char code[MAX_CODE_LENGTH];
    storeCodes(e.ptree, code, 0);

    free(heap);
}

TreeNode * makeTree(TreeNode *left, TreeNode *right)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

Heap * createHeap()
{
    return (Heap *)malloc(sizeof(Heap));
}

void init(Heap *heap)
{
    heap->size = 0;
}

void insertMinHeap(Heap *heap, element value)
{
    if (heap->size == MAX_ELEMENT) // 더이상 원소를 저장할 수 없음
    {
        printf("Heap is full\n");
        return;
    }

    heap->arr[heap->size] = value;
    
    // 힙구조 만들기 (최소 힙) - shift up - 부모노드와 비교하여 자식노드가 더 크면 교환
    shiftUp(heap, heap->size);

    heap->size++;
}

void shiftUp(Heap *heap, int childIndex) 
{
    int parentIndex = (childIndex - 1) / 2;

    if (parentIndex >= 0 && heap->arr[parentIndex].key > heap->arr[childIndex].key) 
    {
        element temp = heap->arr[parentIndex];
        heap->arr[parentIndex] = heap->arr[childIndex];
        heap->arr[childIndex] = temp;

        shiftUp(heap, parentIndex);
    }
}

element extractMin(Heap *heap)
{
    if (heap->size == 0)
    {
        printf("Heap is empty\n");
        element e = {NULL, -1, -1};
        return e;
    }
    element min = heap->arr[0];

    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    shiftDown(heap, 0);

    return min;
}

void shiftDown(Heap *heap, int parentIndex) 
{
    int leftChildIndex = parentIndex * 2 + 1;
    int rightChildIndex = leftChildIndex + 1;
    int smallIndex = parentIndex; // 기본값을 parentIndex로 설정

    if (leftChildIndex < heap->size && heap->arr[leftChildIndex].key < heap->arr[smallIndex].key)
    {
        smallIndex = leftChildIndex;
    }

    if (rightChildIndex < heap->size && heap->arr[rightChildIndex].key < heap->arr[smallIndex].key) 
    {
        smallIndex = rightChildIndex;
    }

    if (smallIndex != parentIndex) 
    {
        element temp = heap->arr[smallIndex];
        heap->arr[smallIndex] = heap->arr[parentIndex];
        heap->arr[parentIndex] = temp;

        shiftDown(heap, smallIndex);
    }
}

void printCode(TreeNode *root, int codes[], int top)
{
    if (root->left)
    {
        codes[top] = 0;
        printCode(root->left, codes, top + 1);
    }

    if (root->right)
    {
        codes[top] = 1;
        printCode(root->right, codes, top + 1);
    }

    if (root->left == NULL && root->right == NULL)
    {
        printf("%c: ", root->ch); // 5출력 
        for (int i = 0; i < top; i++)
        {
            printf("%d", codes[i]);
        }
        printf("\n");
    }
}

void destroyTree(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

void storeCodes(TreeNode *root, char *code, int length) {
    if (root == NULL) return;

    // 리프 노드에 도달했을 때 코드 저장
    if (root->left == NULL && root->right == NULL) {
        huffmanCodes[codeIndex].ch = root->ch;
        strncpy(huffmanCodes[codeIndex].code, code, length);
        huffmanCodes[codeIndex].code[length] = '\0'; // 문자열 끝에 null 추가
        codeIndex++;
        return;
    }

    // 왼쪽 자식 노드로 이동
    if (root->left) {
        code[length] = '0';
        storeCodes(root->left, code, length + 1);
    }

    // 오른쪽 자식 노드로 이동
    if (root->right) {
        code[length] = '1';
        storeCodes(root->right, code, length + 1);
    }
}

void encode(char *str, char *encodedStr) 
{
    encodedStr[0] = '\0'; // 인코딩된 문자열 초기화
    for (int i = 0; str[i] != '\0'; i++) 
    {
        for (int j = 0; j < codeIndex; j++) 
        {
            if (str[i] == huffmanCodes[j].ch) 
            {
                strcat(encodedStr, huffmanCodes[j].code);
                break;
            }
        }
    }
}


void decode(TreeNode *root, char *encodedStr, char *decodedStr) 
{
    TreeNode *current = root;
    int index = 0;
    while (*encodedStr) 
    {
        if (*encodedStr == '0')
        {
            current = current->left;
        } 
        else if (*encodedStr == '1') 
        {
            current = current->right;
        }
        if (current->left == NULL && current->right == NULL) 
        {
            decodedStr[index++] = current->ch;
            current = root; // 다시 루트로
        }
        encodedStr++;
    }
    decodedStr[index] = '\0'; // 문자열 끝
}

void encodingDecodingPrint(char *randomString)
{
    // 인코딩된 문자열 저장을 위한 배열
    char encodedStr[1000] = {0};
    // 디코딩된 문자열 저장을 위한 배열
    char decodedStr[1000] = {0};

    // 인코딩
    printf("Before String: %s\n", randomString);
    encode(randomString, encodedStr);
    printf("Encoded String: %s\n", encodedStr);

    // 디코딩
    decode(encodingRoot, encodedStr, decodedStr); // huffmanCodes[0].ptree는 최종 허프만 트리의 루트 노드
    printf("Decoded String: %s\n", decodedStr);
}