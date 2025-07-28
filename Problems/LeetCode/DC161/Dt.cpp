#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int get(ll x) {
    int res = 0;
    while(x != 1) {
        res++;
        x = __builtin_popcountll(x);
    }
    return res;
}
void solve() {
    vector<vector<int>> cnt(6);
    for(int i = 1; i <= 1000000; i++) {
        int x = get(i);
        if(x <= 5) {
            cnt[x].push_back(i);
        }
    }
    for(int x : cnt[3]) {
        cout << x << " " << __builtin_popcountll(x) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
