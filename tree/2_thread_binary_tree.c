#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
    int isThread; // 만약 오른쪽 링크가 스레드면 TRUE - 추가 된 부분
}TreeNode;

void threadInorder(TreeNode *t);
TreeNode * findSuccessor(TreeNode *p);

//       G
//   C      F
// A   B  D   E
TreeNode n1 = {'A', NULL, NULL, FALSE};
TreeNode n2 = {'B', NULL, NULL, FALSE};
TreeNode n3 = {'C', &n1, &n2, FALSE};
TreeNode n4 = {'D', NULL, NULL, FALSE};
TreeNode n5 = {'E', NULL, NULL, FALSE};
TreeNode n6 = {'F', &n4, &n5, FALSE};
TreeNode n7 = {'G', &n3, &n6, FALSE};
TreeNode *root = &n7;

/**
 * 스레드 이진트리
 * - 노드들을 동적이 아닌 정적으로 생성
*/
int main()
{
    // 스레드 설정
    n1.right = &n3; // A의 오른쪽 링크를 C로 설정
    n1.isThread = TRUE; // A의 오른쪽 링크가 스레드임을 설정
    n2.right = &n7; // B의 오른쪽 링크를 G로 설정
    n2.isThread = TRUE; // B의 오른쪽 링크가 스레드임을 설정
    n4.right = &n6; // D의 오른쪽 링크를 F로 설정
    n4.isThread = TRUE; // D의 오른쪽 링크가 스레드임을 설정

    // 스레드 중위순회
    threadInorder(root);
    printf("\n");

    return 0;
}

TreeNode * findSuccessor(TreeNode *p)
{
    TreeNode *q = p->right;
    if (q == NULL || p->isThread == TRUE) // 오른쪽 링크가 NULL이거나 스레드이면
    {
        return q;
    }
    while (q->left != NULL) // 오른쪽 자식의 왼쪽 자식이 NULL이 아니면
    {
        q = q->left; // 왼쪽 자식으로 이동
    }
    return q;
}

void threadInorder(TreeNode *t)
{
    TreeNode *q;
    q = t;

    while (q->left) // 가장 왼쪽 노드로 이동
    {
        q = q->left;
    }

    do
    {
        printf("%c -> ", q->data); // 데이터 출력
        q = findSuccessor(q); // 후속자 함수 호출
    } while (q); // 후속자가 NULL이 아니면 반복
}