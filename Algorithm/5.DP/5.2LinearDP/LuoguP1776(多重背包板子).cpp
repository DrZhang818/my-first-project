#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



struct info {
    int v, w, m;
};
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<info> a(n + 1);
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].v >> a[i].w >> a[i].m;
        sum += a[i].w;
    }
    vector<int> V(sum + 1), W(sum + 1);
    int idx = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= a[i].m; j <<= 1) {
            V[++idx] = a[i].v * j;
            W[idx] = a[i].w * j;
            a[i].m -= j;
        }
        if(a[i].m) {
            V[++idx] = a[i].v * a[i].m;
            W[idx] = a[i].w * a[i].m;
        }
    }
    vector<int> dp(m + 1);
    for(int i = 1; i <= idx; i++) {
        for(int j = m; j >= W[i]; j--) {
            dp[j] = max(dp[j], dp[j - W[i]] + V[i]);
        }
    }
    cout << dp[m] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

