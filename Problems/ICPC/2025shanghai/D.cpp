#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(1 << n);
    for(int i = 0; i < 1 << n; i++) {
        cin >> a[i];
    }
    for(int s = 0; s < n; s++) {
        int len = 1 << (n - 1 - s);
        if(s == n - 1) {
            int ans = 0;
            for(int i = 0; i < a.size(); i += 2) {
                int L = a[i], R = a[i + 1];
                ans ^= L;
                ans ^= R;
                ans ^= (L + R);
            }
            cout << ans << "\n";
            return;
        }
        vector<int> na;
        na.reserve((a.size() >> 1) * 3);
        for(int i = 0; i < a.size(); i += (len << 1)) {
            int l = i, r = i + len;
            for(int k = 0; k < len; k++) {
                na.push_back(a[l + k]);
            }
            for(int k = 0; k < len; k++) {
                na.push_back(a[r + k]);
            }
            for(int k = 0; k < len; k++) {
                na.push_back(a[l + k] + a[r + k]);
            }
        }
        a = move(na);
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
