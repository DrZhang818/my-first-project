#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mp[x]++;
    }
    int ans = 0, pre = mp.begin()->first - 1, pm = 0;
    for(auto [x, c] : mp) {
        if(x == pre + 1) {
            if(c < pm) {
                ans += pm - c;
            }
            pm = c;
            pre = x;
        } else {
            ans += pm;
            pre = x;
            pm = c;
        }
    }
    ans += pm;
    cout << ans << "\n";
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
    
