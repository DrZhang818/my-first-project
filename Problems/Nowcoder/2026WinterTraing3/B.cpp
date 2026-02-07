#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get(int L, int R) {
    return rng() % (R - L + 1) + L;
}

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    if(n == 1) {
        cout << -1 << "\n";
        return;
    }

    for(int t = 1; t <= 1000; t++) {
        int i = get(1, n);
        int j = i;
        while(j == i) j = get(1, n);
        if(gcd(a[i], a[j]) > 1) {
            cout << a[i] << " " << a[j] << "\n";
            return;
        }
    }
    cout << -1 << "\n";
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
