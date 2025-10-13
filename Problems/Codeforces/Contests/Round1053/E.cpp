#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

void solve() {
    int n;
    cin >> n;
    vector<int> v(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    vector<int> a(n + 1), id(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        id[x] = i;
    }
    ll ans = 0;
    map<int,ll> mp;
    for(int i = 1; i <= n; i++) {
        int val = v[a[i]];
        int pos = id[a[i]];
        ans += val;
        val = -val;
        auto it = mp.lower_bound(pos);
        while(val < 0 && it != mp.end()) {
            if(it->second + val > 0) {
                it->second += val;
                val = 0;
                break;
            }
            val += it->second;
            it = mp.erase(it);
        }
        if(val > 0) {
            mp[pos] += val;
        }
    }
    for(auto [pos, v] : mp) {
        ans += v;
    }
    cout << ans << "\n";
}   

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
