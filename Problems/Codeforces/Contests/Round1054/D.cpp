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
    vector<int> posa, posb;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'a') {
            posa.push_back(i);
        } else {
            posb.push_back(i);
        }
    }
    auto cal = [&](vector<int> &a) -> ll {
        if(a.empty()) {
            return 0;
        }
        int m = a.size();
        int t = a[m / 2];
        ll ans = 0;
        for(int i = m / 2, c = 0; i >= 0; i--, c++) {
            ans += t - c - a[i];
        }
        for(int i = m / 2 + 1, c = 1; i < m; i++, c++) {
            ans += a[i] - t - c;
        }
        return ans;
    };
    cout << min(cal(posa), cal(posb)) << "\n";
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
