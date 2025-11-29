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
    if(a[1] == -1 && a[n] == -1) {
        a[1] = a[n] = 0;
    } else if(a[1] == -1) {
        a[1] = a[n];
    } else if(a[n] == -1) {
        a[n] = a[1];
    }
    for(int i = 2; i <= n - 1; i++) {
        a[i] = a[i] == -1 ? 0 : a[i];
    }
    cout << abs(a[1] - a[n]) << "\n";
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
