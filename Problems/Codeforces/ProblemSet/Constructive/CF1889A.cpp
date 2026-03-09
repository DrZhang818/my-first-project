#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    int c0 = count(s.begin(), s.end(), '0');
    int c1 = n - c0;
    if(c0 != c1) {
        cout << -1 << "\n";
        return;
    }

    int l = 0, r = n;
    vector<int> ans {};

    while(s.size()) {
        if(s.front() != s.back()) {
            s = s.substr(1, s.size() - 2);
            l++;
            r--;
            continue;
        }
        if(s.front() == '0') {
            s = s.substr(1, s.size() - 1) + "0";
            ans.push_back(r);
        } else {
            s = "1" + s.substr(0, s.size() - 1);
            ans.push_back(l);
        }
        l++;
        r++;
    }

    int m = ans.size();
    cout << m << "\n";
    for(int i : ans) {
        cout << i << " ";
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
