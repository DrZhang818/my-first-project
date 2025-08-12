#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/UVA11475

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
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    while(cin >> s) {
        string inv_s = s;
        reverse(inv_s.begin(), inv_s.end());
        auto p = P(inv_s, s);
        int n = s.size(), i = 0;
        while(p[i] != n - i) i++;
        for(int j = i - 1; j >= 0; j--) {
            s += s[j];
        }
        cout << s << "\n";
    }
    return 0;
}
