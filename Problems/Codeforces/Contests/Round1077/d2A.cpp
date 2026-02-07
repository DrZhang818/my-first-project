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
    vector<int> p(n + 1);
    p[n] = n;
    for(int i = n - 1, s = 0; i >= 1; i--, s ^= 1) {
        if(s == 0) {
            p[i] = p[i + 1] - i;
        } else {
            p[i] = p[i + 1] + i;
        }
    }    
    for(int i = 1; i <= n; i++) {
        cout << p[i] << " \n"[i == n];
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
