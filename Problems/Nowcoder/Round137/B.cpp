#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    deque<char> dq;
    int dir = 1;
    for(char c : s) {
        if(c == '!') {
            dir ^= 1;
        } else if(c == '-') {
            if(dq.empty()) continue;
            if(dir == 1) {
                dq.pop_back();
            } else {
                dq.pop_front();
            }
        } else {
            if(dir == 1) {
                dq.push_back(c);
            } else {
                dq.push_front(c);
            }
        }
    }
    if(dq.empty()) {
        cout << "Empty\n";
        return ;
    }
    while(!dq.empty()) {
        cout << dq.front();
        dq.pop_front();
    }
    cout << "\n";
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
