#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr int inf = 1000000000;
struct info {
    db x, y;
};
vector<info> a;
db work(int i, int j) {
    return sqrt((a[i].x - a[j].x) * (a[i].x - a[j].x) + (a[i].y - a[j].y) * (a[i].y - a[j].y));
}
void solve() { 
    int n;
    cin >> n;
    a.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    vector dp(n + 1, vector<db>(1 << n, inf));
    for(int i = 1; i <= n; i++) dp[i][1 << (i - 1)] = sqrt(a[i].x * a[i].x + a[i].y * a[i].y); 
    for(int s = 1; s < 1 << n; s++) {
        for(int i = 1; i <= n; i++) {
            if(s >> (i - 1) & 1) {
                for(int j = 1; j <= n; j++) {
                    if((s ^ (1 << (i - 1))) >> (j - 1) & 1) {
                        dp[i][s] = min(dp[i][s], dp[j][s ^ (1 << i - 1)] + work(i, j));
                    }
                }
            }
        }
    }
    db ans = inf;
    for(int i = 1; i <= n; i++) ans = min(ans, dp[i][(1 << n) - 1]);
    cout << fixed << setprecision(2) << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
