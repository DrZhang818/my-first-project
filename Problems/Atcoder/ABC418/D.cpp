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
    string s;
    cin >> s;
    ll c0 = 1, c1 = 0;
    ll ans = 0;
    s = "#" + s;
    vector<int> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        s[i] ^= 1;
        pre[i] = pre[i - 1] ^ (s[i] - '0');
    }
    for(int i = 1; i <= n; i++) {
        if(pre[i] == 0) {
            ans += c0;
            c0++;
        } else {
            ans += c1;
            c1++;
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
