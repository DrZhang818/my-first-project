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
    map<int,int> mp;
    vector<int> val;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mp[x]++;
        if(mp[x] % 2 == 0) {
            val.push_back(x);
        }
    }
    sort(val.begin(), val.end());
    if(val.size() < 4) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    int x1 = val[0], y2 = val.back(), y1 = val[1], x2 = val[val.size() - 2];
    cout << x1 << " " << y1 << " " << x1 << " " << y2 << " " << x2 << " " << y1 << " " << x2 << " " << y2 << "\n";
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
