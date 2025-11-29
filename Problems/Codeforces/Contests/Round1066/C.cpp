#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(n + 1, inf);
    vector<array<int,3>> Line;
    for(int i = 0; i < q; i++) {
        int c, l, r;
        cin >> c >> l >> r;
        c = 2 - c;
        Line.push_back({c, l, r});
    }
    sort(Line.begin(), Line.end());
    int las = 0, L = 1;
    for(auto [c, l, r] : Line) {
        L = max(L, l);
        if(c == 1) {
            for(int i = l; i <= r; i++) {
                if(a[i] == inf) {
                    a[i] = k;
                } else if(a[i] != k) {
                    a[i] = k + 1;
                }
            }
        } else {
            while(L <= r) {
                a[L] = las;
                las++;
                if(las >= k) {
                    las = 0;
                }
                L++;
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
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
