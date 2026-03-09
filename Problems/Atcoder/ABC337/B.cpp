#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    string s;
    cin >> s;
    int n = s.size();
    char c[] = {'A', 'B', 'C'};
    int p = 0;
    for(int l = 0, r = 0; l < n; l = r) {
        while(r < n && s[r] == s[l]) {
            r++;
        }
        while(p < 3 && s[l] != c[p]) {
            p++;
        }
        if(p == 3) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
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
