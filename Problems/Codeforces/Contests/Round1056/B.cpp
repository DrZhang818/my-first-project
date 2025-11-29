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
    if(k == n * n - 1) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    vector a(n + 1, vector<char>(n + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(k) {
                a[i][j] = 'U';
                k--;    
            } else {
                if(i < n) {
                    a[i][j] = 'D';
                } else {
                    a[i][j] = j == n ? 'L' : 'R';
                }
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cout << a[i][j];
        }
        cout << "\n";
    }
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
