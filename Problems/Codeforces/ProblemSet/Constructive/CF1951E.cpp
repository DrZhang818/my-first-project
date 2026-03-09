#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    string s;
    cin >> s;
    auto t = s;
    reverse(t.begin(), t.end());
    if(t != s) {
        cout << "YES\n";
        cout << 1 << "\n" << s << "\n";
        return;
    }

    vector<int> pos;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] != s[0]) {
            pos.push_back(i);
        }
    }

    if(pos.size() < 2) {
        cout << "NO\n";
        return;
    }

    int st = pos[0], en = s.size() - pos.back() - 1;
    for(int i = 1; i < pos.size(); i++) {
        int d = pos[i] - pos[i - 1] - 1;
        int x = 0;
        while(x <= d && (x == st || d - x == en)) {
            x++;
        }
        if(x <= d) {
            cout << "YES\n";
            cout << 2 << "\n";
            cout << s.substr(0, pos[i - 1] + 1 + x) << " " << s.substr(pos[i - 1] + 1 + x) << "\n";
            return;
        }
    }

    for(int i = 1; i < pos.size(); i++) {
        if(s[pos[i]] != s[pos[0]]) {
            cout << "YES\n";
            cout << 2 << "\n";
            cout << s.substr(0, pos[i] + 2) << " " << s.substr(pos[i] + 2) << "\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
