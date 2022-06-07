#include <stdio.h>
#include <stdlib.h>

typedef char *data;
typedef int keyType;

struct tree {
    keyType key;
    data info;
    struct tree *left;
    struct tree *right;
};

/* Търсене в двоично дърво */
struct tree *search(keyType key, struct tree *T)
{ if (NULL == T)
        return NULL;
    else if (key < T->key)
        return search(key, T->left);
    else if (key > T->key)
        return search(key, T->right);
    else
        return T;
}

/* Включване в двоично дърво */
void insertKey(keyType key, data x, struct tree **T)
{ if (NULL == *T) {
        *T = (struct tree *) malloc(sizeof(**T));
        (*T)->key = key;
        (*T)->info = x;
        (*T)->left = NULL;
        (*T)->right = NULL;
    }
    else if (key < (*T)->key)
        insertKey(key, x, &(*T)->left);
    else if (key > (*T)->key)
        insertKey(key, x, &(*T)->right);
    else
        fprintf(stderr, "Element is already in the tree!\n");
}

/* Изключване от двоично дърво Ј */

/* Намиране на минималния елемент в дърво */
struct tree *findMin(struct tree *T)
{ while (NULL != T->left) T = T->left;
    return T;
}

void deleteKey(keyType key, struct tree **T)
{ if (NULL == *T) {
        fprintf(stderr, "Element not found! \n");
    } else {
        if (key < (*T)->key)
            deleteKey(key, &(*T)->left);
        else if (key > (*T)->key)
            deleteKey(key, &(*T)->right);
        else  /* елемента за изключване е намерен */
        if ((*T)->left && (*T)->right) {       /* елементът има и ляво и дясно поддърво */
            /* намира се върхът за размяна */
            struct tree *replace = findMin((*T)->right);
            (*T)->key = replace->key;
            (*T)->info = replace->info;
            deleteKey((*T)->key, &(*T)->right);    /* върхът се изключва */
        }
        else {  /* елементът има нула или едно поддървета */
            struct tree *temp = *T;
            if ((*T)->left)
                *T = (*T)->left;
            else
                *T = (*T)->right;
            free(temp);
        }
    }
}

void printTree(struct tree *T)
{ if (NULL == T) return;
    printf("%d-l>", T->key);
    printTree(T->left);

    printf("\n%d-r>", T->key);
    printTree(T->right);
}
int random(int max)
{
    return rand() % max;
}

int findDepth(struct tree *origin)
{
    if(origin!=NULL)
    {
        int temp1 =findDepth(origin->left)+1;
        int temp2= findDepth(origin->right)+1;
        return temp1>temp2 ? temp1 : temp2;
    }
}


int treePower(struct tree *src)
{
    if(src!=NULL)
    {
        int left = treePower(src->left)+1;
        int right = treePower(src->right)+1;
        printf("\nCounting elem: %d",src->key);
        return left+right;
    }
    return 0;
}

int countTreeNodes(struct tree *t,int *count)
{
    if(t!=NULL)
    {
        countTreeNodes(t->left, count);
        countTreeNodes(t->right, count);
        (*count)++;
    }
}

void countLeaves(struct tree *src,int *storage)
{
    if(src!=NULL)
    {
        if(src->left==NULL && src->right==NULL)
        {
            (*storage)++;
        }
        countLeaves(src->left,storage);
        countLeaves(src->right,storage);
    }
}


int main(void) {
    struct tree *T = NULL, *result;
    int i;

    insertKey(5, "five", &T);
    insertKey(3, "three", &T);
    insertKey(1, "one", &T);
    insertKey(4, "four", &T);
    insertKey(2, "two", &T);
    insertKey(6, "six", &T);
    insertKey(7, "seven", &T);
    insertKey(8, "eight", &T);
    insertKey(9, "nine", &T);
    insertKey(10, "ten", &T);
    insertKey(11, "eleven", &T);

    printf("Tree: ");

    printTree(T);

    printf("\n Depth %d",findDepth(T));
    printf("\n");
    int test =0;
    countTreeNodes(T,&test);
    printf("\n Power %d",test);
    printf("\n");
    int leaves =0;
    countLeaves(T,&leaves);
    printf("\n Leaves %d",leaves);
    return 0;
}