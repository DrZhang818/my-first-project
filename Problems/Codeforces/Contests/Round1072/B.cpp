#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int s, k, m;
    cin >> s >> k >> m;
    m %= 2 * k;
    if(m < k) {
        cout << max(0, s - m) << "\n";
    } else {
        cout << max(0, min(s, k) - m + k) << "\n";
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
