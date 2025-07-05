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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    if(n & 1) {
        int u = a[1], v = a[2], w = a[3];
        if((v > 0) ^ (w > 0)) {
            cout << v - w << " " << -u << " " << u << " ";
        } else {
            cout << v + w << " " << -u << " " << -u << " ";
        }
        for(int i = 4; i <= n; i += 2) {
            cout << -a[i + 1] << " " << a[i] << " ";
        }
        cout << "\n";
    } else {
        for(int i = 1; i <= n; i += 2) {
            cout << -a[i + 1] << " " << a[i] << " ";
        }
        cout << "\n";
    }
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