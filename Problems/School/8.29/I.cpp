#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 2E18;

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
    array<int,3> dp;
    for(int i = 1; i <= n; i++) {
        array<int,3> ndp;
        if(a[i] == 1 || b[i] == 1) {
            ndp[0] = 
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init(64);
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
