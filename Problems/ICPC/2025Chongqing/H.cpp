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
    vector<int> a(n + 1), b(n + 1), c(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    for(int i = 1, j = 1; i <= n; i++) {
        if(c[i] == 0) {
            continue;
        }
        while(j <= n && b[j] != a[i]) {
            j++;
        }
        if(j > n) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
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
