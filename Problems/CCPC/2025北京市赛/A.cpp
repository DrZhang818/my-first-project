#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    if(s.front() != s.back()) {
        cout << "empty\n";
        return;
    }

    vector<int> pos {-1};
    for(int i = 0; i < n; i++) {
        if(s[i] != s[0]) {
            pos.push_back(i);
        }
    }
    pos.push_back(n);

    int len = inf;
    for(int i = 1; i < pos.size(); i++) {
        len = min(len, pos[i] - pos[i - 1] - 1);
    }

    if(len == 0) {
        cout << "empty\n";
        return;
    }
    cout << string(len, s[0]) << "\n";
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