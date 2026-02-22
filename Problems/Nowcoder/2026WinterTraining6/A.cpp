#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct Info {
    db w;
    int id;
    friend bool operator<(const Info& a, const Info& b) {
        return a.w < b.w;
    }
};

void solve() {  
    ll n, w;
    cin >> n >> w;
    vector<pair<ll,ll>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    priority_queue<Info> q;

    for(int i = 1; i <= n; i++) {
        auto [x, y] = a[i];
        db c = sqrt(x * x + y * y);
        db nc = sqrt(x * x + (y - 1) * (y - 1));
        q.push({c - nc, i});
    }

    while(w > 0 && !q.empty()) {
        auto [c, i] = q.top(); q.pop();
        a[i].second--;
        w--;
        if(a[i].second >= 1) {
            db c = sqrt(a[i].first * a[i].first + a[i].second * a[i].second);
            db nc = sqrt(a[i].first * a[i].first + (a[i].second - 1) * (a[i].second - 1));
            q.push({c - nc, i});
        }
    }

    db ans = 0;
    for(int i = 1; i <= n; i++) {
        auto [x, y] = a[i];
        ans += sqrt(x * x + y * y);
    }
    cout << fixed << setprecision(12) << ans << "\n";
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
