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
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    unordered_set<int> up, down;
    for(int i = n; i >= 1; i--) {
        bool ok = a[i] == b[i];
        if(down.count(b[i]) || up.count(a[i])) ok = true;
        if(ok) {
            cout << i << "\n";
            return;
        }
        up.insert(a[i]);
        down.insert(b[i]);
        if(i <= n - 1) {
            up.insert(b[i + 1]);
            down.insert(a[i + 1]);
        }
    }
    cout << 0 << "\n";
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
