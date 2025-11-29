#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const ll V = ll(2E18) + 5;


void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1), b(n + 1), c(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    sort(c.begin() + 1, c.end());

    auto ck = [&](ll x) -> bool {
        vector<int> pos(n + 1), neg(n + 1);
        for(int i = 1; i <= n; i++) {
            if(a[i] > 0) {
                int l = 0, r = n + 1;
                while(l + 1 < r) {
                    int mid = l + r >> 1;
                    if(a[i] * c[mid] + b[i] >= x) {
                        r = mid;
                    } else {
                        l = mid;
                    }
                }
                if(r <= n) {
                    pos[r]++;
                }
            } else if(a[i] == 0) {
                if(b[i] >= x) {
                    pos[1]++;
                }
            } else {
                int l = 0, r = n + 1;
                while(l + 1 < r) {
                    int mid = l + r >> 1;
                    if(a[i] * c[mid] + b[i] >= x) {
                        l = mid;
                    } else {
                        r = mid;
                    }
                }
                if(l > 0) {
                    neg[l]++;
                }
            }
        }

        int ans = 0;
        int cnt_pos = 0, cnt_neg = 0, used_neg = 0;
        for(int i = 1; i <= n; i++) {
            cnt_neg += neg[i];
        }
        for(int i = 1; i <= n; i++) {
            cnt_pos += pos[i];
            if(cnt_neg + cnt_pos > 0) {
                ans++;
                if(cnt_neg > 0) {
                    cnt_neg--;
                    used_neg++;
                } else {
                    cnt_pos--;
                }
            }
            if(neg[i]) {
                int t = min(neg[i], used_neg);
                neg[i] -= t;
                used_neg -= t;
                if(neg[i] > 0) {
                    cnt_neg -= neg[i];
                }
            }
        }
        return ans >= (n + 1) / 2;
    };

    ll l = -V, r = V;
    while(l + 1 < r) {
        ll mid = l + (r - l) / 2;
        if(ck(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << "\n";
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
