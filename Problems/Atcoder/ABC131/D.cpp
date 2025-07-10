#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k;
    cin >> n >> k;
    int mn = n - 2;
    int mx = n * (n - 1) / 2 - (n - 1);
    if(k > mx || k < mn) {
        cout << -1 << "\n";
        return;
    }
    int rem = mx - k;
    cout << n - 1 + rem << "\n";
    for(int i = 2; i <= n; i++) {
        cout << 1 << " " << i << "\n";
    }
    for(int i = 2; i <= n && rem; i++) {
        for(int j = i + 1; j <= n && rem; j++) {
            cout << i << " " << j << "\n";
            rem--;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
