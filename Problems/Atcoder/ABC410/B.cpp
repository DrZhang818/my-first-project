#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int cnt, id;
    friend bool operator < (const info &a, const info &b) {
        if(a.cnt != b.cnt) return a.cnt > b.cnt;
        return a.id > b.id;
    }    
};
void solve() {
    int n, q;
    cin >> n >> q;
    priority_queue<info> pq;
    for(int i = 1; i <= n; i++) {
        pq.push({0, i});
    }
    vector<int> ans(q + 1);
    vector<int> c(n + 1);
    for(int i = 1; i <= q; i++) {
        int x;
        cin >> x;
        if(x >= 1) {
            ans[i] = x;
            c[x]++;
        } else {
            while(1) {
                auto [cnt, id] = pq.top();
                if(c[id] != cnt) {
                    pq.pop();
                    pq.push({c[id], id});
                } else {
                    break;
                }
            }
            auto [cnt, id] = pq.top(); pq.pop();
            ans[i] = id;
            c[id]++;
            pq.push({cnt + 1, id});
        }
    }
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << " \n"[i == q];
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
