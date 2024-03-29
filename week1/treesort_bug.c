/* treesort_bug.c */
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node *left;
    struct node *right;
};

void AddTree(struct node **, int);
void WalkTree(struct node *);
void FreeTree(struct node *);

/* Tree sort */
int main(void)
{
    struct node *rootp = 0x0; //Fix: 0x1 -> 0x0. Because pp is allocated in address 0x0
    int i;
    int array[15] = {50, 12, 18, 70, 41, 19, 91, 1, 7, 6, 81, 65, 55, 20, 0};

    for (i = 0; i < 15; i++)
    {
        AddTree(&rootp, array[i]);
    }

    WalkTree(rootp);
    printf("\n");

    FreeTree(rootp);

    return 0;
}

void AddTree(struct node **pp, int val)
{
    /* create new node if *p is null */
    if (*pp == (struct node *)0)
    {
        *pp = (struct node *)malloc(sizeof(struct node));
        (*pp)->value = val;
    }
    else if ((*pp)->value > val)
    {
        AddTree(&(*pp)->left, val);
    }
    else if ((*pp)->value < val)
    {
        AddTree(&(*pp)->right, val);
    }
    else
    {
        /* do nothing */
    }
}

void WalkTree(struct node *p)
{
    //Fix: check if p is null or not
    if(p != NULL)
    {
        WalkTree(p->left);
        printf("%d ", p->value);
        WalkTree(p->right);
    }
}

void FreeTree(struct node *p)
{
    //Fix: check if p is NULL then return
    if(p == NULL) return;

    FreeTree(p->left);
    FreeTree(p->right);
    free(p);
    return;
}
