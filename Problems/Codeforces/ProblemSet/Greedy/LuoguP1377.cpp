#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), p(n + 1);   
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        p[a[i]] = i;
    }
    vector<int> ls(n + 1), rs(n + 1);
    vector<int> stk(n + 1);
    int top = 0;
    for(int i = 1; i <= n; i++) {
        int k = 0;
        while(top && p[i] < p[stk[top]]) {
            k = stk[top--];
        }
        if(top) {
            rs[stk[top]] = i;
        }
        if(k) {
            ls[i] = k;
        }
        stk[++top] = i;
    }
    int rt = stk[1];
    auto dfs = [&](this auto &&self, int u) -> void {
        cout << u << " ";
        if(ls[u]) self(ls[u]);
        if(rs[u]) self(rs[u]);
    };
    dfs(rt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
