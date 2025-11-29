#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    int c2 = 0, c3 = 0, c5 = 0;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        while(x % 2 == 0) {
            c2++;
            x /= 2;
        }
        while(x % 3 == 0) {
            c3++;
            x /= 3;
        }
        while(x % 5 == 0) {
            c5++;
            x /= 5;
        }
    }
    cout << min({c2, c3, c5}) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
