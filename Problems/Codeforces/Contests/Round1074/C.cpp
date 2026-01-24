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
    sort(a.begin() + 1, a.end());
    int ans = 1;
    for(int i = 2, len = 1; i <= n; i++) {
        if(a[i] == a[i - 1]) continue;
        if(a[i] == a[i - 1] + 1) {
            len++;
        } else {
            len = 1;
        }
        ans = max(ans, len);
    }
    cout << ans << "\n";
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
