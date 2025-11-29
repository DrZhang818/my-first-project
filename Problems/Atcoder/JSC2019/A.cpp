#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int m, d;
    cin >> m >> d;
    int cnt = 0;
    for(int i = 1; i <= m; i++) {
        for(int j = 20; j <= d; j++) {
            int a = j % 10, b = j / 10 % 10;
            if(a >= 2 && a * b == i) {
                cnt++;
            }
        }
    }
    cout << cnt << "\n";
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
