#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pre1(n + 1), pre2(n + 1);
    for(int i = 2; i <= n; i++) {
        pre1[i] = pre1[i - 1] + (a[i - 1] < a[i]);
        pre2[i] = pre2[i - 1] + (a[i - 1] > a[i]);
    }
    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << pre1[r] - pre1[l] << " " << pre2[r] - pre2[l] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
