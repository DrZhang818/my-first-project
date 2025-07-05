#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    string s;
    cin >> s;
    priority_queue<int> q;
    int ca = 0, cb = 0;
    for(char c : s) {
        if(c == 'A') {
            ca++;
        } else {
            cb++;
            q.push(ca);
            ca = 0;
        }
    }
    q.push(ca);
    ll ans = 0;
    while(!q.empty() && cb) {
        ans += q.top();
        q.pop();
        cb -= 1;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
