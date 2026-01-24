#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    sort(p.begin() + 1, p.end(),
        [&](auto x, auto y) {
            return a[x] < a[y];
        });
    cout << p[1] << " " << p[2] << " " << p[3] << "\n";
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
