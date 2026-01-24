#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    int c0 = 0, c1 = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x == 0) {
            c0++;
        } else if(x == 1) {
            c1++;
        }
    }
    if(c0 == 1 || c0 >= 2 && c1 >= 1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
