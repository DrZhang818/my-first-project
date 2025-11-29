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
    vector<int> p(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    string x;
    cin >> x;
    x = "#" + x;
    if(x[1] == '1' || x[n] == '1') {
        cout << -1 << "\n";
        return;
    }
    int mni, mxi;
    for(int i = 1; i <= n; i++) {
        if(p[i] == 1) {
            mni = i;
        }
        if(p[i] == n) {
            mxi = i;
        }
    }
    int l = min(mni, mxi), r = max(mni, mxi);
    if(x[l] == '1' || x[r] == '1') {
        cout << -1 << "\n";
        return;
    }
    cout << 5 << "\n";
    cout << l << " " << r << "\n";
    cout << 1 << " " << l << "\n";
    cout << l << " " << n << "\n";
    cout << 1 << " " << r << "\n";
    cout << r << " " << n << "\n";
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
