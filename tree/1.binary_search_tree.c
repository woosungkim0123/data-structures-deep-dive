#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct TreeNode
{
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode * addNode(TreeNode *root, int data);
TreeNode * searchNode(TreeNode *root, int data);


int main()
{
    setlocale(LC_ALL, "Korean");

    TreeNode *root = NULL;
    int choice;
    int data;
    while (1)
    {
        system("cls");
        printf("\n\n\t\t*** Binary Search Tree(BST) ***\n\n");
        printf("1. insert node\n");
        printf("2. delete node\n");
        printf("3. search node\n");
        printf("4. 최댓값 구하기\n");
        printf("5. 최소값 구하기\n");
        printf("6. print all (inorder)\n");
        printf("0. program exit\n");
        printf("\n메뉴 선택 : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\n\n삽입할 정수 입력 : ");
            scanf("%d", &data);
            
            addNode(root, data);

            break;
        case 2:
            break;
        case 3:
            printf("\n\n검색할 정수 입력 : ");
            scanf("%d", &data);

            searchNode(root, data);

            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 0:
            exit(0);
        }
        printf("\n\n\t\t");
        system("pause");
    }

    
    return 0;
}

TreeNode * addNode(TreeNode *t, int data)
{
    if (t == NULL)
    {
        t = (TreeNode *) malloc(sizeof(TreeNode));
        t->value = data;
        t->left;
        t->right;
    }
    else if (t->value > data) // 왼쪽
    {
        t->left = addNode(t->left, data);
    }
    else if (t->value < data) // 오른쪽
    {
        t->right = addNode(t->right, data);
    }
    else
    {
        printf("exist duplicated node.\n");
    }
   
    return t;
}

TreeNode * searchNode(TreeNode *t, int data)
{

}