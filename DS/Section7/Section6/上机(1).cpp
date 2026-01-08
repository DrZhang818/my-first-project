#include <stdio.h>
#include <stdlib.h>
const int N = 1000000;

int stk[N + 1];
int T1 = 0;
void stk_push(int o) {
    stk[++T1] = o;
}
int stk_pop() {
    return stk[T1--];
}
int stk_top() {
    return stk[T1];
}
bool stk_empty() {
    return T1 == 0;
}

int q[N + 1];
int S = 1, T2 = 0;
void que_push(int o) {
    q[++T2] = o;
}
int que_pop() {
    return q[S++];
}
int que_front() {
    return q[S];
}
bool que_empty() {
    return S > T2;
}

typedef struct {
    char val;
    int lson, rson;
} info;

info tr[N + 1];
char seq[N + 1];

int idx = 1, sz = 1;
void build(int u) {
    tr[u].val = seq[idx];
    tr[u].lson = tr[u].rson = 0;
    if(seq[++idx] != '.') {
        tr[u].lson = ++sz;
        build(sz);
    }
    if(seq[++idx] != '.') {
        tr[u].rson = ++sz;
        build(sz);
    }
}

void pre_order(int u) {
    printf("%c", tr[u].val);
    if(tr[u].lson) pre_order(tr[u].lson);
    if(tr[u].rson) pre_order(tr[u].rson);
    if(u == 1) printf("\n");
}

void in_order(int u) {
    if(tr[u].lson) in_order(tr[u].lson);
    printf("%c", tr[u].val);
    if(tr[u].rson) in_order(tr[u].rson);
    if(u == 1) printf("\n");
}

void post_order(int u) {
    if(tr[u].lson) in_order(tr[u].lson);
    if(tr[u].rson) in_order(tr[u].rson);
    printf("%c", tr[u].val);
    if(u == 1) printf("\n");
}

void in_order2(int u) {
    do {
        while(u) {
            stk_push(u);
            u = tr[u].lson;
        }
        if(!stk_empty()) {
            u = stk_pop();
            printf("%c", tr[u].val);
            u = tr[u].rson;
        }
    } while(!stk_empty() || u);
    printf("\n");
}

void bfs(int rt) {
    que_push(rt);
    while(!que_empty()) {
        int u = que_pop();
        printf("%c", tr[u].val);
        if(tr[u].lson) que_push(tr[u].lson);
        if(tr[u].rson) que_push(tr[u].rson);
    }
    printf("\n");
}

int max(int a, int b) { return a >= b ? a : b; }

int get_depth(int u) {
    if(u == 0) return 0;
    return 1 + max(get_depth(tr[u].lson), get_depth(tr[u].rson));
}

void solve() {
    scanf("%s", seq + 1);
    build(1);
    pre_order(1);
    in_order(1);
    post_order(1);
    in_order2(1);
    bfs(1);
    printf("%d\n", get_depth(1));
}

int main() {
    solve();
    return 0;
}