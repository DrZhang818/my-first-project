#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m, x, t, d;
    cin >> n >> m >> x >> t >> d;
    vector<int> a(n + 1, t);
    for(int i = x - 1, sum = d; i >= 0; i--) {
        a[i] -= sum;
        sum += d;
    }
    cout << a[m] << "\n";
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
