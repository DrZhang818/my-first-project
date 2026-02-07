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
    iota(a.begin(), a.end(), 0);
    swap(a[1], a[2]);
    vector<int> p(n + 1);
    for(int i = 1; i <= n; i++) {
        p[a[i]] = i;
    }
    if(~n & 1) {
        int mask = (1 << __lg(n) + 1) - 1;
        swap(a[n], a[p[~(n - 1) & mask]]);
    }
    if(n & 1) {
        cout << n << "\n";
    } else {
        cout << (1 << __lg(n) + 1) - 1 << "\n";
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
