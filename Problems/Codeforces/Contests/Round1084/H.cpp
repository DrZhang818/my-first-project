#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr i64 inf = 1E18;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    auto dfs = [&](this auto&& self, vector<int>& a) -> i64 {
        if(a.empty()) {
            return 0;
        }

        int r = a[0] % 6;
        for(int x : a) {
            if(x % 6 != r) {
                return inf;
            }
        }

        i64 ans = 1E18;
        r = (6 - r) % 6;
        for(int d = r; d < 42; d += 6) {
            vector<int> na;
            for(int x : a) {
                int y = x + d;
                if(y % 42 == 0) {
                    na.push_back(y / 42);
                }
            }

            if(na == a) continue;
            i64 sub = self(na);
            if(sub != inf) {
                ans = min(ans, d + 42 * self(na));
            }
        }
        
        return ans;
    };

    i64 res = dfs(a);
    if(res == inf) {
        res = -1;
    }
    cout << res << "\n";
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
