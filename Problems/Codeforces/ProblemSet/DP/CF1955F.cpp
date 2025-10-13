#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    vector<int> a(5);
    for(int i = 1; i <= 4; i++) {
        cin >> a[i];
    }
    int ans = a[1] / 2 + a[2] / 2 + a[3] / 2 + a[4] / 2;
    if(a[1] % 2 == 1 && a[2] % 2 == 1 && a[3] % 2 == 1) {
        ans++;
    }
    cout << ans << "\n";
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
