#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 1 << 20;

int las[N + 1];

void solve() {
    int n, m, x;
    cin >> n >> m >> x;
    vector<int> a(n + 1);
    vector<int> L(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(las[a[i] ^ x] != 0) {
            L[i] = las[a[i] ^ x];
        }
        las[a[i]] = i;
    }
    for(int i = 1; i <= n; i++) {
        L[i] = max(L[i - 1], L[i]);
    }
    while(m--) {
        int l, r;
        cin >> l >> r;
        if(L[r] >= l) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}