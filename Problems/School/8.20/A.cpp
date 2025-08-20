#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, q, x;
    cin >> n >> q >> x;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<ll> pre(n + 1);
    ll tot = 0;
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
        tot += a[i];
    }

    auto get = [&](ll l, ll r) -> ll {
        int R_l = n;
        if(r <= R_l) return pre[r] - pre[l - 1];
        ll sum = pre[n] - pre[l - 1];
        sum += pre[(r % n == 0 ? n : r % n)];
        ll nl = 1, nr = (r + n - 1) / n;
        sum += (nr - nl - 1) * tot;
        return sum;
    };

    int cur = 1; 
    vector<int> pos;
    pos.push_back(1);
    vector<ll> cnt(n + 1);
    vector<int> vis(n + 1);
    vis[1] = true;
    
    int st;
    while(1) {
        ll l = cur - 1, r = inf + cur + 1;
        while(l + 1 < r) {
            ll mid = l + r >> 1;
            if(get(cur, mid) >= x) {
                r = mid;
            } else {
                l = mid;
            }
        }
        cnt[cur] = r - cur + 1;
        r++;
        cur = (r % n == 0 ? n : r % n);
        if(vis[cur]) {
            st = cur;
            break;
        }
        pos.push_back(cur);
        vis[cur] = true;
    }
    int sz = pos.size();
    for(int i = 0; i < sz; i++) {
        if(pos[i] == st) {
            st = i;
            break;        
        }
    }
    while(q--) {
        ll k;
        cin >> k;
        k--;
        if(k < st) {
            cout << cnt[pos[k]] << "\n";
        } else {
            k -= st;
            k %= (sz - st);
            k = st + k;
            cout << cnt[pos[k]] << "\n";
        }
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
