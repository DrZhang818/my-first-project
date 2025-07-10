#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc131/tasks/abc131_f
const int N = 100000;
int fa[2 * N + 1], r[2 * N + 1], c[2 * N + 1];
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) { fa[find(u)] = find(v); }
void solve() {
    int n;
    cin >> n;
    for(int i = 1; i <= 2 * N; i++) fa[i] = i;
    for(int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        merge(x, y + N);
    }
    for(int i = 1; i <= N; i++) {
        r[find(i)]++;
        c[find(i + N)]++;
    }
    ll ans = 0;
    for(int i = 1; i <= 2 * N; i++) {
        ans += 1LL * r[i] * c[i];
    }
    cout << ans - n << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
