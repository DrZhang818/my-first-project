#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> odd;
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x & 1) {
            odd.push_back(x);
        } else {
            ans += x;
        }
    }
    if(odd.empty()) {
        cout << 0 << "\n";
        return;
    }
    sort(odd.begin(), odd.end(), greater<int>());
    int m = odd.size();
    for(int i = 0; i < (m + 1) / 2; i++) {
        ans += odd[i];
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
