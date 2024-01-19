#include <stdio.h>

typedef struct TreeNode 
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

void inorder(TreeNode *root)
{
    if(root != NULL) {
        inorder(root->left);
        printf("[%d] ", root->data); // 중위 순회
        inorder(root->right);
    }    
}

void preorder(TreeNode *root)
{
    if(root != NULL) {
        printf("[%d] ", root->data); // 전위 순회
        preorder(root->left);
        preorder(root->right);
    }    
}

void postorder(TreeNode *root)
{
    if(root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("[%d] ", root->data); // 후위 순회
    }    
}

TreeNode n1 = {1, NULL, NULL};
TreeNode n2 = {4, &n1, NULL};
TreeNode n3 = {16, NULL, NULL};
TreeNode n4 = {25, NULL, NULL};
TreeNode n5 = {20, &n3, &n4};
TreeNode n6 = {15, &n2, &n5};
TreeNode *root = &n6;

int main() 
{
    inorder(root);
    printf("\n");   
    
    preorder(root);
    printf("\n");  
    
    postorder(root);
    printf("\n");
    
    return 0;
}