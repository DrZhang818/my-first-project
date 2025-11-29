#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct node {
    char data;
    struct node *firstchild;
    struct node *nxt;
} node, *CSTree;

typedef struct {
    CSTree nodes[MAX_SIZE];
    int front;
    int rear;
} queue;

void Init(queue *q) {
    q->front = 0;
    q->rear = 0;
}

void push(queue *q, CSTree o) {
    if((q->rear + 1) % MAX_SIZE == q->front) {
        return;
    }
    q->nodes[q->rear] = o;
    q->rear = (q->rear + 1) % MAX_SIZE;
}

CSTree pop(queue *q) {
    if(q->front == q->rear) {
        return NULL;
    }
    CSTree o = q->nodes[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    return o;
}

int empty(queue *q) {
    return q->front == q->rear;
}

CSTree build(char a[], int deg[], int n) {
    if(n <= 0) return NULL;
    queue q;
    Init(&q);

    CSTree root = (CSTree)malloc(sizeof(node));
    root->data = a[0];
    root->firstchild = NULL;
    root->nxt = NULL;

    push(&q, root);

    int j = 1, k = 0;
    while(!empty(&q) && j < n) {
        CSTree fa = pop(&q);
        int d = deg[k++];
        if(d == 0) {
            continue;
        }
        CSTree pre = NULL;
        for(int i = 0; i < d; i++) {
            CSTree cur = (CSTree)malloc(sizeof(node));
            cur->data = a[j++];
            cur->firstchild = NULL;
            cur->nxt = NULL;
            push(&q, cur);
            if(i == 0) {
                fa->firstchild = cur;
            } else {
                pre->nxt = cur;
            }
            pre = cur;
        }
    }
    return root;
}


void print(CSTree T, int dep) {
    if(T == NULL) return;
    for(int i = 0; i < dep; i++) {
        printf(" ");
    }
    printf("%c\n", T->data);
    print(T->firstchild, dep + 1);
    print(T->nxt, dep);
}

int main() {
    char datas[] = "ABCDEF";
    int deg[] = {3, 0, 2, 0, 0, 0};
    int n = 6;

    CSTree T = build(datas, deg, n);

    print(T, 0);

    return 0;
}