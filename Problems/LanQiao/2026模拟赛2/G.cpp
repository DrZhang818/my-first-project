#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> pre(n + 1), suf(n + 2);

    {
        vector<int> val {0};
        for(int i = 1; i <= n; i++) {
            auto it = upper_bound(val.begin(), val.end(), a[i]);
            pre[i] = it - val.begin();
            if(it == val.end()) {
                val.push_back(a[i]);
            } else {
                *it = a[i];
            }
        }
    }

    int ans = 0;
    {
        vector<int> val {inf};

        auto find = [&](int x) {
            int l = -1, r = val.size();
            while(l + 1 < r) {
                int mid = l + r >> 1;
                if(val[mid] < x) {
                    r = mid; 
                } else {
                    l = mid;
                }
            }
            return r;
        };

        for(int i = n; i >= 1; i--) {
            int r = find(a[i]);
            if(r == val.size()) {
                val.push_back(a[i]);
            } else {
                val[r] = a[i];
            }
            suf[i] = r;

            int m = val.size();
            if(i - k >= 2) {
                int f = find(a[i - k - 1]) - 1;
                ans = max(ans, pre[i - k - 1] + f + k);
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        ans = max(ans, pre[i] + min(k, n - i));
        ans = max(ans, suf[i] + min(k, i - 1));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}