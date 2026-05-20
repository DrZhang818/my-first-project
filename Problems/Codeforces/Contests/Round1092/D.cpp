#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

bool ck(i64 n, i64 b, int p, i64 D) {
    i64 M = n / D;
    i128 B = 1;
    for(int i = 0; i < p; i++) {
        B *= b;
    }
    while(M > 0) {
        if(M % B >= b) return false;
        M /= B;
    }
    return true;
}

struct Info {
    i64 b, p, sum;
    friend bool operator<(const Info& a, const Info& b) {
        return a.sum < b.sum;
    }
};

vector<Info> A;

auto init = []() {
    for(i128 b = 2; b <= 1000000; b++) {
        i128 sum = 1 + b;
        i128 cur = b;
        for(int p = 3; ; p++) {
            cur *= b;
            sum += cur;
            if(sum > (i64)1E12) break;
            A.emplace_back((i64)b, p, (i64)sum);
        }
    }
    sort(A.begin(), A.end());
    return 1;
}();

void solve() {
    i64 n;
    cin >> n;

    vector<i64> divs;
    for(i64 i = 1; i * i <= n; i++) {
        if(n % i == 0) {
            divs.push_back(i);
            if(i * i != n) {
                divs.push_back(n / i);
            }
        }
    }

    int ans = 0;
    for(i64 D : divs) {
        if(D < 3) continue;

        i64 b2 = D - 1;
        if(b2 >= 2 && ck(n, b2, 2, D)) {
            ans++;
        }

        auto it = lower_bound(A.begin(), A.end(), D, [&](const Info& a, i64 val) {
            return a.sum < val;
        });

        while(it != A.end()) {
            auto [b, p, sum] = *it;
            if(sum != D) break;
            if(ck(n, b, p, D)) {
                ans++;
            }
            it++;
        }
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