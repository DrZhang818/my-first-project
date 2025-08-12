#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/432/D
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
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    auto z = Z(s);
    vector<int> cnt(n + 2);
    for(int i = 0; i < n; i++) {
        cnt[0]++;
        cnt[z[i] + 1]--;
    }
    for(int i = 1; i <= n; i++) {
        cnt[i] += cnt[i - 1];
    }
    vector<PII> ans;
    for(int i = n - 1; i >= 0; i--) {
        if(z[i] == n - i) {
            ans.emplace_back(z[i], cnt[z[i]]);
        }
    }
    cout << ans.size() << "\n";
    for(auto [len, c] : ans) {
        cout << len << " " << c << "\n";
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
