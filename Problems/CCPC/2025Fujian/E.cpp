#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(2 * n + 1);
    i64 x = 0, y = 0;
    for(int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
        if(i & 1) {
            x += a[i];
        } else {
            y += a[i];
        }
    }

    i64 ans = min(x, y);

    auto calc = [&](i64 x, i64 y, const vector<int>& b) -> void {
        i64 tar = (y - x) >> 1;

        set<i64> st;
        st.insert(0);

        i64 sum = 0;
        for(int val : b) {
            sum += val;
            st.insert(sum);

            auto it = st.upper_bound(sum - tar);
            if(it != st.end()) {
                ans = max(ans, min(x + sum - (*it), y + (*it) - sum));
            }
            if(it != st.begin()) {
                it = prev(it);
                ans = max(ans, min(x + sum - (*it), y + (*it) - sum));
            }
        }
    };

    {
        vector<int> b;
        for(int i = 2; i <= 2 * n; i += 2) {
            b.push_back(a[i] - a[i - 1]);
        }
        calc(x, y, b);
    }

    {
        vector<int> b;
        for(int i = 3; i <= 2 * n; i += 2) {
            b.push_back(a[i] - a[i - 1]);
        }
        calc(y, x, b);
    }

    cout << ans << "\n";
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