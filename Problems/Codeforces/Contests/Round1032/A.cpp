#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, s;
    cin >> n >> s;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    int ans = 0;
    if(s >= a[1] && s <= a[n]) {
        ans = min(s - a[1] + a[n] - a[1], a[n] - s + a[n] - a[1]);
    } else if(s < a[1]) {
        ans = a[n] - s;
    } else {
        ans = s - a[1];
    }
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
