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
        a[i] = min(a[i], 24 - a[i]);
    }    

    sort(a.begin() + 1, a.end());

    for(int i = 2; i <= n; i += 2) {
        a[i] = 24 - a[i];
    }

    int ans = inf;
    for(int i = 1; i <= n; i++) {
        ans = min(ans, min(a[i], 24 - a[i]));
        for(int j = 1; j < i; j++) {
            ans = min(ans, min(abs(a[i] - a[j]), 24 - abs(a[i] - a[j])));
        }
    }

    cout << ans << "\n";
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
