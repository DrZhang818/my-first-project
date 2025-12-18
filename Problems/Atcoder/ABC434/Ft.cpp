#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int n;
    cin >> n;
    vector<string> s(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    if(n == 2) {
        cout << max(s[1] + s[2], s[2] + s[1]) << "\n";
        return;
    }

    shuffle(s.begin() + 1, s.end(), rng);

    sort(s.begin() + 1, s.end(),
        [&](auto &x, auto &y) {
            return x + y < y + x;
        });

    bool equal = false;
    for(int i = 1; i < n; i++) {
        if(s[i] + s[i + 1] == s[i + 1] + s[i]) {
            equal = true;
            break;
        }
    }
    if(!equal) {
        for(int i = 1; i < n - 2; i++) {
            cout << s[i];
        }
        string ans1 = s[n - 2] + s[n] + s[n - 1];
        string ans2 = s[n - 1] + s[n - 2] + s[n];
        cout << min(ans1, ans2) << "\n";
    } else {
        for(int i = 1; i <= n; i++) {
            cout << s[i];
        }
        cout << "\n";
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
