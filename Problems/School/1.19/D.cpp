#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

struct info
{
    int u, v, w;
};
void solve(){
    int n, m1, m2;
    cin >> n >> m1 >> m2;
    int p = __gcd(m1,m2);
    m1 /= p;
    m2 /= p;
    vector<info> in(n);
    int sum1 = 0, sum2 = 0;
    for(int i = 0; i < n; i++){
        cin >> in[i].u >> in[i].v >> in[i].w;
        sum1 += in[i].u;
        sum2 += in[i].v;
    }
    vector<vector<int>> dp(sum1 + 1, vector<int>(sum2 + 1, INT_MAX / 2));
    dp[0][0] = 0;
    for(int p = 0; p < n; p++){
        int u = in[p].u;
        int v = in[p].v;
        int w = in[p].w;
        for(int i = sum1; i >= u; i--){
            for(int j = sum2; j >= v; j--){
                dp[i][j] = min(dp[i][j], dp[i - u][j - v] + w);
            }
        }
    }
    int c = INT_MAX;
    for(int k = 1; k * m1 <= sum1 && k * m2 <= sum2; k++){
        if(dp[k * m1][k * m2] < INT_MAX / 2){
            c = min(c, dp[k * m1][k * m2]);
        }
    }
    if(c != INT_MAX){
        cout << c << "\n";
    }
    else{
        cout << -1 << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}