#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct Info {
    db L, R;
    friend bool operator<(const Info& a, const Info& b) {
        return a.L < b.L;
    }
};

constexpr db eps = 1E-7;

void solve() {  
    ll n, k, r, c;
    cin >> n >> k >> r >> c;
    vector<int> p(n + 1), v(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> p[i] >> v[i];
    }    

    auto ck = [&](db x) -> bool {
        vector<Info> line;

        for(int i = 1; i <= n; i++) {
            db R = v[i] * x;
            if(R < r - eps) continue;
            db D = sqrt(R * R - r * r);
            line.emplace_back(p[i] - D, p[i] + D);
        }
        sort(line.begin(), line.end());

        int m = line.size();
        db L = 0, R = -1;
        int cnt = 0;
        for(int i = 0, j = 0; i < m; i = j) {
            while(j < m && line[j].L < L + eps) {
                R = max(R, line[j].R);
                j++;
            }
            if(i == j) break;
            cnt++;
            if(R > c - eps) {
                break;
            }
            L = R;
        }
        return cnt <= k && (R > c - eps);
    };

    db lo = 0, hi = inf;

    for(int _ = 0; _ < 60; _++) {
        db mid = (lo + hi) / 2;
        if(ck(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    cout << fixed << setprecision(12) << hi << "\n";
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
