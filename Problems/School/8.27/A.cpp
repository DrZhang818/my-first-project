#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    vector<int> a(4);
    for(int i = 1; i <= 3; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    int ans = 0;
    if(a[1] % 2 == a[3] % 2 && a[2] % 2 == a[3] % 2) {
        ans += (a[3] - a[1]) / 2;
        ans += (a[3] - a[2]) / 2;
    } else if(a[1] % 2 != a[3] % 2 && a[2] % 2 != a[3] % 2) {
        ans += 1;
        a[1]++;
        a[2]++;
        ans += (a[3] - a[1]) / 2;
        ans += (a[3] - a[2]) / 2;
    } else if(a[1] % 2 == a[3] % 2) {
        ans += 1;
        a[1]++;
        a[3]++;
        ans += (a[3] - a[1]) / 2;
        ans += (a[3] - a[2]) / 2;
    } else {
        ans += 1;
        a[2]++;
        a[3]++;
        ans += (a[3] - a[1]) / 2;
        ans += (a[3] - a[2]) / 2;
    }
    cout << ans << "\n";
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
