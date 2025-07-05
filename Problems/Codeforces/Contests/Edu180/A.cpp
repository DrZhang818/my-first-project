#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int a, x, y;
    cin >> a >> x >> y;
    if(x > y) swap(x, y);
    int mn = min(a - x, y - a);
    if(mn >= 0) {
        cout << "NO\n";
    } else {
        cout << "YES\n";        
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
