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
    vector<int> pre(n + 2), suf(n + 2);
    for(int i = 1; i <= n; i++) {
        pre[i] = max(pre[i - 1], a[i]);
    }
    for(int i = n; i >= 1; i--) {
        suf[i] = max(suf[i + 1], a[i]);
    }
    for(int i = 1; i <= n; i++) {
        cout << max(pre[i - 1], suf[i + 1]) << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
