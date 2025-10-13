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
    for(int i = 0, d = 1; d <= n; i = (i + d) % n, d++) {
        for(int j = 0; j < n; j++) {
            cout << (i + j) % n + 1 << " \n"[j == n - 1]; 
        }
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
