#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, x, num;
    cin >> n >> x >> num;
    string s;
    cin >> s;

    int cnt = count(s.begin(), s.end(), 'I');
    int ans = 0;

    for(int i = 0; i <= min(x, cnt); i++) {
        int cur = i, rem = x - i, cands = 0, rem2 = i;
        for(char c : s) {
            if(c == 'A') {
                if(rem > 0) {
                    rem--;
                    cands += num - 1;
                    cur++;
                } else if(cands) {
                    cands--;
                    cur++;
                }
            } else if(c == 'E') {
                if(cands) {
                    cands--;
                    cur++;
                }
            } else {
                if(rem2) {
                    cands += num - 1;
                    rem2--;
                }
            }
        }
        ans = max(ans, cur);
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