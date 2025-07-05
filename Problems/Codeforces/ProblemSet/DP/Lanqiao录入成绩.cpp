#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


const int inf = 1000000000;
void solve() { 
    string a;
    cin >> a;
    int n = a.size(), m = 8;
    a = "#" + a;
    unordered_map<string,int> mp;
    mp["G"] = 1, mp["G1"] = 2, mp["G2"] = 4, mp["G3"] = 8;
    mp["GG"] = 16, mp["1"] = 32, mp["2"] = 64, mp["3"] = 128;
    vector<vector<ll>> dp(n + 1, vector<ll>(1 << m, -inf));
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int s = 0; s < 1 << m; s++) {
            if(a[i] == 'G' && (s & 1)) continue;
            string t = {a[i]};
            dp[i][s | mp[t]] = max(dp[i][s | mp[t]], dp[i - 1][s]);
        }
        string t = a.substr(i - 1, 2);
        if(!mp.count(t)) continue;
        for(int s = 0; s < 1 << m; s++) {
            if(t == "G1") dp[i][s | mp[t]] = max(dp[i][s | mp[t]], dp[i - 2][s] + 1);
            else dp[i][s | mp[t]] = max(dp[i][s | mp[t]], dp[i - 2][s]);
        }
    }
    cout << dp[n][(1 << m) - 1] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
