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
    vector<int> pos(n + 1);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    vector<int> val;
    for(int i = 1; i <= n; i++) {
        if(!pos[i]) {
            val.push_back(i);
        }
    }
    for(int i = 1; i <= n; i++) {
        if(a[i] == 0) {
            a[i] = val.back();
            val.pop_back();
        }
    }
    int L = 0, R = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] != i) {
            L = i;
            break;
        }
    }
    for(int i = n; i >= 1; i--) {
        if(a[i] != i) {
            R = i;
            break;
        }
    }
    if(L == 0) {
        cout << 0 << "\n";
        return;
    }
    cout << R - L + 1 << "\n";
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
