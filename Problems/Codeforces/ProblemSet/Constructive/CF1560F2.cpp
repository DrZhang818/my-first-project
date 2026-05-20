#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    string s;
    int k;
    cin >> s >> k;

    int m = s.size();

    auto ck = [&](const string& s) {
        int msk = 0;
        for(char c : s) {
            msk |= 1 << (c - '0');
        }        
        return __builtin_popcount(msk) <= k;
    };

    if(ck(s)) {
        cout << s << "\n";
        return;
    }

    for(int i = m; i >= 0; i--) {
        string cur = s.substr(0, i);
        if(!ck(cur)) continue;

        for(int j = s[i] - '0' + 1; j < 10; j++) {
            cur += char(j + '0');
            if(ck(cur)) {
                break;
            }
            cur.pop_back();
        }
        if(cur.size() == i) continue;

        string tmp = cur;
        for(int j = 0; j < 10; j++) {
            cur = tmp;
            cur += string(m - (i + 1), char(j + '0'));
            if(ck(cur)) {
                cout << cur << "\n";
                return;
            }
        } 
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}