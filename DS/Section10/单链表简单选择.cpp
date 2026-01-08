#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *nxt;
} Node;

void selectionSort(Node *head) {
    for(Node *i = head; i != NULL; i = i->nxt) {
        Node *m = i;
        for(Node *j = i->nxt; j != NULL; j = j->nxt) {
            if(j->val < m->val) {
                m = j;
            }
        }
        int t = i->val;
        i->val = m->val;
        m->val = t;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Node *head = NULL, *cur = NULL;
    for(int i = 1; i <= n; i++) {
        Node *p = (Node *)malloc(sizeof(Node));
        scanf("%d", &p->val);
        p->nxt = NULL;
        if(head == NULL) {
            head = cur = p;
        } else {
            cur->nxt = p;
            cur = p;
        }
    }

    selectionSort(head);

    for(Node *i = head; i != NULL; i = i->nxt) {
        printf("%d ", i->val);
    }
    printf("\n");
}