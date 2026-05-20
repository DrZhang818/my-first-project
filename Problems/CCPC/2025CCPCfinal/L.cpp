#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

u64 splitmix64(u64 x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}

struct XorBasis {
    vector<i64> b;
    vector<int> rightMost;
    XorBasis() : b(32, 0), rightMost(32, -1) {}
    
    void insertRightMost(int idx, i64 v) {
        for(int i = 31; i >= 0; i--) {
            if(!(v >> i)) {
                continue;
            }
            if(b[i] == 0) {
                b[i] = v;
                rightMost[i] = idx;
                return ;
            }
            if(idx > rightMost[i]) {
                swap(idx, rightMost[i]);
                swap(v, b[i]);
            }
            v ^= b[i];
        }
    }
};

void solve() {
    int n;
    cin >> n;
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    XorBasis b;
    vector<u64> space;

    for(int r = 1; r <= n; r++) {
        b.insertRightMost(r, a[r]);

        vector<pair<int, i64>> active;
        for(int i = 0; i < 32; i++) {
            if(b.b[i] > 0) active.emplace_back(b.rightMost[i], b.b[i]);
        }
        sort(active.begin(), active.end(), greater());

        vector<i64> rref(32);

        if(active.empty() || active[0].first < r) {
            space.push_back(0);
        }

        for(auto& [pos, v] : active) {
            i64 cur = v;

            for(int i = 31; i >= 0; i--) {
                if(rref[i] && (cur >> i & 1)) cur ^= rref[i];
            }

            int p = 63 - __builtin_clzll(cur);
            rref[p] = cur;

            for(int i = 31; i >= 0; i--) {
                if(i != p && rref[i] && (rref[i] >> p & 1)) {
                    rref[i] ^= cur;
                }
            }

            u64 h = 0;
            for(int i = 0; i < 32; i++) {
                if(rref[i]) {
                    h ^= splitmix64(rref[i] ^ splitmix64(i));
                }
            }

            space.push_back(h);
        }
    }

    sort(space.begin(), space.end());
    space.erase(unique(space.begin(), space.end()), space.end());

    cout << space.size() << "\n";
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