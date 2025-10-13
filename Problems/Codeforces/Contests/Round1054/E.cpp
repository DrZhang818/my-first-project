#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k, l, r;
    cin >> n >> k >> l >> r;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    map<int,int> mpL, mpR;
    for(int L = 1, R = 1, i = 1; i <= n; i++) {
        mpL[a[i]]++;
        mpR[a[i]]++;
        while(L <= i && mpL.size() > k) {
            if(--mpL[a[L]] == 0) {
                mpL.erase(a[L]);
            }
            L++;
        }
        while(R < L) {
            if(--mpR[a[R]] == 0) {
                mpR.erase(a[R]);
            }
            R++;
        }
        while(R <= i && mpR.size() == k) {
            if(--mpR[a[R]] == 0) {
                mpR.erase(a[R]);
            }
            R++;
        }
        if(mpL.size() == k) {
            int mn = i - r + 1;
            int mx = i - l + 1;
            int tl = max(L, mn), tr = min(mx, R - 1);
            ans += max(0, tr - tl + 1);
        }
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
