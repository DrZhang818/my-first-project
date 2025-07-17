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
    int cur = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            printf("%4d", ++cur);
        }
        printf("\n");
    }
}

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
