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
    vector<int> dp(n + 1);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        dp[a[i]] = dp[a[i] - 1] + 1;
        ans = max(ans, dp[a[i]]);
    }
    cout << n - ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
