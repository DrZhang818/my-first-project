#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 30000000005;

void solve() {
    int x, y, z, ord;
    cin >> x >> y >> z >> ord;
    vector<ll> a(x + 1), b(y + 1), c(z + 1);
    for(int i = 1; i <= x; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= y; i++) {
        cin >> b[i];
    }
    for(int i = 1; i <= z; i++) {
        cin >> c[i];
    }
    sort(a.begin() + 1, a.end());
    vector<ll> val;
    for(int i = 1; i <= y; i++) {
        for(int j = 1; j <= z; j++) {
            val.push_back(b[i] + c[j]);
        }
    }    
    sort(val.begin(), val.end());
    auto ck = [&](ll x, int k) -> bool {
        ll cnt = 0;
        for(int i = a.size() - 1; i >= 1; i--) {
            auto it = lower_bound(val.begin(), val.end(), x - a[i]) - val.begin();
            cnt += val.size() - it;
        }
        return cnt >= k;
    };
    ll l = 0, r = inf;    
    while(l + 1 < r) {
        ll mid = l + r >> 1;
        if(ck(mid, ord)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    ll mn = l;
    vector<ll> ans;
    for(int i = 1; i < a.size(); i++) {
        auto it = lower_bound(val.begin(), val.end(), mn - a[i]) - val.begin();
        for(int j = it; j < val.size(); j++) {
            ans.push_back(a[i] + val[j]);
        }
    }
    sort(ans.begin(), ans.end(), greater<ll>());
    for(int i = 0; i < ord; i++) {
        cout << ans[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}