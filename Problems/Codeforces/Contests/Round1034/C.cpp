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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pre(n + 1, inf), suf(n + 2, -inf);
    pre[1] = a[1], suf[n] = a[n];
    for(int i = 2; i <= n; i++) {
        pre[i] = min(pre[i - 1], a[i]);
    }
    for(int i = n - 1; i >= 1; i--) {
        suf[i] = max(suf[i + 1], a[i]);
    }
    for(int i = 1; i <= n; i++) {
        if(a[i] > pre[i - 1] && a[i] < suf[i + 1]) {
            cout << 0;
        } else {
            cout << 1;
        }
    }
    cout << "\n";
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

