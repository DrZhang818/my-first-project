#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


typedef struct info {
    char name[10];
    int id;
    char job[10];
} info ;

typedef struct node {
    node* nxt;
    info x;
} node ;

node* st;
void add(info o) {
    node* cur = st;
    while(cur->nxt) {
        cur = cur->nxt;
    }
    node* now = (node*)malloc(sizeof(node));
    now->nxt = NULL;
    now->x = o;
    cur->nxt = now;
}

bool equal(info a, info b) {
    return strcmp(a.name, b.name) == 0 && a.id == b.id && strcmp(a.job, b.job) == 0;
}
void erase(info o) {
    node* cur = st;
    while(cur->nxt && !equal(cur->nxt->x, o)) {
        cur = cur->nxt;
    }
    if(cur->nxt) {
        node* t = cur->nxt;
        cur->nxt = cur->nxt->nxt;
        free(t);
    }
}
void print() {
    node* cur = st;
    while(cur->nxt) {
        cur = cur->nxt;
        printf("%s %d %s\n", cur->x.name, cur->x.id, cur->x.job);
    }
    printf("\n");
}

int main() {

    int n;
    scanf("%d", &n);

    st = (node*)malloc(sizeof(node));
    st->nxt = NULL;

    for(int i = 1; i <= n; i++) {
        int op;
        scanf("%d", &op);
        info cur;
        scanf("%s", cur.name);
        scanf("%d", &cur.id);
        scanf("%s", cur.job);
        if(op == 1) {
            add(cur);
        } else {
            erase(cur);
        }
        print();
    }

    return 0;
}
