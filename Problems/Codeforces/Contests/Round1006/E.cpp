#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int k;
    cin >> k;
    int n = 1;
    while(n * (n - 1) < 2 * k) n++;
    vector<int> dp(n + 1);
    dp[0] = dp[1] = 0;
    dp[2] = 1;
    for(int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + i - 1;
    }
    int cx = 0;
    vector<int> ans;
    while(k) {
        auto it = upper_bound(dp.begin(), dp.end(), k);
        it--;
        ans.push_back(it - dp.begin());
        k -= *it;
    }
    int sum = 0;
    for(int i = 0; i < ans.size(); i++) sum += ans[i];
    cout << sum << "\n";
    for(int i = 0; i < ans.size(); i++) {
        for(int j = 0; j < ans[i]; j++) {
            cout << cx << " " << i << "\n";
            cx++;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); 

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
