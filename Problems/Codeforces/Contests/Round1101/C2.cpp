#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    i64 n, x, num;
    cin >> n >> x >> num;
    string s;
    cin >> s;

    i64 ans = 0;

    i64 rem = x, used = 0, cands = 0;
    for(char c : s) {
        if(c == 'A') {
            if(cands > 0) {
                cands--;
                used++;
                ans++;
            } else if(rem > 0) {
                rem--;
                cands += num - 1;
                ans++;
            }
        } else if(c == 'E') {
            if(cands > 0) {
                cands--;
                ans++;
            } else if(used > 0 && rem > 0) {
                rem--;
                used--;
                cands += num - 1;
                ans++;
            }
        } else {
            if(rem > 0) {
                rem--;
                cands += num - 1;
                ans++;
            }
        }
    }
    cout << ans << "\n";
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