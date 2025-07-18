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
    vector<bool> vis(n + 1);
    vector<int> a(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= 2 * n; i++) {
        if(!vis[a[i]]) {
            cout << a[i] << " ";
            vis[a[i]] = true;
            a[i] = -1;
        }
    }   
    cout << "\n";
    for(int i = 1; i <= 2 * n; i++) {
        if(a[i] != -1) {
            cout << a[i] << " ";
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
