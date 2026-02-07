#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

const string T = "keyence";
const int m = T.size();

void solve() {  
    string s;
    cin >> s;
    int n = s.size();
    for(int i = 0; i < m; i++) {
        string cur = s.substr(0, i);
        cur += s.substr(n - m + i);
        if(cur == T) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
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
