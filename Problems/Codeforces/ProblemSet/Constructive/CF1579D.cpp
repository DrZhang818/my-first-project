#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/problemset/problem/1579/D
void solve() { 
    int n;
    cin >> n;
    priority_queue<PII> pq;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x == 0) continue;
        pq.push({x, i});
    }
    vector<PII> ans;
    ans.reserve(100005);
    while(pq.size() > 1) {
        PII u = pq.top();
        pq.pop();
        PII v = pq.top();
        pq.pop();
        ans.emplace_back(u.second, v.second);
        if(u.first > 1) pq.push({u.first - 1, u.second});
        if(v.first > 1) pq.push({v.first - 1, v.second});
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
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
    
