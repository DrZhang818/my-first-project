#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<i64> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + abs(a[i]);
    }

    int pos = -1;
    i64 sum = accumulate(a.begin() + 1, a.end(), 0LL), suf = 0;

    for(int i = n; i >= 1; i--) {
        if(a[i] > 0) {
            i64 cur = pre[i - 1] - a[i] + suf;
            if(cur > sum) {
                sum = cur;
                pos = i;
            }
        }
        suf += a[i];
    }

    vector<int> ans;

    if(pos != -1) {
        int s = 0;
        for(int i = pos - 1; i >= 1; i--) {
            if(s) a[i] = -a[i];
            if(a[i] > 0) {
                ans.push_back(i);
                s ^= 1;
            }
        }
        ans.push_back(pos);
    }

    cout << ans.size() << "\n";
    for(int x : ans) {
        cout << x << " \n"[x == ans.back()];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}