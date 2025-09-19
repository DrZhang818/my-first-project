#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, k;
    cin >> n >> k;
    if(n & 1) {
        cout << "Alice\n";
        return;
    }
    int block = 1;
    while(block <= k) {
        block <<= 1;
    }
    if(n % block == 0) {
        cout << "Bob\n";
    } else {
        cout << "Alice\n";
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
