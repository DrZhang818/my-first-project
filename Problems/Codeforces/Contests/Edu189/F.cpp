#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;
constexpr int P1 = 1E9 + 7;
constexpr int P2 = 1E9 + 9;
constexpr int B1 = 13331;
constexpr int B2 = 13131;
constexpr int N = 1E6 + 5;

int p1_pow[N], p2_pow[N];

auto init = []() {
    p1_pow[0] = p2_pow[0] = 1;
    for(int i = 1; i < N; i++) {
        p1_pow[i] = 1LL * p1_pow[i - 1] * B1 % P1;
        p2_pow[i] = 1LL * p2_pow[i - 1] * B2 % P2;
    }
    return 1;
}();

void solve() {
    int n, l, k;
    cin >> n >> l >> k;

    string s;
    cin >> s;

    if(1LL * k * l > n) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";

    if(k == 1) {
        cout << s << "\n";
        return;
    }

    vector<int> h1(n + 1), h2(n + 1);
    for(int i = 0; i < n; i++) {
        h1[i + 1] = (1LL * h1[i] * B1 + s[i]) % P1;
        h2[i + 1] = (1LL * h2[i] * B2 + s[i]) % P2;
    }

    auto get_hash = [&](int l, int r) -> pair<int,int> {
        int len = r - l + 1;
        int res1 = (h1[r + 1] - 1LL * h1[l] * p1_pow[len]) % P1;
        if(res1 < 0) res1 += P1;
        int res2 = (h2[r + 1] - 1LL * h2[l] * p2_pow[len]) % P2;
        if(res2 < 0) res2 += P2;
        return {res1, res2};
    };

    auto compare = [&](const pair<int,int>& a, pair<int,int> b) {
        auto [l1, r1] = a;
        auto [l2, r2] = b;
        int len = min(r1 - l1 + 1, r2 - l2 + 1);
        int l = -1, r = len + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(get_hash(l1, l1 + mid - 1) == get_hash(l2, l2 + mid - 1)) {
                l = mid;
            } else {
                r = mid;
            }
        }
        if(l == len) {
            return r1 - l1 + 1 == len ? b : a;
        }
        return s[l1 + l] < s[l2 + l] ? b : a;
    };

    pair<int, int> ans {0, n - 1 - (k - 1) * l};

    for(int L = l; L <= n - l; L++) {
        int p = min(L / l, k - 1);
        int R = n - 1 - (k - 1 - p) * l;

        if(R - L + 1 < l) continue;

        ans = compare(ans, {L, R});
    }

    cout << s.substr(ans.first, ans.second - ans.first + 1) << "\n";
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