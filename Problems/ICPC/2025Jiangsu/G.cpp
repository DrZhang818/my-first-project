#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    map<PII,int> mp;
    auto f = [&](this auto &&f, int x, int y) -> int {
        if(mp.contains({x, y})) return mp[{x, y}];
        if(y == 1) return x;
        return mp[{x, y}] = x / a[y] + f(x % a[y], y - 1);
    };
    for(int m = 1; m <= 100; m++) {
        int cnt = 0;
        for(int x = 1; x <= 100000; x++) {
            if(f(x, n) == m) {
                cnt++;
            }
        }
        cout << m << " " << cnt << "\n";
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
