#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int x;
    cin >> x;
    int ans = 0;
    priority_queue<int, vector<int>, greater<int>> q;
    for(int i = 0; i < 3; i++) q.push(0);
    while(1) {
        int u = q.top(); q.pop();
        if(u == x) break;
        int v = q.top();
        q.push(min(x, v << 1 | 1));
        ans++;
    }   
    cout << ans << "\n";
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
