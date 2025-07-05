#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr int N = 100005;
void solve() { 
    int n;
    cin >> n;
    vector<ll> a(N);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[x]++;
    }
    vector<vector<ll>> dp(N, vector<ll>(2, 0));
    for(int i = 1; i <= 100000; i++) {
        dp[i][1] = max(dp[i - 1][0] + a[i] * i, dp[i - 1][1]);
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
    }
    cout << max(dp[100000][0], dp[100000][1]) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
