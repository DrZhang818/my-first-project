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
    vector<int> cnt(n + 1, 1);
    int L = 1;
    while(q--) {
        int x, y;
        cin >> x >> y;
        int tot = 0;
        while(L <= x) {
            cnt[y] += cnt[L];
            tot += cnt[L];
            L++;
        }
        cout << tot << "\n";
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
