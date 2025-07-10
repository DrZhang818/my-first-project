#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/1305/problem/C
int MOD;
void solve() {
    int n;
    cin >> n >> MOD;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    if(n > MOD) {
        cout << 0 << "\n";
        return;
    }
    int ans = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            ans = 1LL * ans * abs(a[i] - a[j]) % MOD;
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
