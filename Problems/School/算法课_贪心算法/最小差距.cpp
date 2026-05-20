#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int M = 1 << 10;

array<vector<int>, M> val;
array<int, M> ans;

void solve() {
    int n;
    cin >> n;

    int msk = 0;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        msk |= 1 << x;
    }

    cout << ans[msk] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for(int s = 1; s < M; s++) {
        int c = __builtin_popcount(s);
        if(c > 5) continue;

        vector<int> d;
        for(int i = 0; i < 10; i++) {
            if(s >> i & 1) {
                d.push_back(i);
            }
        }

        do {
            if(c > 1 && d[0] == 0) continue;
            int x = 0;
            for(auto v : d) {
                x = x * 10 + v;
            }
            val[s].push_back(x);
        } while(next_permutation(d.begin(), d.end()));
        
        sort(val[s].begin(), val[s].end());
    }

    ans.fill(inf);
    for(int msk = 1; msk < M; msk++) {
        int n = __builtin_popcount(msk);
        if(n < 2) {
            continue;
        }
        int k = n / 2;
        for(int s = msk; s; s = (s - 1) & msk) {
            if(__builtin_popcount(s) != k) {
                continue;
            }
            int t = msk ^ s;
            auto& a = val[s];
            auto& b = val[t];

            int i = 0, j = 0;
            while(i < int(a.size()) && j < int(b.size())) {
                ans[msk] = min(ans[msk], abs(a[i] - b[j]));
                if(a[i] < b[j]) {
                    i++;
                } else {
                    j++;
                }
            }
        }
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}