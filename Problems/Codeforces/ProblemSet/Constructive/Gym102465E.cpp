#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

constexpr int N = 10000;

void solve() {
    int n;
    cin >> n;
    vector<string> s(n + 1);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> s[i] >> a[i];
    }

    vector<int> L(n + 1), R(n + 1);
    int mn = 0, mx = 0;

    for(int i = 1; i <= n; i++) {
        L[i] = max(0, a[i] * 100 - 50);
        R[i] = min(N, a[i] * 100 + 49);
        mn += L[i];
        mx += R[i];
    }

    if(mn > N || mx < N) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    auto out = [&](int x, int y) {
        cout << x << ".";
        if(y < 10) cout << 0;
        cout << y;
    };

    for(int i = 1; i <= n; i++) {
        mn -= L[i];
        mx -= R[i];

        int lo = max(L[i], N - mx);
        int hi = min(R[i], N - mn);

        cout << s[i] << " ";
        out(lo / 100, lo % 100);
        cout << " ";
        out(hi / 100, hi % 100);
        cout << "\n";

        mn += L[i];
        mx += R[i];
    }

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
