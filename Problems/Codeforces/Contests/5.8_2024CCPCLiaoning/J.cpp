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
    int a, b, c;
    cin >> a >> b >> c;
    int ans = 0;
    vector<PII> vec(n + 1);
    for(int i = 1; i <= n; i++) cin >> vec[i].first >> vec[i].second;
    int d;
    cin >> d;
    for(int i = 1; i <= n; i++) {
        auto [u, v] = vec[i];
        if(u + v < c && min(a, u + d) + v >= c) {
            ans++;
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
