#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 2E5;

vector<int> sq;
vector<bool> isSq(N + 1);
vector<bool> sum2(N + 1);
vector<int> mn(N + 1, inf);

auto init = []() {
    for(int i = 1; i * i <= N; i++) {
        sq.push_back(i * i);
        isSq[i * i] = true;
    }

    for(auto x : sq) {
        for(auto y : sq) {
            if(x + y <= N) {
                sum2[x + y] = true;
            }
            int d = y - x;
            if(0 < d && d <= N) {
                mn[d] = min(mn[d], x);
            }
        }
    }
    return 1;
}();

void solve() {
    int n, q;
    cin >> n >> q;

    auto two = [&](int a, int b) {
        if(a > b) swap(a, b);
        int d = b - a;
        if(d == 0) return false;
        if(sum2[d]) return true;
        return mn[d] <= max(a - 1, n - b);
    };

    while(q--) { 
        int a, b;
        cin >> a >> b;
        if(isSq[b - a]) {
            cout << 1 << "\n";
            continue;
        } 
        if(two(a, b)) {
            cout << 2 << "\n";
            continue;
        } 

        bool ok = false;

        auto ck = [&](int c) {
            if(c < 1 || c > n) return false;
            return two(c, b);
        };

        for(int x : sq) {
            if(x > n - 1) break;
            ok |= ck(a - x);
            ok |= ck(a + x);
        }

        cout << (ok ? 3 : 4) << "\n";
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