#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a[0] = -10000000;
    int dp = 0, ans = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] <= a[i - 1]) {
            dp++;
            ans = max(ans, dp);
        } else {
            dp = 0;
        }
    }   
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
