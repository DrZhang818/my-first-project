#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *son, *sibling;
} Node;

typedef struct {
    Node *p;
    int d;
} Info;

Node* newNode(char c) {
    Node *res = (Node *)calloc(1, sizeof(Node));
    res->data = c;
    return res;
}

void preOrder(Node *u) {
    if(!u) return;
    printf("%c ", u->data);
    preOrder(u->son);
    preOrder(u->sibling);
}

int main() {
    int n;
    scanf("%d", &n);

    Info *q = (Info *)malloc(n * sizeof(Info));
    int head = 0, tail = 0;
    
    char val;
    int deg;
    scanf(" %c %d", &val, &deg);
    Node *root = newNode(val);
    q[tail++] = (Info){root, deg};
    while(head < tail) {
        Info t = q[head++];
        Node *pre = NULL;
        for(int i = 0; i < t.d; i++) {
            scanf(" %c %d", &val, &deg);
            Node *cur = newNode(val);
            if(i == 0) {
                t.p->son = cur;
            } else {
                pre->sibling = cur;
            }
            pre = cur;
            q[tail++] = (Info){cur, deg};
        }
    }

    preOrder(root);

    return 0;
}