#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int M = 5000000;

void solve() {  
    int n, k;
    cin >> n >> k;
    const int U = (1 << n) - 1;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> msk(M);
    for(int j = 0; j < n; j++) {
        for(int i = 0; i < M; i++) {
            if(i / a[j] % 2 == 0) {
                msk[i] |= 1 << j;
            }
        }
    }

    auto ck = [&](int x) {
        vector<int> cnt(1 << n);
        for(int i = 0; i < x; i++) {
            cnt[msk[i]]++;
        }

        for(int i = 0; i < n; i++) {
            for(int s = 0; s < 1 << n; s++) {
                s |= 1 << i;
                cnt[s] += cnt[s ^ (1 << i)];
            }
        }
        for(int s = 0; s < 1 << n; s++) {
            int pc = __builtin_popcount(s);
            int demand = pc * k;
            int supply = x - cnt[s ^ U];
            if(supply < demand) {
                return false;
            }
        }
        return true;
    };     

    int lo = 0, hi = M;
    while(lo + 1 < hi) {
        int mid = lo + hi >> 1;
        if(ck(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    cout << hi << "\n";
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
