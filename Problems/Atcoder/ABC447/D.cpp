#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    string s;
    cin >> s;

    int cnt_c = count(s.begin(), s.end(), 'C');
    int cnt_a = 0;
    int used = 0;

    int ans = 0;
    for(char c : s) {
        if(c == 'A') {
            cnt_a++;
        } else if(c == 'B') {
            if(cnt_a > 0 && cnt_c > 0) {
                ans++;
                cnt_a--;
                cnt_c--;
                used++;
            }
        } else {
            if(used > 0) {
                used--;
            } else {
                cnt_c--;
            }
        }
    }

    cout << ans << "\n";
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
