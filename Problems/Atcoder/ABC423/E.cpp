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
    vector<ll> s1(n + 1), s2(n + 1), s3(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        s1[i] = s1[i - 1] + a[i];
        s2[i] = s2[i - 1] + 1LL * i * a[i];
        s3[i] = s3[i - 1] - 1LL * i * i * a[i];
    }
    while(q--) {
        ll l, r;
        cin >> l >> r;
        cout << s3[r] - s3[l - 1] + (l + r) * (s2[r] - s2[l - 1]) + (r - l + 1 - l * r) * (s1[r] - s1[l - 1]) << "\n";
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
