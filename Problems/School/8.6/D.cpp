#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int a, b, k;
    cin >> a >> b >> k;
    for(int i = min(a, b); i >= 1; i--) {
        if(a % i == 0 && b % i == 0) k--;
        if(k == 0) {
            cout << i << "\n";
            return;
        }
    }
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
