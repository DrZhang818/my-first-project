#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9 + 7;
constexpr int N = 1E6;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    stack<int> stk;
    for(int i = 1; i <= n; i++) {
        while(!stk.empty() && a[stk.top()] >= a[i]) {
            stk.pop();
        }
        stk.push(i);
    }
    vector<int> pos;
    while(!stk.empty()) {
        pos.push_back(stk.top());
        stk.pop();
    }
    reverse(pos.begin(), pos.end());
    int m = pos.size();

    int k;
    cin >> k;

    vector<int> d(n + 1);
    for(int i = 0; i < m; i++) {
        if(i == m - 1) {
            d[pos[i]] += k / a[pos[i]];
            break;
        }

        int x = a[pos[i]];
        int y = a[pos[i + 1]];
        if(k < x) break;
        int l = -1, r = k / x + 1;
        while(l + 1 < r) {
            int mid = l + (r - l) / 2;
            if((k - x * mid) / x == (k - x * mid) / y) {
                r = mid;
            } else {
                l = mid;
            }
        }
        d[pos[i]] += r;
        k -= x * r;
    }

    for(int i = n - 1; i >= 1; i--) {
        d[i] += d[i + 1];
    }

    for(int i = 1; i <= n; i++) {
        cout << d[i] << " \n"[i == n];
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