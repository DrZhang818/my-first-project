#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;
constexpr int MOD = 998244353;

int power(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

struct Info {
    int x, y;
    friend bool operator<(const Info& a, const Info& b) {
        return 1LL * a.x * b.y < 1LL * a.y * b.x;
    }
    friend bool operator<=(const Info& a, const Info& b) {
        return 1LL * a.x * b.y <= 1LL * a.y * b.x;
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    int fac_n = 1, fac_n2 = 1;
    for(int i = 1; i <= n; i++) {
        fac_n = 1LL * fac_n * i % MOD;
        if(i <= n - 2) {
            fac_n2 = 1LL * fac_n2 * i % MOD;
        }
    }   

    auto get = [&](const vector<int>& vec, bool tag) {
        vector<Info> val;
        val.reserve(1LL * n * (n - 1) / 2);

        for(int i = 1; i <= n; i++) {
            for(int j = i + 1; j <= n; j++) {
                int x = vec[i], y = vec[j];
                int g = gcd(x, y);
                x /= g;
                y /= g;
                val.emplace_back(x, y);
                if(tag) val.emplace_back(y, x);
            }
        }
        sort(val.begin(), val.end());

        return val;
    };

    auto val_a = get(a, 0);
    auto val_b = get(b, 1);

    int m = val_a.size();
    int ans = 0;

    for(int i = 0, j = 0; i < val_b.size(); i++) {
        while(j < m && val_a[j] <= val_b[i]) j++;
        int cur = 1LL * (m - j) * fac_n2 % MOD;
        ans = (ans + cur) % MOD;
    }

    ans = 1LL * ans * power(fac_n, MOD - 2) % MOD;

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