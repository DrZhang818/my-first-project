#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


struct node {
    int l, r;
    node(int a = 0, int b = 0) : l(a), r(b) {}
};
void solve(){
    int n;
    cin >> n;
    vector<int> pre(n + 1), mid(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> pre[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> mid[i];
    }
    vector<node> tree(n + 1);
    auto dfs = [&](auto &&dfs, int pl, int pr, int ml, int mr, int i) -> void {
        if(ml > mr) return ;
        int pos = ml;
        while(mid[pos] != i) pos++;
        int lenL = pos - ml, lenR = mr - pos;

        int lson = (lenL > 0) ? pre[pl + 1] : 0;
        int rson = (lenR > 0) ? pre[pl + 1 + lenL] : 0;
        tree[i].l = lson;
        tree[i].r = rson;
        if(lenL > 0) dfs(dfs, pl + 1, pl + lenL, ml, pos - 1, lson);
        if(lenR > 0) dfs(dfs, pl + 1 + lenL, pr, pos + 1, mr, rson);
    };
    dfs(dfs, 1, n, 1, n, pre[1]);
    auto print = [&](auto &&print, int i) -> void {
        if(i == 0) return;
        print(print, tree[i].l);
        print(print, tree[i].r);
        cout << i << " ";
    };
    print(print, pre[1]);
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

