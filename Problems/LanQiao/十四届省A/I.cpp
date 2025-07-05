#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m));
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < m; j++) {
            if(s[j] == '_') a[i][j] = 0;
            else a[i][j] = s[j] - '0';
        }
    }
    vector<vector<int>> dp(n + 1, vector<int>((1 << m) + 1));
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int s = 0; s < 1 << m; s++) {
            for(int ps = 0; ps < 1 << m; ps++) {
                for(int pps = 0; pps < 1 << m; pps++) {
                    
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
