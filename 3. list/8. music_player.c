#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];
typedef struct DListNode {
    element data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

DListNode* current;

void init(DListNode* phead)
{
    phead->llink = phead;
    phead->rlink = phead;
}

void print_dlist(DListNode* phead)
{
    DListNode* p;
    for (p = phead->rlink; p != phead; p = p->rlink) {
        if (p == current) {
            printf("<-#### %s ####->", p->data);
        } else {
            printf("<----- %s ----->", p->data);
        }
        printf("\n");
    }
}

void dinsert(DListNode *before, element data)
{
    DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
    strcpy(newnode->data, data);
    
    newnode->llink = before;
    newnode->rlink = before->rlink;
    
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

int main() 
{
    char ch;
    
    DListNode* head = (DListNode *)malloc(sizeof(DListNode));
    init(head);
    
    dinsert(head, "Change");
    dinsert(head, "Love Someone");
    dinsert(head, "Thank u, next");
    
    current = head->rlink;
    print_dlist(head);
    
    do {
        printf("\n insert command(<, >, q): ");
        ch = getchar();
        
        if (ch == '<') {
            current = current->llink;
            if (current == head) {
                current = current->llink;
            }
        } else if (ch == '>') {
            current = current->rlink;
            if (current == head) {
                current = current->rlink;
            }
        }
        print_dlist(head);
        getchar();
        
    } while (ch != 'q');
    
    return 0;
}