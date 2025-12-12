#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

PII query(int i, int j) {
    cout << "? " << i << " " << j << endl;
    int u, v;
    cin >> u >> v;
    return {u, v};
}

void answer() {
    cout << "!" << endl;
}

void solve() {  
    int n;
    cin >> n;
    vector<int> pos(n + 1);
    vector<int> p(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
        pos[p[i]] = i;
    }
    for(int i = 1; i <= n / 2; i++) {
        int &x = pos[i], &y = pos[n - i + 1];
        while(x != i) {
            auto [u, v] = query(x, i);
            swap(pos[p[u]], pos[p[v]]);
            swap(p[u], p[v]);
        }
        int t = y;
        while(x != i || y != n - i + 1) {
            auto [u, v] = query(t, n - i + 1);
            swap(pos[p[u]], pos[p[v]]);
            swap(p[u], p[v]);
        }
    }
    answer();
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
