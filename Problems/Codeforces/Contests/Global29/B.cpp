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
    vector<int> a(2 * n + 1);
    a[1] = a[n + 1] = n;
    for(int i = 2; i <= n; i++) {
        a[i] = a[2 * n - i + 2] = n - i + 1;
    }
    for(int i = 1; i <= 2 * n; i++) {
        cout << a[i] << " \n"[i == 2 * n];
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
