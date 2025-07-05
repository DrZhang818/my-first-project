#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    int N;
    cin >> N;
    vector<int> a(N + 1);
    for(int i = 1; i <= N; i++) {
        cin >> a[i];
    }
    int D, Q;
    cin >> D >> Q;
    int step = (a[N] - a[1] + D - 1) / D;
    int M = log2(step) + 1;
    vector<vector<int>> dp(N + 1, vector<int>(M + 1));
    for(int i = 1; i <= N; i++) {
        int nxt = upper_bound(a.begin() + 1, a.end(), a[i] + D) - a.begin() - 1;
        dp[i][0] = nxt;
        if(nxt > N) dp[i][0] = N;
    }
    for(int s = 1; s <= M; s++) {
        for(int i = 1; i <= N; i++) {
            dp[i][s] = dp[dp[i][s - 1]][s - 1];
        }
    }
    while(Q--) {
        int l, r;
        cin >> l >> r;
        if(l > r) swap(l, r);
        int cur = l;
        int ans = 0;
        for(int s = M; s >= 0; s--) {
            if(dp[cur][s] < r) {
                ans += (1 << s);
                cur = dp[cur][s];
            }
        }
        ans += 1;
        cout << ans << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

