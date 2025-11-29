#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *lson;
    struct node *rson;
} node, *BinaryTree;

BinaryTree build(char pre[], char in[], int preL, int preR, int inL, int inR) {
    if(preL > preR) {
        return NULL;
    }
    BinaryTree root = (BinaryTree)malloc(sizeof(node));
    root->data = pre[preL];

    int k;
    for(k = inL; k <= inR; k++) {
        if(in[k] == root->data) {
            break;
        }
    }

    int numLeft = k - inL;
    root->lson = build(pre, in, preL + 1, preL + numLeft, inL, k - 1);
    root->rson = build(pre, in, preL + numLeft + 1, preR, k + 1, inR);

    return root;
}

BinaryTree build(char pre[], char in[], int n) {
    return build(pre, in, 0, n - 1, 0, n - 1);
}

void print(BinaryTree T) {
    if(T == NULL) return;
    print(T->lson);
    print(T->rson);
    printf("%c", T->data);
}

int main() {
    char pre[] = "ABDEGCF";
    char in[] = "DBGEACF";
    int n = 7;

    BinaryTree T = build(pre, in, n);

    print(T);
    printf("\n");

    return 0;
}