#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

ll f(ll x) {
    if(x == 0) return 0;

    ll res = 1;
    while(x) {
        res *= x % 10;
        x /= 10;
    }

    return res;
}


ll g(ll x) {
    ll t = f(x);
    if(x == t) return 0;
    return 1 + g(t);
}

void solve() {  
    array<int,10> cnt {};

    ll X = -1, Y = -1;
    ll f1 = 0, f2 = 0;
    ll g1 = 0, g2 = 0;

    ll tot = 0;
    
    auto dfs = [&](this auto&& self, int i, int rem) -> void {
        if(i == 10) {
            ll num = 0;
            for(int j = 2; j <= 9; j++) {
                for(int k = 0; k < cnt[j]; k++) {
                    num = num * 10 + j;
                }
            }
            auto curf = f(num);
            auto curg = g(num);

            if(curg > g1) {
                Y = X;
                f2 = f1;
                g2 = g1;

                X = num;
                f1 = curf;
                g1 = curg;
            } else if(curg > g2) {
                if(curf != f1) {
                    Y = num;
                    f2 = curf;
                    g2 = curg;
                }
            }
            return;
        }
        for(int j = 0; j <= rem; j++) {
            cnt[i] = j;
            self(i + 1, rem - j);
        }
    };

    dfs(2, 18);
    cout << X << " " << Y << "\n";
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
