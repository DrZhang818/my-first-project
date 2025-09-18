#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    vector<int> cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    ll ans = 0;
    if(k == 1) {
        int mex = 0;
        for(int i = 0; i <= n; i++) {
            if(cnt[i]) {
                mex++;
            } else {
                break;
            }
        }
        for(int i = 1; i <= n; i++) {
            if(cnt[a[i]] >= 2) {
                ans += mex;
            } else {
                ans += min(mex, a[i]);
            }
        }
        cout << ans << "\n";
        return;
    }
    for(int i = 0; i <= n; i++) {
        if(cnt[i] == 0 || cnt[i] >= 2) {
            if(cnt[i] == 0) {
                int tag = (k % 2 == 1);
                if(i == n - 1) {
                    ans += i;
                } else {
                    if(tag) {
                        ans += 1LL * i * (n - i);
                    } else {
                        ans += 1LL * (i + 1) * (n - i);
                    }
                }
            } else {
                int tag = (k % 2 == 1);
                if(tag == 0) {
                    ans += 1LL * i * (n - i);
                } else {
                    ans += 1LL * (i + 1) * (n - i);
                }
            }
            cout << ans << "\n";
            return;
        } else {
            ans += i;
        }
    }
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
