#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode 
{
    int data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode * insert_node(TreeNode * node, int data);
TreeNode * search(TreeNode * node, int data);
TreeNode * new_node(int item);
TreeNode * min_value_node(TreeNode * node);
TreeNode * max_value_node(TreeNode * node);
TreeNode * delete_node(TreeNode * root, int data);
void inorder(TreeNode * root);

int main() 
{
    TreeNode *root = NULL;
    
    root = insert_node(root, 30);
    root = insert_node(root, 20);
    root = insert_node(root, 10);
    root = insert_node(root, 40);
    root = insert_node(root, 50);
    root = insert_node(root, 60);
    
    printf("binary tree inorder result\n");
    
    inorder(root);
    
    printf("\n\n");
    
    int searchvalue = 30;
    
    if (search(root, searchvalue) != NULL) 
    {
        printf("binary tree find %d\n", searchvalue);
    }
    else 
    {
        printf("binary tree not find %d\n", searchvalue);
    }

    root = delete_node(root, 50);

    inorder(root);

    return 0;
}

TreeNode * search(TreeNode * node, int data)
{
    if (node == NULL) 
    {
        return NULL;
    }

    if (data == node->data) 
    {
        return node;
    } 
    else if (data < node->data) 
    {
        return search(node->left, data);
    }
    else 
    {
        return search(node->right, data);
    }
}

TreeNode * new_node(int item)
{
    TreeNode * temp = (TreeNode *)malloc(sizeof(TreeNode));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

TreeNode * insert_node(TreeNode * node, int data)
{
    if (node == NULL) 
    {
        return new_node(data);
    }
    
    if (data < node->data) 
    {
        node->left = insert_node(node->left, data);
    } 
    else if (data > node->data) 
    {
        node->right = insert_node(node->right, data);
    }
    
    return node;
}

TreeNode * min_value_node(TreeNode * node)
{
    TreeNode * current = node;
    
    while(current->left != NULL) 
    {
        current = current->left;
    }
    return current;
}

TreeNode * max_value_node(TreeNode * node)
{
    TreeNode * current = node;
    
    while(current->right != NULL) 
    {
        current = current->right;
    }
    return current;
}

TreeNode * delete_node(TreeNode * t, int data)
{
    if (t == NULL) 
    {
        return t;
    }
    
    TreeNode * temp;

    if (t->data == data)
    {
        if (t->left == NULL && t->right == NULL) // 자식 노드가 없는 경우
        {
            free(t);
            return NULL;
        }
        else if (t->left == NULL || t->right == NULL) // 자식 노드가 하나인 경우
        {
            temp = (t->left == NULL) ? t->right : t->left;
            free(t);
            return temp;
        }
        else // 자식 노드가 두 개인 경우
        {
            // 왼쪽 자식 노드 중 가장 큰 값을 가진 노드를 찾는다.
            temp = max_value_node(t->left);
            t->data = temp->data;
            t->left = delete_node(t->left, temp->data);
        }
    }
    else if (t->data > data)
    {
        t->left = delete_node(t->left, data);
    }
    else
    {
        t->right = delete_node(t->right, data);
    }

    return t;
}


void inorder(TreeNode * root)
{
    if (root != NULL) 
    {
        inorder(root->left);
        printf("[%d] ", root->data);
        inorder(root->right);
    }
}

