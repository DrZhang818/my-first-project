#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    vector<vector<int>> a(4, vector<int>(4));
    for(int i = 1; i <= 3; i++) {
        for(int j = 1; j <= 3; j++) {
            cin >> a[i][j];
        }
    }
    int m;
    cin >> m;
    set<int> st;
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        st.insert(x);
    }
    for(int i = 1; i <= 3; i++) {
        for(int j = 1; j <= 3; j++) {
            if(st.count(a[i][j])) {
                a[i][j] = 1;
            } else {
                a[i][j] = 0;
            }
        }
    }
    bool ok = false;
    for(int i = 1; i <= 3; i++) {
        if(a[i][1] == 1 && a[i][2] == 1 && a[i][3] == 1) {
            ok = true;
        }
    }
    for(int j = 1; j <= 3; j++) {
        if(a[1][j] == 1 && a[2][j] == 1 && a[3][j] == 1) {
            ok = true;
        }
    }
    if(a[1][1] == 1 && a[2][2] == 1 && a[3][3] == 1) {
        ok = true;
    }
    if(a[3][1] == 1 && a[2][2] == 1 && a[1][3] == 1) {
        ok = true;
    }
    cout << (ok ? "Yes" : "No") << "\n";
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
