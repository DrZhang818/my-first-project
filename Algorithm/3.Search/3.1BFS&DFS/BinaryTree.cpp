#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



struct node {
    int val;
    int l, r;
};
void solve(){ 
    int n;
    cin >> n;
    vector<node> tree(n + 1);
    int idx = 0;
    auto new_node = [&](int x) -> int {
        tree[++idx].val = x;
        return idx; 
    };
    auto addEdge = [&](int fa, int son, int flag) -> void {
        if(!flag) tree[fa].l = son;
        else tree[fa].r = son;
    };
    int A = new_node(1), B = new_node(2), C = new_node(3), D = new_node(4);
    int E = new_node(5), F = new_node(6), G = new_node(7), H = new_node(8);
    addEdge(A, B, 0), addEdge(A, C, 1), addEdge(B, D, 0), addEdge(B, E, 1);
    addEdge(C, F, 0), addEdge(C, G, 1), addEdge(F, H, 0);
    int root = A;
    auto dfs = [&](this auto &&dfs, int fa) -> void {
        if(fa == 0) return;
        cout << tree[fa].val << " ";
        dfs(tree[fa].l);
        dfs(tree[fa].r);
    };
    dfs(root);
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

