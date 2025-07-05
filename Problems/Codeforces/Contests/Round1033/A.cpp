#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    vector<int> a(4), b(4);
    for(int i = 3; i >= 1; i--) {
        cin >> a[i] >> b[i];
    }
    if(a[1] == a[2] && a[2] == a[3]) {
        if(b[1] + b[2] + b[3] == a[1]) {
            cout << "YES\n";
            return;
        } 
    } else if(a[1] + a[2] == a[3]) {
        if(b[1] == b[2] && b[1] + b[3] == a[3]) {
            cout << "YES\n";
            return;
        } 
    }
    if(b[1] == b[2] && b[2] == b[3]) {
        if(a[1] + a[2] + a[3] == b[1]) {
            cout << "YES\n";
            return;
        } 
    } else if(b[1] + b[2] == b[3]) {
        if(a[1] == a[2] && a[1] + a[3] == b[3]) {
            cout << "YES\n";
            return;
        } 
    }
    cout << "NO\n";
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
