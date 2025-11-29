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
    vector<int> b(n + 1);
    ll sum = 0;
    int m = n;
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        sum += b[i];
        if(b[i] == 0) {
            m--;
        }
    }
    for(int i = m; i >= 1; i--) {
        if(sum - i >= n - 1) {
            cout << i << "\n";
            return;
        }
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
