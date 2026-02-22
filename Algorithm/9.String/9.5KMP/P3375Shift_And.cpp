#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

using B = bitset<1000005>;

B h[26], F;

void solve() {  
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();

    for(int i = 0; i < m; i++) {
        h[t[i] - 'A'].set(i);
    }

    for(int i = 0; i < n; i++) {
        F <<= 1;
        F.set(0);
        F &= h[s[i] - 'A'];
        if(F.test(m - 1)) {
            cout << i - m + 2 << "\n";
        }
    }
}

B h[26], F;

void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();

    for(int i = 0; i < n; i++) {
        h[s[i] - 'A'].set(i);
        F.set(i);
    }

    for(int i = 0; i < m; i++) {
        F &= (h[t[i] - 'A'] >> i);
    }

    for(int i = 0; i < n; i++) {
        if(F.test(i)) {
            cout << i + 1 << "\n";
        }
    }
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
