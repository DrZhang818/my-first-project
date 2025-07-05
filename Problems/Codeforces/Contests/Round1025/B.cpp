#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    int a1 = 1, a2 = 1;
    int tn = min(a, n - a + 1), tm = m;
    a1 += ceil(log2(tn)) + ceil(log2(tm));
    tn = n, tm = min(b, m - b + 1);
    a2 += ceil(log2(tn)) + ceil(log2(tm));
    cout << min(a1, a2) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
