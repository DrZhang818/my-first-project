#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> Z(string &s) {
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    for(int i = 1, j = 1; i < n; i++) {
        z[i] = max(0, min(j + z[j] - i, z[i - j]));
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > j + z[j]) {
            j = i;
        }
    }
    return z;
}
vector<int> P(string &s, string &t) {
    int n = s.size(), m = t.size();
    auto z = Z(s);
    vector<int> p(m);
    for(int i = 0, j = 0; i < m; i++) {
        p[i] = max(0, min(j + p[j] - i, z[i - j]));
        while(p[i] < n && i + p[i] < m && s[p[i]] == t[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > j + p[j]) {
            j = i;
        }
    }
    return p;
}
void solve() {
    string a, b;
    cin >> a >> b;
    auto z = Z(b);
    auto p = P(b, a);
    ll ans1 = 0, ans2 = 0;
    for(int i = 0; i < b.size(); i++) {
        ans1 ^= 1LL * (i + 1) * (z[i] + 1);
    }
    for(int i = 0; i < a.size(); i++) {
        ans2 ^= 1LL * (i + 1) * (p[i] + 1);
    }
    cout << ans1 << "\n" << ans2 << "\n";
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
