#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int a, id;
};
void solve() {
    int n;
    cin >> n;
    vector<int> w(n);
    for(int i = 0; i < n; i++) {
        cin >> w[i];
    }
    int q;
    cin >> q;
    int B = sqrt(n);
    vector<ll> ans(q);
    vector<vector<info>> Q(B);
    for(int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        if(b < B) {
            Q[b].emplace_back(a, i);
        } else {
            ll sum = 0;
            for(int i = a; i < n; i += b) {
                sum += w[i];
            }
            ans[i] = sum;
        }
    }
    vector<ll> pre(n);
    for(int b = 1; b < B; b++) {
        if(Q[b].empty()) continue;
        for(int i = 0; i < n; i++) {
            pre[i] = w[i];
            if(i >= b) {
                pre[i] += pre[i - b];
            }
        }
        for(auto [a, id] : Q[b]) {
            int r = n - 1 - (n - 1 - a) % b;
            ans[id] = pre[r] - pre[a] + w[a];
        }
    }
    for(int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
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
