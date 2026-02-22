#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    string s;
    cin >> s;

    string t = "#";

    for(int i = 1; i < s.size(); i += 2) {
        int x = 0;
        for(int j : {i, i + 1}) {
            x *= 16;
            if(isdigit(s[j])) {
                x += s[j] - '0';
            } else {
                x += s[j] - 'a' + 10;
            }
        }
        x = 255 - x;
        int y = x % 16;
        int z = x / 16;
        for(int w : {z, y}) {
            if(w < 10) {
                t += char('0' + w);
            } else {
                t += char('a' + w - 10);
            }
        }
    }
    cout << t << "\n";
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
