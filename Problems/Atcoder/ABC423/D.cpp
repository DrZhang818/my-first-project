#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    ll time, c;
    friend bool operator < (const info &a, const info &b) {
        return a.time > b.time;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    priority_queue<info> q; 
    ll cur = 0, T = 0;
    for(int i = 1; i <= n; i++) {
        ll st, len, cnt;
        cin >> st >> len >> cnt;
        while(!q.empty() && cur + cnt > k) {
            auto [time, c] = q.top(); q.pop();
            cur -= c;
            T = time;
        }
        T = max(T, st);
        cout << T << "\n";
        q.push({T + len, cnt});
        cur += cnt;
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
