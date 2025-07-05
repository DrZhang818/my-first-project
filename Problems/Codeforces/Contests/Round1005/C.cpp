#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n;
    cin >> n; 
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    map<PII,ll> mp;
    auto dfs = [&](this auto &&dfs, int l, int r) -> ll {
        if(l == r) {
            return abs(a[l]);
        }
        if(mp.find({l, r}) != mp.end()) return mp[{l, r}];
        ll &res = mp[{l, r}];
        res = 0;
        while(a[l] >= 0 && l < r) {
            res += a[l];
            l++;
        }
        while(a[r] < 0 && r >= l) {
            res += -a[r];
            r--;
        }
        if(r < l) return res;
        int i = l, j = r;
        ll lm = 0, rm = 0;
        for(; i <= r; i++) {
            if(a[i] >= 0) break;
            lm = max(lm, -a[i]);
        }
        for(; j >= l; j--) {
            if(a[j] < 0) break;
            rm = max(rm, a[j]);
        }
        return res = res + max({lm, rm, dfs(i, j)});
    };
    ll ans = dfs(0, n - 1);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

