#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

void solve(){
    int n;
    cin >> n; 
    string s;
    cin >> s;
    
    if(s.back() != '!'){
        cout << "NO\n";
        return;
    }
    vector<int> dp(n + 1, 0);
    ll ans = 0;
    for(int i = 1; i <= n; i++){
        dp[i] = dp[i - 1] + (s[i - 1] == '/');
        if(s[i] == '+'){
            ans += dp[i] * (dp[i] - 1) / 2;
        }
    }
    cout << (ans >= 66 ? "YES\n" : "NO\n") << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
  
    solve();
    
    return 0;
}