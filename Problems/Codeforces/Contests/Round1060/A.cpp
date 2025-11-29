#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    s = "#" + s;
    vector<int> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + (s[i] == '1');
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '1') {
            int L = i - k + 1;
            L = max(1, L);
            if(pre[i - 1] - pre[L - 1] == 0) {
                ans++;
            }
        }
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
