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
    vector<int> cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    vector<int> b;
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        if(cnt[i]) {
            b.push_back(cnt[i]);
            mx = max(mx, cnt[i]);
        }
    }
    int cmx = count(b.begin(), b.end(), mx);
    int ans = (n - cmx) / (mx - 1) - 1;
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
