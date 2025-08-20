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
    string s;
    cin >> s;
    vector<int> a(n + 1);
    for(int i = 1; i < n; i++) {
        if(s[i - 1] == 'A' && s[i] == 'C') {
            a[i]++;
        }
    }
    for(int i = 1; i <= n; i++) {
        a[i] += a[i - 1];
    }
    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << a[r - 1] - a[l - 1] << "\n";
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
