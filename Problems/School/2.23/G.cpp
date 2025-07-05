#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n, x, y;
    cin >> n >> x >> y;
    priority_queue<int> q;
    for(int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        q.push(v);
    }
    while(x--) {
        int u = q.top();
        q.pop();
        q.push((int)sqrt(u));
    }
    while(y--) {
        int u = q.top();
        q.pop();
        q.push(u / 2);
    }
    ll ans = 0;
    while(!q.empty()) {
        ans += q.top();
        q.pop();
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
    
