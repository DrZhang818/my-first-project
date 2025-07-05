#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/problemset/problem/550/C

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> dp(8);
    for(int i = 0; i < n; i++) {
        auto ndp = dp;
        int r = (s[i] - '0') % 8;
        if(ndp[r].empty()){
            ndp[r].push_back(i);
        }
        for(int rem = 0; rem < 8; rem++) {
            if(!dp[rem].empty()){
                auto t = dp[rem];
                t.push_back(i); 
                if(s[t[0]] == '0' && t.size() > 1) continue;
                int new_rem = (rem * 10 + r) % 8;
                if(ndp[new_rem].empty() || t.size() < ndp[new_rem].size()){
                    ndp[new_rem] = t;
                }
            }
        }
        dp = ndp;
        if(!dp[0].empty()){
            cout << "YES" << "\n";
            for(int idx : dp[0]) {
                cout << s[idx];
            }
            cout << "\n";
            return;
        }
    }
    cout << "NO" << "\n";
}
int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
