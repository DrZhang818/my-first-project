#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {      
    string s;
    vector<string> ss;
    int mx = 0;
    while(getline(cin, s)) {
        ss.emplace_back(s);
        mx = max(mx, int(s.size()));
    }
    int len = mx + 2;
    cout << string(len, '*') << "\n";
    int tag = 0;
    for(string &s : ss) {
        int sz = s.size();
        int m = len - 2 - sz;
        int x = m / 2, y = m / 2;
        if(m & 1) {
            if(tag == 0) {
                y++;
            } else {
                x++;
            }
            tag ^= 1;
        }
        cout << "*";
        cout << string(x, ' ');
        cout << s;
        cout << string(y, ' ');
        cout << "*";
        cout << "\n";
    }
    cout << string(len, '*') << "\n";
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
