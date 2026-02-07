#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, k, s;
    cin >> n >> k >> s;
    vector<int> a(n + 1);
    for(int i = 1; i <= k; i++) {
        a[i] = s;
    }
    int x = (s == 1 ? s + 1 : s - 1);
    for(int i = k + 1; i <= n; i++) {
        a[i] = x;
    }
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
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
