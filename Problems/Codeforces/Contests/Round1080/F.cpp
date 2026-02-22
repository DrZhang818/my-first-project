#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct Info {
    ll a, b, c;
};

void solve() {  
    int n;
    cin >> n;
    
    vector<Info> A(n + 1);

    for(int i = 1; i <= n; i++) {
        cin >> A[i].a >> A[i].b >> A[i].c;
    }

    auto ck = [&](ll a, ll b, ll c) {
        if(a > 0) {
            return b * b - 4 * a * c < 0;
        } else if(a == 0) {
            return b == 0 && c > 0;
        }
        return false;
    };

    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    sort(p.begin() + 1, p.end(),
        [&](auto x, auto y) {
            if(A[x].a != A[y].a) {
                return A[x].a < A[y].a;
            }
            return A[x].c < A[y].c;
        }); 

    vector<int> up(n + 1, 1), down(n + 1, 1);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            auto [a1, b1, c1] = A[p[i]];
            auto [a2, b2, c2] = A[p[j]];
            if(ck(a1 - a2, b1 - b2, c1 - c2)) {
                up[i] = max(up[i], up[j] + 1);
            }
        }
    }

    for(int i = n; i >= 1; i--) {
        for(int j = i + 1; j <= n; j++) {
            auto [a1, b1, c1] = A[p[j]];
            auto [a2, b2, c2] = A[p[i]];
            if(ck(a1 - a2, b1 - b2, c1 - c2)) {
                down[i] = max(down[i], down[j] + 1);
            }
        }
    }

    vector<int> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        ans[p[i]] = up[i] + down[i] - 1;
    }

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }

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
