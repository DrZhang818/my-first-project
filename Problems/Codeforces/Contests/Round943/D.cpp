#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, k, u, v;
    cin >> n >> k >> u >> v;
    vector<int> p(n + 1), a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    } 
    ll x = 0, y = 0;
    vector<int> v1, v2;
    vector<bool> vis1(n + 1), vis2(n + 1);
    while(!vis1[u]) {
        vis1[u] = true;
        v1.push_back(a[u]);
        u = p[u];
    }
    while(!vis2[v]) {
        vis2[v] = true;
        v2.push_back(a[v]);
        v = p[v];
    }
    ll sum1 = 0, sum2 = 0;
    for(int i = 0; i < v1.size() && i < k; i++) {
        x = max(x, sum1 + (ll)(k - i) * v1[i]);
        sum1 += v1[i];
    }
    for(int i = 0; i < v2.size() && i < k; i++) {
        y = max(y, sum2 + (ll)(k - i) * v2[i]);
        sum2 += v2[i];
    }
    if(x > y) {
        cout << "Bodya\n";
    } else if(x < y) {
        cout << "Sasha\n";
    } else {
        cout << "Draw\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
