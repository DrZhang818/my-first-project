#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int a, b;
    friend bool operator < (const info &a, const info &b) {
        return a.b > b.b;
    }
};
void solve() {
    int n;
    cin >> n;
    priority_queue<info> q;
    for(int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        q.push({a, b});
    }
    ll cur = 0;
    while(!q.empty()) {
        auto [a, b] = q.top(); q.pop();
        cur += a;
        if(cur > b) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
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
