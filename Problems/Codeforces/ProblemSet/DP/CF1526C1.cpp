#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/problemset/problem/1526/C2
constexpr ll inf = 1e18;
void solve() { 
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    priority_queue<ll> pq;
    ll ans = 0, cur = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] >= 0) {
            ans++;
            cur += a[i];
        } else {
            if(cur + a[i] >= 0) {
                ans++;
                cur += a[i];
                pq.push(-a[i]);
            } else if(!pq.empty() && -a[i] < pq.top()) {
                cur += a[i] + pq.top();
                pq.pop();
                pq.push(-a[i]);
            }
        }
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
    
