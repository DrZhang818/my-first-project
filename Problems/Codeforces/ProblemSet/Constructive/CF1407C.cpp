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
    vector<int> a(n + 1), c(n + 1);
    int l = 1, r = n;
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cout << "? " << l << " " << r << endl;
        cin >> u;
        cout << "? " << r << " " << l << endl;
        cin >> v;
        if(u > v) a[l++] = u, c[u] = 1;
        else a[r--] = v, c[v] = 1; 
    }
    for(int i = 1; i <= n; i++) {
        if(!c[i]) {
            a[l] = i;
            break;
        }
    }
    cout << "! ";
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
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
