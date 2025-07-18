#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> fa, mx;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return;
    fa[u] = v;
    mx[v] = max(mx[u], mx[v]);
}
void solve() {
    int n;
    cin >> n;
    fa.assign(n + 1, 0);
    mx.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mx[i] = a[i];
    }
    vector<int> stk(n + 1);
    int top = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] >= a[stk[top]]) {
            stk[++top] = i;
        } else {
            int t = stk[top];
            while(a[i] < a[stk[top]]) {
                merge(i, stk[top]);
                top--;
            }
            stk[++top] = t;
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << mx[find(i)] << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
