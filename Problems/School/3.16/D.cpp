#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, m;
    cin >> n >> m;
    priority_queue<db> pq;
    for(int i = 1; i <= n; i++) {
        db x;
        cin >> x;
        pq.push(x);
    }
    for(int i = 1; i <= m; i++) {
        db x = pq.top();
        pq.pop();
        pq.push(x / 2);
    }
    ll ans = 0;
    while(!pq.empty()) {
        ans += (int)(pq.top());
        pq.pop();
    }
    cout << ans << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
