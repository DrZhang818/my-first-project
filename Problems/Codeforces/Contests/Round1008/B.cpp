#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, k;
    cin >> n >> k;
    vector<int> ans(n + 1);
    ans[n] = n - 1;
    ans[n - 1] = n;
    for(int i = n - 2; i >= 0; i--) {
        if(k % 2 == 1) ans[i] = n;
        else ans[i] = n - 1;
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
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
    
