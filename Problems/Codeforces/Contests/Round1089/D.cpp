#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;

    auto work = [&](const string& s) -> pair<int,int> {
        stack<int> stk;

        vector<int> pre(n, -1);
        for(int i = 0; i < n; i++) {
            char c = s[i];
            if(c == '(') {
                stk.push(i);
            } else {
                pre[i] = stk.top();
                stk.pop();
            }
        }

        int out = 0, cnt = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] == '(') continue;
            if(pre[i] == i - 1) {
                cnt++;
            }
        }

        for(int i = n - 1; i >= 0; i--) {
            if(pre[i] == n - 1 - i) {
                out++;
            } else {
                break;
            }
        }

        return {out, cnt};
    };

    auto ps = work(s);
    auto pt = work(t);

    if(ps == pt) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
