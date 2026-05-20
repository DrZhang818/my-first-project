#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr i64 inf = 1E18;

void solve() {
    string s;
    cin >> s;
    int cnt = count(s.begin(), s.end(), s[0]);
    if(cnt == 4) {
        cout << "Weak\n";
        return;
    }
    cnt = 0;
    for(int i = 1; i <= 3; i++) {
        if(s[i] == s[i - 1] + 1 || s[i - 1] == '9' && s[i] == '0') {
            cnt++;
        }
    }
    if(cnt == 3) {
        cout << "Weak\n";
        return;
    }
    cout << "Strong\n";
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
