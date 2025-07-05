#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 1; i <= 4 * k; i++) {
        int x;
        cin >> x;
    }
    cout << n * m + m + n - 2 << "\n";
    for(int i = 1; i < m; i++) {
        cout << "L";
    }
    for(int i = 1; i < n; i++) {
        cout << "U";
    }   
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(j == m) {
                cout << "D";
            } else if(i & 1) {
                cout << "R";
            } else {
                cout << "L";
            }
        }
    }
    cout << "\n";
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
