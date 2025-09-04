#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    vector<vector<int>> a(3, vector<int>(7));
    for(int i = 1; i <= 2; i++) {
        for(int j = 1; j <= 6; j++) {
            cin >> a[i][j];
        }
    }
    bool ok = true;
    if(a[2][1] >= a[1][4] || a[2][2] >= a[1][5] || a[2][3] >= a[1][6]) {
        ok = false;
    }
    if(a[2][4] <= a[1][1] || a[2][5] <= a[1][2] || a[2][6] <= a[1][3]) {
        ok = false;
    }
    if(ok) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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
