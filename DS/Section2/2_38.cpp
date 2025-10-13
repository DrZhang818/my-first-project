#include <stdio.h>
#include <stdlib.h>
const int inf = 1000000000;
const int N = 2E5 + 10;

typedef struct node {
    struct node *nxt, *pre;
    int val, cnt;
} node ;


void Swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
} 

void locate(node* st, int x) {
    if(st->nxt == NULL) return;
    node* cur = st;
    do {
        cur = cur->nxt;
    } while(cur->nxt != st->nxt && cur->val != x);
    if(cur->nxt == st->nxt && cur->val != x) return;
    cur->cnt++;
    while(cur != st->nxt && cur->pre->cnt < cur->cnt)
    {
        Swap(&cur->cnt, &cur->pre->cnt);
        Swap(&cur->val, &cur->pre->val);
        cur = cur->pre;
    }
}

void solve() {
    int n;
    scanf("%d", &n);
    node* st = (node*)malloc(sizeof(node));
    st->nxt = NULL;
    node* cur = st;

    for(int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        node* p = (node*)malloc(sizeof(node));
        p->val = x;
        p->pre = cur;
        p->cnt = 0;
        cur->nxt = p;
        cur = cur->nxt;
    }
    cur->nxt = st->nxt, st->nxt->pre = cur;

    int q;
    scanf("%d", &q);
    while(q--) {
        int x;
        scanf("%d", &x);
        locate(st, x);
        node* cur = st;
        do {
            cur = cur->nxt;
            printf("(%d,%d) ", cur->val, cur->cnt);
            
        } while(cur->nxt != st->nxt);
        printf("\n");
    }

}

int main() {

    solve();
    return 0;    
}