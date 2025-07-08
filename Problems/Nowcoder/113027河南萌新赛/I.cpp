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
    string s;
    cin >> s;
    int l, r;
    cin >> l >> r;
    assert(n == s.size());
    assert(1 <= l && l <= n);
    assert(1 <= r && r <= n);
    if(s[0] == s[n - 1]) {
        cout << "Yes\n";
        return;
    }
    if(l == 1 || r == n) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
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
