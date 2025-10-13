#include <stdio.h>
#include <stdlib.h>
const int inf = 1000000000;
const int N = 2E5 + 10;

typedef struct node {
    struct node* nxt;
    int val;
} node ;

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
        p->nxt = NULL;
        cur->nxt = p;
        cur = cur->nxt;
    }
    int mink, maxk;
    scanf("%d %d", &mink, &maxk);
    cur = st;
    while(cur->nxt) {
        node* nxt = cur->nxt;
        if(nxt->val >= maxk) {
            break;
        }
        if(nxt->val > mink) {
            cur->nxt = nxt->nxt;
            free(nxt);
        } else {
            cur = nxt;
        }
    }
    cur = st;
    while(cur->nxt) {
        cur = cur->nxt;
        printf("%d ", cur->val);
    }
    printf("\n");
}

int main() {

    solve();
    return 0;    
}
