#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

//https://codeforces.com/problemset/problem/1475/E
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
vector<vector<int>> C;
void init(int n) {
    C.resize(n + 1, vector<int>(n + 1));
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= i; j++) {
            if(j == 0) C[i][j] = 1;
            else add(C[i][j], (C[i - 1][j] + C[i - 1][j - 1]) % MOD);
        }
    }
}
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    int ans = 1;
    for(int i = n; i >= 1 && k; i--) {
        int c = cnt[i];
        if(c <= k) {
            k -= c;
        } else {
            ans = C[c][k];
            k = 0;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init(1001);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
