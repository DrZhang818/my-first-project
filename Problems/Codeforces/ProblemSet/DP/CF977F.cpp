#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pre(n + 1);
    unordered_map<int,int> dp, idx;
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        dp[a[i]] = dp[a[i] - 1] + 1;
        pre[i] = idx[a[i] - 1];
        if(dp[a[i]] > mx) {
            mx = dp[a[i]];
        }
        idx[a[i]] = i;
    }
    cout << mx << "\n";
    int i = n;
    while(dp[a[i]] != mx) i--;
    stack<int> stk;
    for(; i > 0; i = pre[i]) {
        stk.push(i);
    }
    while(!stk.empty()) {
        cout << stk.top() << " ";
        stk.pop();
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
