#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int k, t;
    cin >> k >> t;
    vector<int> a(t + 1);
    for(int i = 1; i <= t; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end(), greater<int>());

    if(a[1] * 2 > k) {
        cout << 2 * a[1] - k - 1 << '\n';
    } else {
        cout << 0 << "\n";
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
