#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *l, *r;
} Node;

Node* newNode(int x) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = x;
    node->l = node->r = NULL;
    return node;
}

Node* build(int *pre, int *in, int pl, int pr, int il, int ir) {
    if(pl > pr) return NULL;
    Node *root = newNode(pre[pl]);
    int k = il;
    while(in[k] != pre[pl]) k++;
    int lenL = k - il;
    root->l = build(pre, in, pl + 1, pl + lenL, il, k - 1);
    root->r = build(pre, in, pl + lenL + 1, pr, k + 1, ir);
    return root;
}

void postOrder(Node *u, int *cnt, int n) {
    if (!u) return;
    postOrder(u->l, cnt, n);
    postOrder(u->r, cnt, n);
    (*cnt)++;
    printf("%d%c", u->val, " \n"[*cnt == n]);
}

int main() {
    int n;
    scanf("%d", &n);

    int *pre = (int *)malloc((n + 1) * sizeof(int));
    int *in = (int *)malloc((n + 1) * sizeof(int));
    for(int i = 1; i <= n; i++) scanf("%d", &pre[i]);
    for(int i = 1; i <= n; i++) scanf("%d", &in[i]);

    Node *root = build(pre, in, 1, n, 1, n);

    int cnt = 0;
    postOrder(root, &cnt, n);

    return 0;
}